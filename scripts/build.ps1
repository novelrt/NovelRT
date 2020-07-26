[CmdletBinding(PositionalBinding=$false)]
Param(
  [switch] $build,
  [switch] $ci,
  [ValidateSet("Debug", "MinSizeRel", "Release", "RelWithDebInfo")][string] $configuration = "Debug",
  [switch] $generate,
  [switch] $help,
  [switch] $install,
  [switch] $test,
  [string] $vcpkgInstallDirectory = "$HOME/vcpkg",
  [string] $dotnetInstallDirectory = "$HOME/dotnet",
  [Parameter(ValueFromRemainingArguments=$true)][String[]] $remaining
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = "Stop"
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

function Build() {
  & cmake --build $BuildDir --config $configuration

  if ($LastExitCode -ne 0) {
    throw "'Build' failed"
  }
}

function Create-Directory([string[]] $Path) {
  if (!(Test-Path -Path $Path)) {
    New-Item -Path $Path -Force -ItemType "Directory" | Out-Null
  }
}

function Generate() {
  if ($ci) {
    $VcpkgToolchainFile = Join-Path -Path $vcpkgInstallDirectory -ChildPath "scripts/buildsystems/vcpkg.cmake"
    $remaining = ,"-DCMAKE_TOOLCHAIN_FILE=$VcpkgToolchainFile", "-DNOVELRT_BUILD_DOCUMENTATION=OFF", "-DPython_FIND_REGISTRY=NEVER", "-DPython_FIND_STRATEGY=LOCATION" + $remaining
  }

  & cmake -S $RepoRoot -B $BuildDir -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -A x64 -DCMAKE_BUILD_TYPE="$configuration" -DCMAKE_INSTALL_PREFIX="$InstallDir" $remaining

  if ($LastExitCode -ne 0) {
    throw "'Generate' failed"
  }
}

function Help() {
  Write-Host -Object "Common settings:"
  Write-Host -Object "  -configuration <value>            Build configuration (Debug, MinSizeRel, Release, RelWithDebInfo)"
  Write-Host -Object "  -dotnetInstallDirectory <value>   .NET Core install directory"
  Write-Host -Object "  -help                             Print help and exit"
  Write-Host -Object "  -vcpkgInstallDirectory <value>    VCPKG install directory"
  Write-Host -Object ""
  Write-Host -Object "Actions:"
  Write-Host -Object "  -build                            Build repository"
  Write-Host -Object "  -generate                         Generate CMake cache"
  Write-Host -Object "  -install                          Install repository"
  Write-Host -Object "  -test                             Test repository"
  Write-Host -Object ""
  Write-Host -Object "Advanced settings:"
  Write-Host -Object "  -ci                               Set when running on CI server"
  Write-Host -Object ""
  Write-Host -Object "Command line arguments not listed above are passed through to CMake."
  Write-Host -Object "The above arguments can be shortened as much as to be unambiguous (e.g. -co for configuration, -t for test, etc.)."
}

function Install() {
  & cmake --install $BuildDir --config $configuration

  if ($LastExitCode -ne 0) {
    throw "'Install' failed"
  }
}

function Test() {
  Push-Location -Path $TestDir
  & ctest --build-config $configuration --output-on-failure
  Pop-Location

  if ($LastExitCode -ne 0) {
    throw "'Test' failed"
  }
}

try {
  if ($help) {
    Help
    exit 0
  }

  if ($ci) {
    $build = $true
    $generate = $true
    $install = $true
    $test = $true
  }

  $RepoRoot = Join-Path -Path $PSScriptRoot -ChildPath ".."

  $ArtifactsDir = Join-Path -Path $RepoRoot -ChildPath "artifacts"
  Create-Directory -Path $ArtifactsDir

  $BuildDir = Join-Path -Path $ArtifactsDir -ChildPath "build/$configuration"
  Create-Directory -Path $BuildDir

  $InstallDir = Join-Path -Path $ArtifactsDir -ChildPath "install/$configuration"
  Create-Directory -Path $InstallDir

  $TestDir = Join-Path -Path $BuildDir -ChildPath "tests"
  Create-Directory -Path $TestDir

  $env:PATH="$DotNetInstallDirectory;$env:PATH"

  if ($generate) {
    Generate
  }

  if ($build) {
    Build
  }

  if ($test) {
    Test
  }

  if ($install) {
    Install
  }
}
catch {
  Write-Host -Object $_
  Write-Host -Object $_.Exception
  Write-Host -Object $_.ScriptStackTrace
  exit 1
}
