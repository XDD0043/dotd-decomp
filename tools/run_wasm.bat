@echo off
rem run_wasm.bat - serves the web build (build\wasm) on http://localhost:8080/ and opens it in the browser.
rem The game's files are read from your USRDIR as they are (the usrdir of dotd.ini, DOTD_USRDIR,
rem or: run_wasm.bat --usrdir PATH). Keyboard and gamepad as in the native build. Close this window to stop.
setlocal
set "WEB=%~dp0..\build\wasm"
if not exist "%WEB%\dotd.wasm" (
    echo dotd.wasm not found. Run build_wasm.bat first.
    pause
    exit /b 1
)
start "" /b cmd /c "timeout /t 2 /nobreak >nul & start http://localhost:8080/"
python "%WEB%\serve.py" --port 8080 %*
pause
