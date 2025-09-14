@echo off
REM シンプルなバッチ処理 - runstrender.batがある場所にコピーして使用

setlocal enabledelayedexpansion

REM 処理したいフォルダを指定（変更してください）
set SOURCE_FOLDER=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01
set COLOR=2

echo Processing all files in: %SOURCE_FOLDER%
echo Color scale: %COLOR%
echo.

set /a count=0

REM .DATファイルを処理
for %%F in ("%SOURCE_FOLDER%\*.DAT") do (
    set /a count+=1
    echo [!count!] %%~nxF
    st_render5_cpp.exe hsdfile file "%%F" color %COLOR%
)

REM .DAT.bz2ファイルを処理
for %%F in ("%SOURCE_FOLDER%\*.DAT.bz2") do (
    set /a count+=1
    echo [!count!] %%~nxF
    st_render5_cpp.exe hsdfile file "%%F" color %COLOR%
)

echo.
echo Complete! Processed %count% files.
pause