@echo off
setlocal
set "prefix=%~1"
if "%prefix%"=="" exit /b 1

set "dest=C:\Codesforces\%prefix%"
if not exist "%dest%" mkdir "%dest%"
move /y "%prefix%*.cpp" "%dest%"
