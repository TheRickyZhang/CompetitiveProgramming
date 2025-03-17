@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Usage: run filename
    exit /b 1
)

rem Attempt to locate the file; if no extension, append .cpp
set "FILE=%~1"
if not exist "%FILE%" (
    set "FILE=%FILE%.cpp"
)

if not exist "%FILE%" (
    echo Error: File "%~1" not found.
    exit /b 1
)

rem Extract name and directory based on the actual file
for %%F in ("%FILE%") do (
    set "NAME=%%~nF"
    set "DIR=%%~dpF"
)

rem Compile the file
g++ "%FILE%" -O2 -std=c++17 -o "%DIR%%NAME%.exe"
if errorlevel 1 (
    echo Compilation failed.
    exit /b 1
)

rem Kill any running instance of the executable
taskkill /IM "%NAME%.exe" /F 2>nul

rem Run the executable (this keeps the terminal open for input)
"%DIR%%NAME%.exe"

rem Delete the executable after execution
del "%DIR%%NAME%.exe"

endlocal
