@echo off
setlocal enabledelayedexpansion

REM 修正版バッチ処理スクリプト - 解凍場所の問題を解決

REM 設定
set SOURCE_DIR=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01
set RENDER_DIR=C:\Users\Putoshi\Downloads\st_render5.2_cppRelease\st_render5.2_cppRelease
set OUTPUT_DIR=%RENDER_DIR%\output
set COLOR=2

echo ====================================
echo Himawari8 HSD Batch Processing (Fixed)
echo ====================================
echo.
echo Source: %SOURCE_DIR%
echo Render: %RENDER_DIR%
echo Output: %OUTPUT_DIR%
echo Color scale: %COLOR%
echo.

REM 出力ディレクトリの作成
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

REM 作業ディレクトリに移動
cd /d "%RENDER_DIR%"

REM 処理カウンタ
set /a count=0
set /a success=0
set /a errors=0

REM .DAT.bz2ファイルを処理
echo Processing .DAT.bz2 files...
echo.

for %%F in ("%SOURCE_DIR%\*.DAT.bz2") do (
    set /a count+=1
    echo [!count!] Processing: %%~nxF
    
    REM bz2ファイルを作業ディレクトリにコピー
    echo    Copying to work directory...
    copy "%%F" "%%~nxF" >nul
    
    REM 処理実行
    st_render5_cpp.exe hsdfile file "%%~nxF" color %COLOR% outpic "%OUTPUT_DIR%\%%~nF.png"
    
    if !errorlevel! equ 0 (
        set /a success+=1
        echo    SUCCESS: %%~nF.png created
        
        REM 作業ファイルのクリーンアップ
        if exist "%%~nxF" del "%%~nxF" >nul
        if exist "%%~nF" del "%%~nF" >nul
    ) else (
        set /a errors+=1
        echo    ERROR: Failed to process %%~nxF
        echo    Check if 7z.exe and 7z.dll are in the same directory
    )
    echo.
)

REM .DATファイルを処理（もしあれば）
for %%F in ("%SOURCE_DIR%\*.DAT") do (
    set /a count+=1
    echo [!count!] Processing: %%~nxF
    
    REM DATファイルを作業ディレクトリにコピー
    copy "%%F" "%%~nxF" >nul
    
    st_render5_cpp.exe hsdfile file "%%~nxF" color %COLOR% outpic "%OUTPUT_DIR%\%%~nxF.png"
    
    if !errorlevel! equ 0 (
        set /a success+=1
        echo    SUCCESS: %%~nxF.png created
        del "%%~nxF" >nul
    ) else (
        set /a errors+=1
        echo    ERROR: Failed to process %%~nxF
    )
    echo.
)

echo ====================================
echo Processing complete!
echo Total files: %count%
echo Success: %success%
echo Errors: %errors%
echo Output files are in: %OUTPUT_DIR%
echo ====================================

REM 残ったファイルのクリーンアップ
echo.
echo Cleaning up temporary files...
del *.DAT 2>nul
del *.DAT.bz2 2>nul

pause