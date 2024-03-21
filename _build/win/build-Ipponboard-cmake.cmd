@echo off
setlocal
call %~dp0init_env_cfg.cmd  || exit /b %errorlevel%

SET CONFIG=Release
if not "%1"=="" SET CONFIG=%1

if "%2"=="clean" SET CLEAN=--clean-first

:: Create makefiles
cmake -S "%IPPONBOARD_ROOT_DIR%\base" -B "%IPPONBOARD_ROOT_DIR%\_build\build-Ipponboard" -G "Visual Studio 17 2022" -A Win32 || exit /b %errorlevel%

:: Build Release
cmake --build "%IPPONBOARD_ROOT_DIR%\_build\build-Ipponboard" --config %CONFIG% %CLEAN%
::--clean-first