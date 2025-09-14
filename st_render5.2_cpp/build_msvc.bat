@echo off
REM Direct MSVC build script for st_render5_cpp

set NETCDF_PATH=C:\Program Files\netCDF 4.9.3

echo Compiling with MSVC...

cl /c /O2 /EHsc /MD /I"%NETCDF_PATH%\include" main.cpp st_render.cpp colorscale.cpp lodepng.cpp others.cpp

echo Linking...

link /OUT:st_render5_cpp.exe main.obj st_render.obj colorscale.obj lodepng.obj others.obj ^
     /LIBPATH:"%NETCDF_PATH%\lib" netcdf.lib urlmon.lib

echo Build complete!

del *.obj 2>NUL