@echo off
setlocal enabledelayedexpansion

REM Navigate to the source directory
cd /d %~dp0src

REM Create the output directory if it doesn't exist
if not exist ..\output (
    mkdir ..\output
)

REM Initialize the sources variable to an empty string
set sources=

REM Loop through all .c files in the source directory and add them to the sources variable
for %%f in (*.c) do (
    set sources=!sources! %%f
)

REM Add the common.c file to the sources variable
set sources=!sources! ..\..\Common\common.c

REM Compile all .c files in the source directory and specify the include paths for the header and Common directories
gcc -Wall -Wextra -o ..\output\main !sources! -I..\header -I..\..\Common

REM Check if the compilation was successful
if %errorlevel% equ 0 (
    REM Run the compiled executable
    ..\output\main
) else (
    echo Compilation failed.
)

endlocal