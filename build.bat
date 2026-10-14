@echo off
setlocal EnableDelayedExpansion

set "ROOT=%~dp0"
set "BUILD_DIR=%ROOT%build"
set "OUTPUT=%BUILD_DIR%\terminal.exe"
set "SOURCES="

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

for %%F in ("%ROOT%src\*.c") do (
    set "SOURCES=!SOURCES! "%%~fF""
)

if not defined SOURCES (
    echo No C source files found in src.
    exit /b 1
)

gcc -Wall -Wextra -std=c17 -I"%ROOT%include" ^
    !SOURCES! ^
    -o "%OUTPUT%"

if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Build succeeded: %OUTPUT%
echo.
"%OUTPUT%"

endlocal
