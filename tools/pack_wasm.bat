@echo off
rem pack_wasm.bat - makes the folder a static web host serves (Netlify, Cloudflare Pages): build\site.
rem Step 1, web\pack.py: packs the game's files into build\web-data (zstd-compressed level data with level-to-level
rem   differences; with an ffmpeg on the PATH, the videos re-encoded as VP9 and the music as Vorbis; your USRDIR is
rem   only read). About 12 minutes for the level data, 55 for the videos, 1 for the music, on all CPU cores; a later
rem   run only adds what is missing. Arguments go to pack.py (--usrdir PATH, --video-crf N, --music-quality N:
rem   0 leaves the videos / the music as they are).
rem Step 2, web\make_site.py: the site folder from the pack and the web build (build_wasm.bat first).
rem Then: run_wasm_download.bat tries the folder here. The site holds the game's data: host it only for yourself.
setlocal
python "%~dp0..\web\pack.py" --out "%~dp0..\build\web-data" %*
if errorlevel 1 goto done
python "%~dp0..\web\make_site.py"
:done
set "RC=%ERRORLEVEL%"
echo.
pause
exit /b %RC%
