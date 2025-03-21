# HimawariStandardDataRender
Test
A program to generate pictures from HSD file

Himawari8  HSD file only  
 Windows Vista and later

因为老电脑用不了Python所以拿C#写了个程序  
只有Windows的，从命令行启动！！ 
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
