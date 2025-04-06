@echo off
setlocal enabledelayedexpansion

rem Process only *.cpp files in the current directory.
if "%~1"=="" (
    for %%F in (*.cpp) do call :process "%%F"
    goto :eof
) else (
    set "prefix=%~1"
    set "dest=Codeforces\%prefix%"
    if not exist "%dest%" mkdir "%dest%"
    move /y "%prefix%*.cpp" "%dest%"
    goto :eof
)

:process
set "file=%~1"
set "name=%~n1"

rem USACO: if name starts with Bronze, Silver, Gold, or Platinum
echo !name! | findstr /R /I "^Bronze ^Silver ^Gold ^Platinum" >nul
if not errorlevel 1 (
    if not exist "USACO" mkdir "USACO"
    move /y "%~1" "USACO"
    goto :eof
)

rem Codeforces: if name starts with exactly 3, 4, or 6 digits then a letter.
echo !name! | findstr /R /I "^[0-9][0-9][0-9][A-Za-z]" >nul && goto codeforces
echo !name! | findstr /R /I "^[0-9][0-9][0-9][0-9][A-Za-z]" >nul && goto codeforces
echo !name! | findstr /R /I "^[0-9][0-9][0-9][0-9][0-9][0-9][A-Za-z]" >nul && goto codeforces
goto checkcses

:codeforces
if not exist "Codeforces" mkdir "Codeforces"
move /y "%~1" "Codeforces"
goto :eof

:checkcses
echo !name! | findstr /C:"-" >nul
if not errorlevel 1 (
    if not exist "CSES" mkdir "CSES"
    move /y "%~1" "CSES"
)
goto :eof
