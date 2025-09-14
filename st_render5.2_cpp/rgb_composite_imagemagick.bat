@echo off
setlocal enabledelayedexpansion

REM ImageMagick用RGB合成スクリプト
REM 事前にImageMagickのインストールが必要

echo ====================================
echo Himawari-8 RGB Composite with ImageMagick
echo ====================================

set SOURCE_DIR=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01
set WORK_DIR=C:\Users\Putoshi\Downloads\st_render5.2_cppRelease\st_render5.2_cppRelease
set OUTPUT_DIR=%WORK_DIR%\rgb_composites

REM ImageMagickの確認
where magick >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: ImageMagick not found!
    echo Please install from: https://imagemagick.org/
    pause
    exit /b
)

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"
cd /d "%WORK_DIR%"

echo.
echo Available RGB recipes:
echo 1. True Color (Natural appearance)
echo 2. Day Microphysics (Cloud analysis)
echo 3. Airmass (Weather patterns)
echo 4. Dust (Yellow dust detection)
echo.
set /p RECIPE="Select recipe (1-4): "

REM 時刻情報を取得（ファイル名から）
set TIME_STAMP=
for %%F in ("%SOURCE_DIR%\*_B01_*.DAT.bz2") do (
    set FILENAME=%%~nF
    set TIME_STAMP=!FILENAME:~6,12!
)

if "%RECIPE%"=="1" (
    REM True Color: B03(R) B02(G) B01(B)
    call :ProcessBand 03 red
    call :ProcessBand 02 green
    call :ProcessBand 01 blue
    
    echo Creating True Color composite...
    magick ^
        "%OUTPUT_DIR%\band_03.png" ^
        "%OUTPUT_DIR%\band_02.png" ^
        "%OUTPUT_DIR%\band_01.png" ^
        -gamma 0.5 ^
        -combine ^
        -quality 95 ^
        "%OUTPUT_DIR%\TrueColor_%TIME_STAMP%.png"
    
) else if "%RECIPE%"=="2" (
    REM Day Microphysics: B04(R) B07(G) B13(B)
    call :ProcessBand 04 red
    call :ProcessBand 07 green
    call :ProcessBand 13 blue
    
    echo Creating Day Microphysics composite...
    magick ^
        "%OUTPUT_DIR%\band_04.png" -gamma 0.5 ^
        "%OUTPUT_DIR%\band_07.png" -negate ^
        "%OUTPUT_DIR%\band_13.png" -negate ^
        -combine ^
        -quality 95 ^
        "%OUTPUT_DIR%\DayMicrophysics_%TIME_STAMP%.png"
    
) else if "%RECIPE%"=="3" (
    REM Airmass: 複雑な処理が必要
    echo Airmass RGB requires band differences (not implemented)
    echo Processing basic version with B08, B12, B05...
    call :ProcessBand 08 red
    call :ProcessBand 12 green  
    call :ProcessBand 05 blue
    
) else if "%RECIPE%"=="4" (
    REM Dust RGB
    call :ProcessBand 15 red
    call :ProcessBand 13 green
    call :ProcessBand 11 blue
    
    echo Creating Dust RGB composite...
    echo This requires temperature difference calculations
)

echo.
echo ====================================
echo Processing complete!
echo Output directory: %OUTPUT_DIR%
echo ====================================
pause
exit /b

:ProcessBand
REM サブルーチン: 指定バンドを処理
set BAND=%1
set CHANNEL=%2

for %%F in ("%SOURCE_DIR%\*_B%BAND%_*.DAT.bz2") do (
    echo Processing Band %BAND% for %CHANNEL% channel...
    copy "%%F" temp_%BAND%.bz2 >nul
    st_render5_cpp.exe hsdfile file temp_%BAND%.bz2 color 0 outpic "%OUTPUT_DIR%\band_%BAND%.png"
    del temp_%BAND%.bz2 >nul
    del temp_%BAND%.DAT 2>nul
)
exit /b