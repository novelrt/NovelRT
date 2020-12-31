@ECHO OFF
powershell.exe -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0ci-generate-diff.ps1"""%*"
EXIT /B %ERRORLEVEL%
