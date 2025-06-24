@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem - clear out executables in the cmake directory
if exist "*.exe" (
    echo Clearing executables
    del /Q "*.exe"
)
if exist "cmake-build-debug\*.exe" (
    echo Clearing executables in cmake-build-debug
    del /Q "cmake-build-debug\*.exe"
)


rem —––––––––––––––––––––––––––––––––––––
rem List of excluded basenames, space-separated
set "EXCLUDE=Template.cpp Checker.cpp"

rem ————————————————
rem No‑arg: process every .cpp via :process
if "%~1"=="" (
    for %%F in (*.cpp) do (
        set "skip=0"
        for %%E in (%EXCLUDE%) do (
          if /I "%%~nxF"=="%%E" set "skip=1"
        )
        if "!skip!"=="0" (
          call :process "%%F"
        ) else (
          echo [skip] %%~nxF
        )
    )
    goto :eof
)

rem ————————————————
rem One‑arg: move all %prefix%*.cpp into the proper Codeforces subfolder
set "prefix=%~1"

rem compute 50‑range
set /a start=(prefix/50)*50
set /a end=start+49
set "rangeFolder=%start%-%end%"

rem target dir: Codeforces\start-end\prefix
set "contestDir=Codeforces\%rangeFolder%\%prefix%"

rem mkdir -p equivalent
mkdir "%contestDir%" 2>nul

rem move the files
move /y "%prefix%*.cpp" "%contestDir%" >nul
if errorlevel 1 (
    echo [err] No files matching "%prefix%*.cpp"
) else (
    echo [success] Moved "%prefix%*.cpp" to "%contestDir%"
)
goto :eof


:process
rem %~1 = full filename, %~n1 = basename
set "file=%~1"
set "name=%~n1"

rem — USACO: Bronze/Silver/Gold/Platinum*
echo !name! | findstr /R /C:"^Bronze" /C:"^Silver" /C:"^Gold" /C:"^Platinum" >nul
if not errorlevel 1 (
    mkdir "USACO" 2>nul
    move /y "%file%" "USACO" >nul
    echo [USACO] Moved "%file%" → USACO
    goto :eof
)

rem — Codeforces: 3‑ or 4‑digit contest ID + letter (e.g. 123A or 2087B)
echo !name! | findstr /R /C:"^[0-9][0-9][0-9][A-Za-z]" /C:"^[0-9][0-9][0-9][0-9][A-Za-z]" >nul
if not errorlevel 1 (
    mkdir "Codeforces" 2>nul
    move /y "%file%" "Codeforces" >nul
    echo [CF] Moved "%file%" → Codeforces
    goto :eof
)

rem — CSES: any dash in the basename
echo !name! | findstr /C:"-" >nul
if not errorlevel 1 (
    mkdir "CSES" 2>nul
    move /y "%file%" "CSES" >nul
    echo [CSES] Moved "%file%" → CSES
)

goto :eof
