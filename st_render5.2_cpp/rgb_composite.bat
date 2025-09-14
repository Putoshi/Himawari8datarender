@echo off
setlocal enabledelayedexpansion

REM ひまわり8号 RGB合成バッチスクリプト
REM True Color (B01, B02, B03) の例

echo ====================================
echo Himawari-8 RGB Composite Generator
echo ====================================
echo.

REM 設定
set SOURCE_DIR=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01
set WORK_DIR=C:\Users\Putoshi\Downloads\st_render5.2_cppRelease\st_render5.2_cppRelease
set OUTPUT_DIR=%WORK_DIR%\rgb_output

REM RGB合成タイプを選択
echo Select RGB composite type:
echo 1. True Color (B01 blue, B02 green, B03 red)
echo 2. Natural Color (B01 blue, B03+B04 green, B03 red)
echo 3. Custom (specify bands)
echo.
set /p RGB_TYPE="Enter choice (1-3): "

if "%RGB_TYPE%"=="1" (
    set BAND_R=03
    set BAND_G=02
    set BAND_B=01
    set COMP_NAME=TrueColor
) else if "%RGB_TYPE%"=="2" (
    echo Natural Color requires special processing (not implemented in basic version)
    pause
    exit /b
) else (
    set /p BAND_R="Enter RED band (01-16): "
    set /p BAND_G="Enter GREEN band (01-16): "
    set /p BAND_B="Enter BLUE band (01-16): "
    set COMP_NAME=Custom_B!BAND_R!B!BAND_G!B!BAND_B!
)

echo.
echo RGB Composite: %COMP_NAME%
echo RED: Band %BAND_R%
echo GREEN: Band %BAND_G%
echo BLUE: Band %BAND_B%
echo.

REM 出力ディレクトリ作成
if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

REM 作業ディレクトリに移動
cd /d "%WORK_DIR%"

REM 各バンドの画像を生成
echo Generating individual band images...
echo.

REM 赤チャンネル (Band BAND_R)
set RED_FILE=
for %%F in ("%SOURCE_DIR%\*_B%BAND_R%_*.DAT.bz2") do (
    echo Processing RED channel: %%~nxF
    copy "%%F" temp_red.bz2 >nul
    st_render5_cpp.exe hsdfile file temp_red.bz2 color 0 outpic "%OUTPUT_DIR%\band_%BAND_R%_red.png"
    del temp_red.bz2 >nul
    del temp_red.DAT 2>nul
    set RED_FILE=%OUTPUT_DIR%\band_%BAND_R%_red.png
)

REM 緑チャンネル (Band BAND_G)
set GREEN_FILE=
for %%F in ("%SOURCE_DIR%\*_B%BAND_G%_*.DAT.bz2") do (
    echo Processing GREEN channel: %%~nxF
    copy "%%F" temp_green.bz2 >nul
    st_render5_cpp.exe hsdfile file temp_green.bz2 color 0 outpic "%OUTPUT_DIR%\band_%BAND_G%_green.png"
    del temp_green.bz2 >nul
    del temp_green.DAT 2>nul
    set GREEN_FILE=%OUTPUT_DIR%\band_%BAND_G%_green.png
)

REM 青チャンネル (Band BAND_B)
set BLUE_FILE=
for %%F in ("%SOURCE_DIR%\*_B%BAND_B%_*.DAT.bz2") do (
    echo Processing BLUE channel: %%~nxF
    copy "%%F" temp_blue.bz2 >nul
    st_render5_cpp.exe hsdfile file temp_blue.bz2 color 0 outpic "%OUTPUT_DIR%\band_%BAND_B%_blue.png"
    del temp_blue.bz2 >nul
    del temp_blue.DAT 2>nul
    set BLUE_FILE=%OUTPUT_DIR%\band_%BAND_B%_blue.png
)

echo.
echo ====================================
echo Individual band images created!
echo.
echo To create RGB composite, you need:
echo 1. Image processing software (GIMP, Photoshop, ImageMagick)
echo 2. Combine the three grayscale images as R, G, B channels
echo.
echo Band images saved in: %OUTPUT_DIR%
echo - Red: band_%BAND_R%_red.png
echo - Green: band_%BAND_G%_green.png  
echo - Blue: band_%BAND_B%_blue.png
echo ====================================
echo.

REM ImageMagickがインストールされている場合の自動合成
where magick >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo ImageMagick detected! Creating RGB composite...
    magick "%OUTPUT_DIR%\band_%BAND_R%_red.png" "%OUTPUT_DIR%\band_%BAND_G%_green.png" "%OUTPUT_DIR%\band_%BAND_B%_blue.png" -combine "%OUTPUT_DIR%\%COMP_NAME%_composite.png"
    echo RGB composite saved as: %COMP_NAME%_composite.png
) else (
    echo.
    echo To automatically create RGB composites, install ImageMagick:
    echo https://imagemagick.org/script/download.php#windows
)

pause