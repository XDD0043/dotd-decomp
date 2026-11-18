@echo off
rem run_wasm_download.bat - serves the site folder (build\site, made by pack_wasm.bat) on http://localhost:8081/
rem the way a static web host would, and opens it in the browser: nothing is read from your game folder; the game's
rem files are downloaded, stored in the browser and fetched ahead level by level.
rem The folder is brought up to date with the web build first (quick when the pack did not change).
rem Add --rate 50 to send the data over one 50 Mbit/s connection (to see the real waits), --no-range to answer
rem like a host without range requests. Close this window to stop.
setlocal
if not exist "%~dp0..\build\web-data\manifest.json" (
    echo No pack in build\web-data. Run pack_wasm.bat first.
    pause
    exit /b 1
)
python "%~dp0..\web\make_site.py"
if errorlevel 1 (
    pause
    exit /b 1
)
start "" /b cmd /c "timeout /t 2 /nobreak >nul & start http://localhost:8081/"
python "%~dp0..\web\serve.py" --site "%~dp0..\build\site" --port 8081 %*
pause
