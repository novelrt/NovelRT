@ECHO OFF
pwsh -NoLogo -NoProfile -ExecutionPolicy ByPass -Command "& """%~dp0machine-setup.ps1""" %*"
EXIT /B %ERRORLEVEL%
