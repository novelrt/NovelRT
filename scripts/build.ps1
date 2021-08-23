[CmdletBinding(PositionalBinding=$false)]
Param(
  [switch] $build,
  [switch] $ci,
  [ValidateSet("Debug", "MinSizeRel", "Release", "RelWithDebInfo")][string] $configuration = "Debug",
  [switch] $documentation,
  [switch] $generate,
  [switch] $help,
  [switch] $install,
  [switch] $test,
  [ValidateSet("all", "csharp")][string] $update = "",
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
  conan config install https://github.com/novelrt/ConanConfig.git
  conan install . -if "$BuildDir" --build=missing --profile windows-vs2019-amd64
    $remaining = ,"-DNOVELRT_BUILD_DOCUMENTATION=OFF", "-DPython_FIND_REGISTRY=NEVER", "-DPython_FIND_STRATEGY=LOCATION" + $remaining
  }

  & cmake -S $RepoRoot -B $BuildDir -Wdev -Werror=dev -Wdeprecated -Werror=deprecated -A x64 -DCMAKE_BUILD_TYPE="$configuration" -DCMAKE_INSTALL_PREFIX="$InstallDir" $remaining

  if ($LastExitCode -ne 0) {
    throw "'Generate' failed"
  }
}

function BuildDocumentation() {
  & cmake --build $BuildDir --config $configuration --target Doxygen

  if ($LastExitCode -ne 0) {
    throw "'Build Documentation' failed"
  }
}

function Help() {
  Write-Host -Object "Common settings:"
  Write-Host -Object "  -configuration <value>            Build configuration (Debug, MinSizeRel, Release, RelWithDebInfo)"
  Write-Host -Object "  -dotnetInstallDirectory <value>   .NET Core install directory"
  Write-Host -Object "  -help                             Print help and exit"
  Write-Host -Object ""
  Write-Host -Object "Actions:"
  Write-Host -Object "  -build                            Build repository"
  Write-Host -Object "  -generate                         Generate CMake cache"
  Write-Host -Object "  -documentation                    Generate CMake cache and Build Doxygen documentation"
  Write-Host -Object "  -install                          Install repository"
  Write-Host -Object "  -test                             Test repository"
  Write-Host -Object ""
  Write-Host -Object "Advanced settings:"
  Write-Host -Object "  -ci                               Set when running on CI server"
  Write-Host -Object "  -update <value>                   Update the bindings for the given language (csharp)"
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

function Update-CSharp() {
  $generationDir = Join-Path -Path $RepoRoot -ChildPath "generation"
  $generateRspFiles = Get-ChildItem -Path "$generationDir" -Recurse -Filter "generate.rsp"

  $generateRspFiles | ForEach-Object -Parallel {
    $includeDirectories = @(
      "$HOME/.conan/data/bzip2/1.0.8/_/_/package/4528437567062bbbdabe0f12323b342a14f38892/include"
      "$HOME/.conan/data/flac/1.3.3/_/_/package/840741e0c2fe086ebeae5ebab1d812f6f8a24eea/include"
      "$HOME/.conan/data/fmt/7.1.2/_/_/package/127af201a4cdf8111e2e08540525c245c9b3b99e/include"
      "$HOME/.conan/data/freetype/2.10.1/_/_/package/0346a2bb772a133154db158db36dcafcf4a18114/include"
      "$HOME/.conan/data/freetype/2.10.1/_/_/package/0346a2bb772a133154db158db36dcafcf4a18114/include/freetype2"
      "$HOME/.conan/data/glad/0.1.33/_/_/package/830ebe61abc2ce47d1ae6b80029e84624132be57/include"
      "$HOME/.conan/data/glfw/3.3.2/_/_/package/bbccade5442fcfbbf624bac852a93d4485409c0f/include"
      "$HOME/.conan/data/glm/0.9.9.7/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
      "$HOME/.conan/data/gtest/1.10.0/_/_/package/5ad274d83035c78ba2b205e6cf4f1b317aee8e05/include"
      "$HOME/.conan/data/libpng/1.6.37/_/_/package/d140711d95cc16a85766a8fc3a551dfafe84cf63/include"
      "$HOME/.conan/data/libsndfile/1.0.30/_/_/package/0556be7ad73b556f90040e7e7a680a076aa21856/include"
      "$HOME/.conan/data/lua/5.3.5/_/_/package/127af201a4cdf8111e2e08540525c245c9b3b99e/include"
      "$HOME/.conan/data/ms-gsl/3.1.0/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
      "$HOME/.conan/data/ogg/1.3.4/_/_/package/127af201a4cdf8111e2e08540525c245c9b3b99e/include"
      "$HOME/.conan/data/openal/1.19.1/_/_/package/127af201a4cdf8111e2e08540525c245c9b3b99e/include"
      "$HOME/.conan/data/opengl/system/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
      "$HOME/.conan/data/opus/1.3.1/_/_/package/127af201a4cdf8111e2e08540525c245c9b3b99e/include"
      "$HOME/.conan/data/spdlog/1.8.2/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include"
      "$HOME/.conan/data/vorbis/1.3.7/_/_/package/840741e0c2fe086ebeae5ebab1d812f6f8a24eea/include"
      "$HOME/.conan/data/zlib/1.2.11/_/_/package/3fb49604f9c2f729b85ba3115852006824e72cab/include"
    )

    Push-Location -Path $_.DirectoryName
    & ClangSharpPInvokeGenerator "@generate.rsp" --include-directory $includeDirectories
    Pop-Location
  }
}

try {
  if ($help) {
    Help
    exit 0
  }

  if ($ci) {
    $generate = $true
    if ($documentation)
    {
      $build = $false
      $install = $false
      $test = $false
    }
    else
    {
      $build = $true
      $install = $true
      $test = $true
    }

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

  if ($update -eq "all" -or $update -eq "csharp") {
    Update-CSharp
  }

  if ($generate) {
    Generate
  }

  if ($documentation) {
    BuildDocumentation
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
