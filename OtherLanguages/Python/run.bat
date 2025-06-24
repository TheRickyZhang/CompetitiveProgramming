@echo off
setlocal enabledelayedexpansion

:: Check if a filename was provided
if "%~1"=="" (
    echo Usage: run filename
    exit /b 1
)

:: Attempt to locate the file; if no extension, append .py
set "FILE=%~1"
if not exist "%FILE%" (
    set "FILE=%FILE%.py"
)

if not exist "%FILE%" (
    echo Error: File "%~1" not found.
    exit /b 1
)

:: Just run the Python file directly
python "%FILE%"

endlocal
