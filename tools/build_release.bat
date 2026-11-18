@echo off
rem build_release.bat - builds dotd.exe (MSVC Release x64) from this checkout.
rem Output: build\windows-msvc\Release\dotd.exe. Close the game first, or the link cannot replace the exe.
rem Needs Visual Studio with the C++ tools, CMake 3.25+ and Ninja. Run it from anywhere; a developer prompt is found
rem with vswhere when this is not one already.
setlocal
if defined VSCMD_VER goto :have_vs
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    pushd "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
    for /f "delims=" %%I in ('.\vswhere.exe -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath') do set "DOTD_VS=%%I"
    popd
)
if not defined DOTD_VS (
    echo Visual Studio with the C++ tools was not found. Run this from an x64 developer command prompt.
    goto :fail
)
call "%DOTD_VS%\VC\Auxiliary\Build\vcvars64.bat" >nul || goto :fail
:have_vs
cd /d "%~dp0.."
if not exist "build\windows-msvc\CMakeCache.txt" cmake --preset windows-msvc -DDOTD_SDL_DIR="%CD%\thirdparty\SDL" -DDOTD_FFMPEG_DIR="%CD%\thirdparty\ffmpeg" || goto :fail
cmake --build --preset windows-msvc-release --target dotd || goto :fail
echo.
echo Built: %CD%\build\windows-msvc\Release\dotd.exe
pause
exit /b 0
:fail
echo.
echo Build failed. If the link failed, check that dotd.exe is not still running.
pause
exit /b 1
