@echo off
setlocal enabledelayedexpansion

REM バッチ処理スクリプト - フォルダ内の全HSDファイルを処理

REM 設定
set SOURCE_DIR=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01
set RENDER_DIR=C:\Users\Putoshi\Downloads\st_render5.2_cppRelease\st_render5.2_cppRelease
set COLOR=2

echo ====================================
echo Himawari8 HSD Batch Processing
echo ====================================
echo.
echo Source: %SOURCE_DIR%
echo Render: %RENDER_DIR%
echo Color scale: %COLOR%
echo.

REM 作業ディレクトリに移動
cd /d "%RENDER_DIR%"

REM 処理カウンタ
set /a count=0

REM .DATファイルを処理
echo Processing .DAT files...
for %%F in ("%SOURCE_DIR%\*.DAT") do (
    set /a count+=1
    echo [!count!] Processing: %%~nxF
    st_render5_cpp.exe hsdfile file "%%F" color %COLOR%
)

REM .DAT.bz2ファイルを処理
echo.
echo Processing .DAT.bz2 files...
for %%F in ("%SOURCE_DIR%\*.DAT.bz2") do (
    set /a count+=1
    echo [!count!] Processing: %%~nxF
    st_render5_cpp.exe hsdfile file "%%F" color %COLOR%
)

echo.
echo ====================================
echo Processing complete!
echo Total files processed: %count%
echo Output files are in: %RENDER_DIR%
echo ====================================

pause