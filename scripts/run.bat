@echo off
color 03
echo This script was made by @smvax.
timeout /t 2 /nobreak >nul
cls
color 0A

:: Переход в корень проекта (на один уровень вверх из папки scripts)
cd ..

:: Удаление старой папки Build в корне проекта, если она существует
if exist "Build" (
    echo [INFO] Removing old Build directory...
    rmdir /s /q "Build"
)

:: Создание новой папки Build
echo [INFO] Creating new Build directory...
mkdir Build

cd Build
echo [INFO] Creating CMake configuration...
cmake -G "Visual Studio 17 2022" ..

if %errorlevel% equ 0 (
    echo [INFO] CMake configured successfully! Opening solution...
    
    :: Поиск и открытие файла решения .sln
    for %%f in (*.sln) do (
        start "" "%%f"
        goto :success
    )
    echo [ERROR] CMake finished successfully, but no .sln file was found.
) else (
    echo [ERROR] CMake configuration failed.
    pause
)

:success

