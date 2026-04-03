@echo off

SET BUILD_DIR=build

:: Configurar loud flag
set "OUTPUT=>nul 2>&1"
for %%a in (%*) do (
    if /i "%%a"=="-l" (
        set "OUTPUT="
    )
)

echo [1/3] A configurar CMake...
cmake -S . -B %BUILD_DIR% %OUTPUT%
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Configuracao do CMake falhou!
    pause
    exit /b %ERRORLEVEL%
)

echo [2/3] A construir projeto...
cmake --build %BUILD_DIR% %OUTPUT%
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ A construcao do projeto falhou!
    pause
    exit /b %ERRORLEVEL%
)

ctest --test-dir build -C Debug --output-on-failure --verbose