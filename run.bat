@echo off
setlocal EnableExtensions
cd /d "%~dp0"

title Student Performance Analysis System

echo ================================================
echo   Student Performance Analysis System
echo ================================================
echo.

REM Stop older copies so the browser never connects to stale code.
taskkill /IM student_system.exe /F >nul 2>&1

if not exist build mkdir build

echo [1/3] Building C backend...
gcc backend\*.c -std=c99 -Wall -Wextra -O2 -o build\student_system.exe -lws2_32
if errorlevel 1 (
    echo.
    echo Build failed.
    echo Make sure MinGW-w64 GCC is installed and GCC is in PATH.
    pause
    exit /b 1
)

echo [2/3] Starting C HTTP server...
start "SPAS C Backend" /D "%~dp0" cmd /k ""%~dp0build\student_system.exe""

timeout /t 2 /nobreak >nul

echo [3/3] Opening dashboard...
start "" "http://localhost:8080/dashboard"

echo.
echo Dashboard: http://localhost:8080/dashboard
echo.
echo Keep the C Backend window open while using the website.
echo Close that window to stop the server.
echo.
endlocal
