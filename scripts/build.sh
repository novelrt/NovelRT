#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  ScriptRoot="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$ScriptRoot/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
ScriptRoot="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

build=false
ci=false
configuration='Debug'
dotnetInstallDirectory="$HOME/dotnet"
generate=false
help=false
install=false
test=false
remaining=''

while [[ $# -gt 0 ]]; do
  lower="$(echo "$1" | awk '{print tolower($0)}')"
  case $lower in
    --build)
      build=true
      shift 1
      ;;
    --ci)
      ci=true
      shift 1
      ;;
    --configuration)
      configuration=$2
      shift 2
      ;;
    --dotnetInstallDirectory)
      dotnetInstallDirectory=$2
      shift 2
      ;;
    --generate)
      generate=true
      shift 1
      ;;
    --help)
      help=true
      shift 1
      ;;
    --install)
      install=true
      shift 1
      ;;
    --test)
      test=true
      shift 1
      ;;
    *)
      if [ -z "$remaining" ]; then
        remaining="$1"
      else
        remaining="$remaining $1"
      fi
      shift 1
      ;;
  esac
done

function Build {
  if [ -z "$remaining" ]; then
    cmake --build "$BuildDir" --config "$configuration"
  else
    cmake --build "$BuildDir" --config "$configuration" "${remaining[@]}"
  fi

  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'Build' failed"
    return "$LASTEXITCODE"
  fi
}

function CreateDirectory {
  if [ ! -d "$1" ]; then
    mkdir -p "$1"
  fi
}

function Generate {
  if [ -z "$remaining" ]; then
    cmake -S "$RepoRoot" -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_BUILD_TYPE="$configuration" -DCMAKE_INSTALL_PREFIX="$InstallDir"
  else
    cmake -S "$RepoRoot" -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_BUILD_TYPE="$configuration" -DCMAKE_INSTALL_PREFIX="$InstallDir" "${remaining[@]}"
  fi

  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'Generate' failed"
    return "$LASTEXITCODE"
  fi
}

function Help {
  echo "Common settings:"
  echo "  --configuration <value>             Build configuration (Debug, MinSizeRel, Release, RelWithDebInfo)"
  echo "  --dotnetInstallDirectory <value>   .NET Core install directory"
  echo "  --help                              Print help and exit"
  echo ""
  echo "Actions:"
  echo "  --build                             Build repository"
  echo "  --generate                          Generate CMake cache"
  echo "  --install                           Install repository"
  echo "  --test                              Test repository"
  echo ""
  echo "Advanced settings:"
  echo "  --ci                                Set when running on CI server"
  echo ""
  echo "Command line arguments not listed above are passed through to CMake."
}

function Install {
  if [ -z "$remaining" ]; then
    cmake --install "$BuildDir" --config "$configuration"
  else
    cmake --install "$BuildDir" --config "$configuration" "${remaining[@]}"
  fi

  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'Install' failed"
    return "$LASTEXITCODE"
  fi
}

function Test {
  pushd "$TestDir"

  if [ -z "$remaining" ]; then
    ctest --build-config "$configuration" --output-on-failure
  else
    ctest --build-config "$configuration" --output-on-failure "${remaining[@]}"
  fi

  LASTEXITCODE=$?
  popd

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'Test' failed"
    return "$LASTEXITCODE"
  fi
}

if $help; then
  Help
  exit 0
fi

if $ci; then
  build=true
  generate=true
  install=true
  test=true
fi

RepoRoot="$ScriptRoot/.."

ArtifactsDir="$RepoRoot/artifacts"
CreateDirectory "$ArtifactsDir"

BuildDir="$ArtifactsDir/build/$configuration"
CreateDirectory "$BuildDir"

InstallDir="$ArtifactsDir/install/$configuration"
CreateDirectory "$InstallDir"

TestDir="$BuildDir/tests"
CreateDirectory "$TestDir"

export PATH="$dotnetInstallDirectory:$PATH:"

if $generate; then
  Generate

  if [ "$LASTEXITCODE" != 0 ]; then
    return "$LASTEXITCODE"
  fi
fi

if $build; then
  Build

  if [ "$LASTEXITCODE" != 0 ]; then
    return "$LASTEXITCODE"
  fi
fi

if $test; then
  Test

  if [ "$LASTEXITCODE" != 0 ]; then
    return "$LASTEXITCODE"
  fi
fi

if $install; then
  Install

  if [ "$LASTEXITCODE" != 0 ]; then
    return "$LASTEXITCODE"
  fi
fi
