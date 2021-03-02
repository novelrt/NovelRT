@ECHO OFF
pwsh -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0scripts\build.ps1""" -build %*"
EXIT /B %ERRORLEVEL%
