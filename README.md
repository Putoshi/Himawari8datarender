# HimawariStandardDataRender
Test
A program to generate pictures from HSD file

Himawari8  HSD file only  
 Windows Vista and later

因为老电脑用不了Python所以拿C#写了个程序  
只有Windows的，从命令行启动！！ 
## 2025.6.1update
### 支持了简单看GOES16~18的L1b，netcdf格式文件
使用方法 
1.从release下载程序，解压,解压完文件夹里面应该有15个文件，其中8个dll文件，2个exe文件，一个bz2文件是向日葵9号的hsd格式数据 3个.nc是GOES卫星的netcdf格式数据，还有一个.bat用来启动程序 
2.可以双击runstrender.bat，文件夹内应该会多出来4张图。分别是读取4个示例数据得到的。 
2.对于H8/9卫星，获得想要的himawari standard data(HSD)数据文件,可以从https://registry.opendata.aws/noaa-himawari/ 网页右侧browse bucket里找，下载的是bz2后缀，解不解压都行，然后放在你第一步解压出来的文件夹里面(我提前准备了一个文件HS_H09_20250321_0810_B13_R302_R20_S0101.DAT.bz2让你试试) 
3.对于GOES16~18卫星，获得想要的GOES卫星的L1b数据文件netcdf格式,可以从https://registry.opendata.aws/noaa-goes/ 网页右侧browse bucket里找，看好是哪个卫星,下载L1b数据，下载的是.nc后缀，然后放在你第一步解压出来的文件夹里面(我提前准备了三个.nc文件让你试试) 
4.右键runstrender.bat然后点编辑，里面的file后面跟的是要处理的文件名字，color 后面填0是黑白色阶不太准，1是BD，2是我忘记了名字的色阶，3是水汽色阶 
后面还可以加outpic空格然后写上你希望输出的图片文件名字，输出的图片都是png格式 
4.双击runstrender.bat运行。用cmd运行也行。 

st_render5_cpp goesncfile file OR_ABI-L1b-RadM1-M6C13_G16_s20192440901238_e20192440901307_c20192440901338.nc color 2 
这是读GOES L1b的命令，"goesncfile"代表读取的是GOES的L1b,(对于H8H9卫星来说是HSD格式要换成"hsdfile") file 后面是数据文件的名字，color后面是色阶选择，0~3 

对于H8H9就是这样 st_render5_cpp hsdfile file HS_H09_20250321_0810_B13_R302_R20_S0101.DAT.bz2 color 2 

使用了7zip解压，lodepng输出png图片，netcdf读取nc文件，我对开源协议不熟，感谢所有帮过我的人 
唯一对电脑有威胁的使用方法就是乱用outpic导致替换掉了电脑的其它文件，本人对任何此类自残行为不负责 
## 2025.3.21update更新
三年前代码换成c++了，现在才发呵呵呵  
使用方法:  
1.从release下载程序，解压,解压完文件夹里面应该有5个文件 7z.exe 7z.dll HS_H09_20250321_0810_B13_R302_R20_S0101.DAT.bz2 runstrender.bat st_render5_cpp.exe  
1.5你可以直接双击runstrender.bat这是准备的示例  
2.获得想要的himawari standard data(HSD)数据文件,可以从https://registry.opendata.aws/noaa-himawari/ 网页右侧browse bucket里找，下载的是bz2后缀，解不解压都行，然后放在你第一步解压出来的文件夹里面(我提前准备了一个文件HS_H09_20250321_0810_B13_R302_R20_S0101.DAT.bz2让你试试)  
3.右键runstrender.bat然后点编辑，里面的file后面跟的是要处理的HSD文件名字，color 后面填0是黑白色阶，1是BD，2是我忘记了名字的色阶  
后面还可以加outpic空格然后写上你希望输出的图片文件名字，输出的图片都是png格式  
4.双击runstrender.bat运行，等几秒文件夹内会多出来一个解压的HSD文件和一个png图片  
用cmd运行也行  
用了7zip的程序解压，lodepng项目输出图片，感谢这些作者们，感谢全世界所有帮助过我的人，我对各种开源协议不是很熟。 
