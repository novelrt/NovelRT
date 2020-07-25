# NOTE: DO NOT RUN THIS ON DEVELOPMENT MACHINES!
# This is intended for setting up CI machines with the correct dependencies.

$VcpkgInstallDirectory = Join-Path -Path $HOME -ChildPath "vcpkg"
$DotNetInstallDirectory = Join-Path -Path $HOME -ChildPath "dotnet"

if (!(Get-Command python -ErrorAction SilentlyContinue ))
{
  $PythonInstaller = New-TemporaryFile | Rename-Item -NewName { $_.Name + ".exe" } - PassThru
  Invoke-WebRequest -Uri "https://www.python.org/ftp/python/3.8.3/python-3.8.3.exe" -OutFile $PythonInstaller

  & $PythonInstaller /quiet InstallAllUsers=0 PrependPath=1 Include_test=0

  if ($LastExitCode -ne 0) {
    throw "'python-3.8.3' failed"
  }
}

& python -m pip --version
& python -m pip install setuptools
& python -m pip install glad

if ($LastExitCode -ne 0) {
  throw "'pip install' failed"
}

if (!(Test-Path -Path $VcpkgInstallDirectory)) {
  & git clone https://github.com/capnkenny/vcpkg $VcpkgInstallDirectory
}

$VcpkgExe = Join-Path -Path $VcpkgInstallDirectory -ChildPath "vcpkg.exe"

if (!(Test-Path -Path $VcpkgExe)) {
  & $VcpkgInstallDirectory/bootstrap-vcpkg.bat

  if ($LastExitCode -ne 0) {
    throw "'bootstrap-vcpkg' failed"
  }
}

& $VcpkgExe install freetype glfw3 glm gtest libsndfile lua openal-soft spdlog --triplet x64-windows

if ($LastExitCode -ne 0) {
    throw "'vcpkg install' failed"
}

$env:DOTNET_CLI_TELEMETRY_OPTOUT = 1
$env:DOTNET_MULTILEVEL_LOOKUP = 0
$env:DOTNET_SKIP_FIRST_TIME_EXPERIENCE = 1

$DotNetInstallScript = New-TemporaryFile | Rename-Item -NewName { $_.Name + ".ps1" } -PassThru
$DotNetExe = Join-Path -Path $DotNetInstallDirectory -ChildPath "dotnet.exe"
Invoke-WebRequest -Uri "https://dot.net/v1/dotnet-install.ps1" -OutFile $DotNetInstallScript -UseBasicParsing
New-Item -Path $DotNetInstallDirectory -Force -ItemType "Directory" | Out-Null

& $DotNetInstallScript -Channel 3.1 -Version latest -InstallDir $DotNetInstallDirectory
& $DotNetInstallScript -Channel 2.1 -Version latest -InstallDir $DotNetInstallDirectory -Runtime dotnet

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
