@ECHO OFF
pwsh -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0scripts\build.ps1""" -install %*"
EXIT /B %ERRORLEVEL%
