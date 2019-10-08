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
  if [ -z "$remaining" ]; then
    cmake --build "$BuildDir"
  else
    cmake --build "$BuildDir" "${remaining[@]}"
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
    if $ci; then
      VcpkgToolchainFile="$VcpkgInstallDir/scripts/buildsystems/vcpkg.cmake"
      echo cmake -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX="$InstallDir" -DCMAKE_TOOLCHAIN_FILE="$VcpkgToolchainFile"
      cmake -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX="$InstallDir" -DCMAKE_TOOLCHAIN_FILE="$VcpkgToolchainFile"
    else
      cmake -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX="$InstallDir"
    fi
  else
    if $ci; then
      VcpkgToolchainFile="$VcpkgInstallDir/scripts/buildsystems/vcpkg.cmake"
      cmake -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX="$InstallDir" -DCMAKE_TOOLCHAIN_FILE="$VcpkgToolchainFile" "${remaining[@]}"
    else
      cmake -B "$BuildDir" -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX="$InstallDir" "${remaining[@]}"
    fi
  fi

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
  if [ -z "$remaining" ]; then
    cmake --install "$BuildDir"
  else
    cmake --install "$BuildDir" "${remaining[@]}"
  fi

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

  VcpkgExe="$VcpkgInstallDir/vcpkg"

  if [ ! -f "$VcpkgExe" ]; then
    "$VcpkgInstallDir/bootstrap-vcpkg.sh"
    LASTEXITCODE=$?

    if [ "$LASTEXITCODE" != 0 ]; then
      echo "'bootstrap-vcpkg' failed"
      return "$LASTEXITCODE"
    fi
  fi

  "$VcpkgExe" install freetype glad glm lua sdl2 sdl2-image sdl2-mixer[core,mpg123,libvorbis]
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
