[CmdletBinding(PositionalBinding=$false)]
Param(
  [switch] $build,
  [switch] $ci,
  [ValidateSet("Debug", "MinSizeRel", "Release", "RelWithDebInfo")][string] $configuration = "Debug",
  [switch] $generate,
  [switch] $help,
  [switch] $install,
  [switch] $test,
  [Parameter(ValueFromRemainingArguments=$true)][String[]]$remaining
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
  & cmake -S $RepoRoot -B $BuildDir -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -A x64 -DCMAKE_BUILD_TYPE="$configuration" -DCMAKE_INSTALL_PREFIX="$InstallDir" $remaining

  if ($LastExitCode -ne 0) {
    throw "'Generate' failed"
  }
}

function Help() {
    Write-Host -Object "Common settings:"
    Write-Host -Object "  -configuration <value>  Build configuration (Debug, MinSizeRel, Release, RelWithDebInfo)"
    Write-Host -Object "  -help                   Print help and exit"
    Write-Host -Object ""
    Write-Host -Object "Actions:"
    Write-Host -Object "  -build                  Build repository"
    Write-Host -Object "  -generate               Generate CMake cache"
    Write-Host -Object "  -install                Install repository"
    Write-Host -Object "  -test                   Test repository"
    Write-Host -Object ""
    Write-Host -Object "Advanced settings:"
    Write-Host -Object "  -ci                     Set when running on CI server"
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

  if ($ci) {
    $env:DOTNET_CLI_TELEMETRY_OPTOUT = 1
    $env:DOTNET_MULTILEVEL_LOOKUP = 0
    $env:DOTNET_SKIP_FIRST_TIME_EXPERIENCE = 1

    $DotNetInstallScript = Join-Path -Path $ArtifactsDir -ChildPath "dotnet-install.ps1"
    Invoke-WebRequest -Uri "https://dot.net/v1/dotnet-install.ps1" -OutFile $DotNetInstallScript -UseBasicParsing

    $DotNetInstallDirectory = Join-Path -Path $ArtifactsDir -ChildPath "dotnet"
    Create-Directory -Path $DotNetInstallDirectory

    & $DotNetInstallScript -Channel 3.1 -Version latest -InstallDir $DotNetInstallDirectory
    & $DotNetInstallScript -Channel 2.1 -Version latest -InstallDir $DotNetInstallDirectory -Runtime dotnet

    $env:PATH="$DotNetInstallDirectory;$env:PATH"

    & dotnet | Out-Null
  }

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
