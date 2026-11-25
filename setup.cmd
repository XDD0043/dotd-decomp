@echo off
rem One-click setup of the Dawn of the Dragon port: builds dotd.exe and points it at your copy of the game.
rem Double-click it, or run "setup.cmd -GamePath D:\Games\DotD" (setup.ps1 lists the options).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0setup.ps1" %*
