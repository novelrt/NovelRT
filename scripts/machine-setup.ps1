# NOTE: DO NOT RUN THIS ON DEVELOPMENT MACHINES!
# This is intended for setting up CI machines with the correct dependencies.

$ProgressPreference = 'SilentlyContinue'

if (!(Get-Command python -ErrorAction SilentlyContinue ))
{
  $PythonInstaller = New-TemporaryFile | Rename-Item -NewName { $_.Name + ".exe" } -PassThru
  Invoke-WebRequest -Uri "https://www.python.org/ftp/python/3.10.4/python-3.10.4-amd64.exe" -OutFile $PythonInstaller

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

& cmake --version

if ($LastExitCode -ne 0) {
  throw "'cmake' failed"
}

$RepoRoot = Join-Path -Path $PSScriptRoot -ChildPath ".."

echo "Machine setup completed."
