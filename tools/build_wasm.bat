@echo off
rem build_wasm.bat - builds the web version of dotd (wasm32 + WebGL2) with the Emscripten SDK (web\README.md).
rem The SDK is taken from EMSDK when it is set, otherwise from toolchain\emsdk in this checkout (git-ignored):
rem   git clone https://github.com/emscripten-core/emsdk toolchain\emsdk, then emsdk install latest, emsdk activate latest.
rem Output: build\wasm\ (dotd.js, dotd.wasm, index.html, serve.py). Then: run_wasm.bat.
rem Extra arguments go to "cmake --build" (for example: -- -k 0 to keep going after errors).
setlocal
for %%I in ("%~dp0..") do set "ROOT=%%~fI"
if not defined EMSDK set "EMSDK=%ROOT%\toolchain\emsdk"
set "EMSDK_WIN=%EMSDK:/=\%"
if not exist "%EMSDK_WIN%\upstream\emscripten\emcc.py" (
    echo Emscripten not found in %EMSDK_WIN%. See web\README.md.
    goto :fail
)
rem The environment emsdk_env.bat would set (the wasm preset's toolchain file path uses EMSDK).
set "EMSDK=%EMSDK_WIN:\=/%"
set "EM_CONFIG=%EMSDK_WIN%\.emscripten"
for /d %%D in ("%EMSDK_WIN%\node\*") do set "EMSDK_NODE=%%D\node.exe"
for /d %%D in ("%EMSDK_WIN%\python\*") do set "EMSDK_PYTHON=%%D\python.exe"
set "PATH=%EMSDK_WIN%\upstream\emscripten;%PATH%"
cd /d "%ROOT%"
if not exist build\wasm\build.ninja (
    cmake --preset wasm %DOTD_WASM_CMAKE_ARGS% || goto :fail
)
cmake --build build\wasm --target dotd %* || goto :fail
echo.
echo Built: %ROOT%\build\wasm
pause
exit /b 0
:fail
echo.
echo Build failed.
pause
exit /b 1
