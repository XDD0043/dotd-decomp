@echo off
rem run_release.bat - starts the latest MSVC Release x64 build (build\windows-msvc\Release\dotd.exe).
rem Keyboard = RPCS3's default pad layout (Enter START, X Cross, C Circle, Z Square, V Triangle, WASD move,
rem arrows d-pad, Q/E L1/R1, R/T L2/R2, Space Select); a gamepad works too.
setlocal
set "EXE=%~dp0..\build\windows-msvc\Release\dotd.exe"
if not exist "%EXE%" (
    echo dotd.exe not found. Run build_release.bat first.
    pause
    exit /b 1
)
for %%I in ("%EXE%") do echo Starting %%~fI  (built %%~tI)
start "Dawn of the Dragon" /D "%~dp0..\build\windows-msvc\Release" "%EXE%" %*
