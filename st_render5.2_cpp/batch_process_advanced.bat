@echo off
setlocal enabledelayedexpansion

REM 高度なバッチ処理スクリプト - 出力フォルダ指定、色選択、エラー処理付き

REM デフォルト設定
set SOURCE_DIR=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01
set RENDER_DIR=C:\Users\Putoshi\Downloads\st_render5.2_cppRelease\st_render5.2_cppRelease
set OUTPUT_DIR=%RENDER_DIR%\output
set COLOR=2

REM コマンドライン引数の処理
if not "%1"=="" set SOURCE_DIR=%1
if not "%2"=="" set COLOR=%2
if not "%3"=="" set OUTPUT_DIR=%3

echo ====================================
echo Himawari8 HSD Advanced Batch Processing
echo ====================================
echo.
echo Source directory: %SOURCE_DIR%
echo Render directory: %RENDER_DIR%
echo Output directory: %OUTPUT_DIR%
echo Color scale: %COLOR% (0=BW, 1=BD, 2=Color2, 3=WV)
echo.

REM ソースディレクトリの確認
if not exist "%SOURCE_DIR%" (
    echo Error: Source directory not found!
    echo %SOURCE_DIR%
    goto :error
)

REM 実行ファイルの確認
if not exist "%RENDER_DIR%\st_render5_cpp.exe" (
    echo Error: st_render5_cpp.exe not found in %RENDER_DIR%
    goto :error
)

REM 出力ディレクトリの作成
if not exist "%OUTPUT_DIR%" (
    echo Creating output directory...
    mkdir "%OUTPUT_DIR%"
)

REM 作業ディレクトリに移動
cd /d "%RENDER_DIR%"

REM 処理カウンタ
set /a count=0
set /a errors=0

REM ログファイル
set LOG_FILE=%OUTPUT_DIR%\processing_log.txt
echo Processing started at %date% %time% > "%LOG_FILE%"
echo. >> "%LOG_FILE%"

REM .DATファイルを処理
echo Processing .DAT files...
for %%F in ("%SOURCE_DIR%\*.DAT") do (
    set /a count+=1
    echo [!count!] Processing: %%~nxF
    echo [!count!] Processing: %%~nxF >> "%LOG_FILE%"
    
    st_render5_cpp.exe hsdfile file "%%F" color %COLOR% outpic "%OUTPUT_DIR%\%%~nF.png"
    
    if !errorlevel! neq 0 (
        set /a errors+=1
        echo    ERROR: Failed to process %%~nxF
        echo    ERROR: Failed to process %%~nxF >> "%LOG_FILE%"
    ) else (
        echo    SUCCESS: %%~nF.png created
        echo    SUCCESS: %%~nF.png created >> "%LOG_FILE%"
    )
)

REM .DAT.bz2ファイルを処理
echo.
echo Processing .DAT.bz2 files...
for %%F in ("%SOURCE_DIR%\*.DAT.bz2") do (
    set /a count+=1
    echo [!count!] Processing: %%~nxF
    echo [!count!] Processing: %%~nxF >> "%LOG_FILE%"
    
    REM .bz2を除いたファイル名を取得
    set "filename=%%~nF"
    
    st_render5_cpp.exe hsdfile file "%%F" color %COLOR% outpic "%OUTPUT_DIR%\!filename!.png"
    
    if !errorlevel! neq 0 (
        set /a errors+=1
        echo    ERROR: Failed to process %%~nxF
        echo    ERROR: Failed to process %%~nxF >> "%LOG_FILE%"
    ) else (
        echo    SUCCESS: !filename!.png created
        echo    SUCCESS: !filename!.png created >> "%LOG_FILE%"
    )
)

echo. >> "%LOG_FILE%"
echo Processing completed at %date% %time% >> "%LOG_FILE%"
echo Total files: %count%, Errors: %errors% >> "%LOG_FILE%"

echo.
echo ====================================
echo Processing complete!
echo Total files processed: %count%
echo Errors: %errors%
echo Output files are in: %OUTPUT_DIR%
echo Log file: %LOG_FILE%
echo ====================================

goto :end

:error
echo.
echo Press any key to exit...
pause >nul
exit /b 1

:end
pause