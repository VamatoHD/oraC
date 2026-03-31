@echo off
REM Configura o ambiente de construção e execução para o projeto CMake
REM Certifique-se de que o CMake esteja instalado e disponível no PATH
SET BUILD_DIR=build
SET EXE_NAME=MyApplication.exe

echo [1/3] A configurar CMake...
cmake -S . -B %BUILD_DIR%
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ Configuracao do CMake falhou!
    pause
    exit /b %ERRORLEVEL%
)

echo [2/3] A construir projeto...
cmake --build %BUILD_DIR%
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ❌ A construcao do projeto falhou!
    pause
    exit /b %ERRORLEVEL%
)

echo [3/3] A executar %EXE_NAME%...
echo ---------------------------------------
if exist %BUILD_DIR%\Debug\%EXE_NAME% (
    %BUILD_DIR%\Debug\%EXE_NAME%
) else if exist %BUILD_DIR%\Release\%EXE_NAME% (
    %BUILD_DIR%\Release\%EXE_NAME%
) else (
    echo ❌ Executavel %EXE_NAME% nao encontrado!
)

echo ---------------------------------------
echo Execucao concluida.
pause