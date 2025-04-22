@echo off
setlocal enabledelayedexpansion

echo Compiling .cpp files...

REM Create build directory if it does not exist
if not exist "build" (
    mkdir "build"
)

REM Compile all .cpp files from src/ to object files in build/
for %%f in (src\*.cpp) do (
    echo Compiling %%f...
    g++ -c "%%f" -I"include" -o "build\%%~nf.o"
)

echo Linking object files...
g++ "build\*.o" -o "bin\app.exe" -L"lib" -lallegro -lallegro_image -lallegro_dialog

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful. Executable generated at bin\app.exe
    echo Launching application...
    start /B bin/app.exe
) else (
    echo There were errors in the compilation.
    pause
)

endlocal