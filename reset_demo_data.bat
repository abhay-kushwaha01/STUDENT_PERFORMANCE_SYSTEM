@echo off
setlocal
cd /d "%~dp0"
echo Resetting Student Performance Analysis System demo data...
del /q data\students.dat data\marks.dat data\attendance.dat 2>nul
echo Demo data files removed.
echo Start run.bat to recreate the 40-student demo dataset.
pause
endlocal
