@echo off
echo ====================================
echo Environment Check for st_render5_cpp
echo ====================================
echo.

echo Current directory:
cd
echo.

echo Checking required files:
echo -----------------------
if exist st_render5_cpp.exe (
    echo [OK] st_render5_cpp.exe found
) else (
    echo [ERROR] st_render5_cpp.exe NOT FOUND
)

if exist 7z.exe (
    echo [OK] 7z.exe found
) else (
    echo [ERROR] 7z.exe NOT FOUND - Required for bz2 extraction
)

if exist 7z.dll (
    echo [OK] 7z.dll found
) else (
    echo [ERROR] 7z.dll NOT FOUND - Required for bz2 extraction
)

echo.
echo Testing with a sample file:
echo --------------------------
set TEST_FILE=C:\Users\Putoshi\Downloads\HS_H08_20170623_0250_JP01\HS_H08_20170623_0250_B03_JP01_R05_S0101.DAT.bz2

if exist "%TEST_FILE%" (
    echo Test file: %TEST_FILE%
    echo.
    
    REM Copy test file to current directory
    copy "%TEST_FILE%" test.DAT.bz2 >nul
    
    echo 1. Testing 7z extraction manually:
    7z e test.DAT.bz2 -y
    echo.
    
    if exist test.DAT (
        echo [OK] Manual extraction successful
        echo.
        
        echo 2. Testing st_render5_cpp with extracted DAT:
        st_render5_cpp.exe hsdfile file test.DAT color 2 outpic test_output.png
        
        if exist test_output.png (
            echo [OK] PNG generation successful
        ) else (
            echo [ERROR] PNG generation failed
        )
        
        REM Cleanup
        del test.DAT >nul
        del test_output.png 2>nul
    ) else (
        echo [ERROR] Manual extraction failed
    )
    
    del test.DAT.bz2 >nul
) else (
    echo [ERROR] Test file not found: %TEST_FILE%
)

echo.
echo ====================================
pause