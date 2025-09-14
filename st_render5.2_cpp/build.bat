@echo off
REM Build script for st_render5_cpp on Windows
REM Requires Visual Studio Build Tools or MinGW-w64

echo Building st_render5_cpp...

REM Option 1: Build with MSBuild (if Visual Studio installed)
where msbuild >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using MSBuild...
    msbuild st_render5_c.vcxproj /p:Configuration=Release /p:Platform=x64
    goto :end
)

REM Option 2: Build with MinGW-w64
where g++ >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using MinGW-w64...
    mingw32-make -f Makefile.win
    goto :end
)

REM Option 3: Build with MSVC directly
where cl >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using MSVC compiler...
    call build_msvc.bat
    goto :end
)

echo Error: No suitable compiler found!
echo Please install either:
echo   - Visual Studio with C++ support
echo   - MinGW-w64
echo   - MSVC Build Tools

:end
pause