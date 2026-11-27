@echo off
setlocal
title Dawn of the Dragon - launch.cmd
set "DOTD_LAUNCH_DIR=%~dp0"
if not exist "%DOTD_LAUNCH_DIR%dotd.exe" (
    set "DOTD_LAUNCH_DIR=%~dp0build\windows-msvc\Release\"
)
if not exist "%DOTD_LAUNCH_DIR%dotd.exe" (
    echo Release build not found. Build it with launcher.cmd first.
    pause
    exit /b 1
)
start "Dawn of the Dragon - Console" /D "%DOTD_LAUNCH_DIR%" "%DOTD_LAUNCH_DIR%dotd.exe" %*
