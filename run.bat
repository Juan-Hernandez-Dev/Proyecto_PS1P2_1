@echo off
setlocal

if not exist build\ (
    mkdir build
)

:: Configuración
g++ -Iinclude include/utils.cpp main.cpp -o build/blackjack.exe

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ¡Compilación exitosa!
    echo.
    build\blackjack.exe
) else (
    echo.
    echo Error en la compilación.
)