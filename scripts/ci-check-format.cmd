@ECHO OFF
powershell.exe -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0ci-check-format.ps1"""%*"
EXIT /B %ERRORLEVEL%
