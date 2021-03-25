# NOTE: DO NOT RUN THIS ON DEVELOPMENT MACHINES!
# This is intended for setting up CI machines with the correct dependencies.

$DotNetInstallDirectory = Join-Path -Path $HOME -ChildPath "dotnet"
$ProgressPreference = 'SilentlyContinue'

if (!(Get-Command python -ErrorAction SilentlyContinue ))
{
  $PythonInstaller = New-TemporaryFile | Rename-Item -NewName { $_.Name + ".exe" } -PassThru
  Invoke-WebRequest -Uri "https://www.python.org/ftp/python/3.8.3/python-3.8.3.exe" -OutFile $PythonInstaller

  & $PythonInstaller /quiet InstallAllUsers=0 PrependPath=1 Include_test=0

  if ($LastExitCode -ne 0) {
    throw "'python-3.8.3' failed"
  }
}

& python -m pip --version
& python -m pip install conan

if ($LastExitCode -ne 0) {
  throw "'pip install' failed"
}

$env:DOTNET_CLI_TELEMETRY_OPTOUT = 1
$env:DOTNET_MULTILEVEL_LOOKUP = 0
$env:DOTNET_SKIP_FIRST_TIME_EXPERIENCE = 1

$DotNetInstallScript = New-TemporaryFile | Rename-Item -NewName { $_.Name + ".ps1" } -PassThru
$DotNetExe = Join-Path -Path $DotNetInstallDirectory -ChildPath "dotnet.exe"
Invoke-WebRequest -Uri "https://dot.net/v1/dotnet-install.ps1" -OutFile $DotNetInstallScript -UseBasicParsing
New-Item -Path $DotNetInstallDirectory -Force -ItemType "Directory" | Out-Null

& $DotNetInstallScript -Channel 5.0 -Version latest -InstallDir $DotNetInstallDirectory

if ($LastExitCode -ne 0) {
  throw "'dotnet-install' failed"
}

& $DotNetExe --info

if ($LastExitCode -ne 0) {
  throw "'dotnet' failed"
}

& cmake --version

if ($LastExitCode -ne 0) {
  throw "'cmake' failed"
}

$RepoRoot = Join-Path -Path $PSScriptRoot -ChildPath ".."

echo "Machine setup completed."
