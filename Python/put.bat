@echo off
setlocal enabledelayedexpansion

rem If no argument is provided, process all *.py files in the current directory.
if "%~1"=="" (
    for %%F in (*.py) do call :process "%%F"
    goto :eof
) else (
    set "prefix=%~1"
    set "dest=Codeforces\%prefix%"
    if not exist "%dest%" mkdir "%dest%"
    move /y "%prefix%*.py" "%dest%"
    goto :eof
)

:process
set "file=%~1"
set "name=%~n1"

rem Check if the file is a template.
echo !name! | findstr /R /I "^template" >nul
if errorlevel 1 (
    rem If not a template, move it to Codeforces.
    if not exist "Codeforces" mkdir "Codeforces"
    move /y "%~1" "Codeforces"
) else (
    rem Skip template files.
    echo Skipping template file: %~1
)
goto :eof
