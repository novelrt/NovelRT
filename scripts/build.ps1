[CmdletBinding(PositionalBinding=$false)]
Param(
  [switch] $build,
  [switch] $ci,
  [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")][string] $configuration = "Debug",
  [switch] $generate,
  [switch] $help,
  [switch] $install,
  [Parameter(ValueFromRemainingArguments=$true)][String[]]$remaining
)

Set-StrictMode -Version 2.0
$ErrorActionPreference = "Stop"
[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12

function Build() {
  & cmake --build $BuildDir

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
  & cmake -S $RepoRoot -B $BuildDir -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -DCMAKE_INSTALL_PREFIX=$InstallDir $remaining

  if ($LastExitCode -ne 0) {
    throw "'Generate' failed"
  }
}

function Help() {
    Write-Host -Object "Common settings:"
    Write-Host -Object "  -configuration <value>  Build configuration (Debug, Release, RelWithDebInfo, MinSizeRel)"
    Write-Host -Object "  -help                   Print help and exit"
    Write-Host -Object ""
    Write-Host -Object "Actions:"
    Write-Host -Object "  -build                  Build repository"
    Write-Host -Object "  -generate               Generate CMake cache"
    Write-Host -Object "  -install                Install repository"
    Write-Host -Object ""
    Write-Host -Object "Advanced settings:"
    Write-Host -Object "  -ci                     Set when running on CI server"
    Write-Host -Object ""
    Write-Host -Object "Command line arguments not listed above are passed through to CMake."
    Write-Host -Object "The above arguments can be shortened as much as to be unambiguous (e.g. -co for configuration, -t for test, etc.)."
}

function Install() {
  & cmake --install $BuildDir

  if ($LastExitCode -ne 0) {
    throw "'Install' failed"
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
  }

  $RepoRoot = Join-Path -Path $PSScriptRoot -ChildPath ".."

  $ArtifactsDir = Join-Path -Path $RepoRoot -ChildPath "artifacts"
  Create-Directory -Path $ArtifactsDir

  $BuildDir = Join-Path -Path $ArtifactsDir -ChildPath "build"
  $BuildDir = Join-Path -Path $BuildDir -ChildPath $Configuration
  Create-Directory -Path $BuildDir

  $InstallDir = Join-Path -Path $ArtifactsDir -ChildPath "install"
  $InstallDir = Join-Path -Path $InstallDir -ChildPath $Configuration
  Create-Directory -Path $InstallDir

  if ($ci) {
  }

  if ($generate) {
    Generate
  }

  if ($build) {
    Build
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
