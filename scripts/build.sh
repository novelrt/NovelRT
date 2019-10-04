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
generate=false
help=false
install=false
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
  BuildArgs="--build \"$BuildDir\""

  if [[ ! -z "$remaining" ]]; then
    BuildArgs="$BuildArgs ${remaining[@]}"
  fi

  cmake "${BuildArgs[@]}"
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
  GenerateArgs="-B \"$BuildDir\" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX=\"$InstallDir\""

  if $ci; then
    vcpkgToolchainFile="$VcpkgInstallDir/scripts/buildsystems/vcpkg.cmake"
    GenerateArgs="$GenerateArgs -DCMAKE_TOOLCHAIN_FILE=\"$vcpkgToolchainFile\""
  fi

  if [[ ! -z "$remaining" ]]; then
    GenerateArgs="$GenerateArgs ${remaining[@]}"
  fi

  cmake "${GenerateArgs[@]}"
  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'Generate' failed"
    return "$LASTEXITCODE"
  fi
}

function Help {
  echo "Common settings:"
  echo "  --configuration <value>   Build configuration (Debug, MinSizeRel, Release, RelWithDebInfo)"
  echo "  --help                    Print help and exit"
  echo ""
  echo "Actions:"
  echo "  --build                   Build repository"
  echo "  --generate                Generate CMake cache"
  echo "  --install                 Install repository"
  echo ""
  echo "Advanced settings:"
  echo "  --ci                      Set when running on CI server"
  echo ""
  echo "Command line arguments not listed above are passed through to CMake."
}

function Install {
  InstallArgs="--install \"$BuildDir\""

  if [[ ! -z "$remaining" ]]; then
    InstallArgs="$InstallArgs ${remaining[@]}"
  fi

  cmake "${InstallArgs[@]}"
  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'Install' failed"
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
fi

RepoRoot="$ScriptRoot/.."

ArtifactsDir="$RepoRoot/artifacts"
CreateDirectory "$ArtifactsDir"

BuildDir="$ArtifactsDir/build/$configuration"
CreateDirectory "$BuildDir"

InstallDir="$ArtifactsDir/install/$configuration"
CreateDirectory "$InstallDir"

if $ci; then
  VcpkgInstallDir="$ArtifactsDir/vcpkg"

  if [ ! -d "$VcpkgInstallDir" ]; then
     git clone https://github.com/microsoft/vcpkg "$VcpkgInstallDir"
  fi

  "$VcpkgInstallDir/bootstrap-vcpkg.sh"
  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'bootstrap-vcpkg' failed"
    return "$LASTEXITCODE"
  fi

  "$VcpkgInstallDir/vcpkg.exe" install freetype glad glm lua sdl2 sdl2-image
  LASTEXITCODE=$?

  if [ "$LASTEXITCODE" != 0 ]; then
    echo "'vcpkg install' failed"
    return "$LASTEXITCODE"
  fi
fi

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

if $install; then
  Install

  if [ "$LASTEXITCODE" != 0 ]; then
    return "$LASTEXITCODE"
  fi
fi
