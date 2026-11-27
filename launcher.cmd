@echo off
rem The Dawn of the Dragon launcher (launcher.ps1): builds and starts the game, sets the game folder, the graphics
rem options and the keyboard controls. Double-click it.
start "" powershell -NoProfile -ExecutionPolicy Bypass -WindowStyle Hidden -File "%~dp0launcher.ps1"
