@echo off
echo Building st_render5_cpp without GOES/netCDF support...

cl /c /O2 /EHsc /MD /DWIN32 /DNO_NETCDF main.cpp st_render.cpp colorscale.cpp lodepng.cpp others.cpp

link /OUT:st_render5_cpp_no_netcdf.exe main.obj st_render.obj colorscale.obj lodepng.obj others.obj urlmon.lib

echo Build complete! (HSD only version - no GOES support)

del *.obj 2>NUL