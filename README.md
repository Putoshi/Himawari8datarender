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
下载release，解压，解压完的文件夹应该有这些文件  
7z.dll 7z.exe runstrender.bat st_render5_cpp.exe 还有一个Himawari8/9卫星的HSD数据文件  
双击runstrender.bat，等几秒会生成一个解压的Himawari卫星数据文件和一张图  
右键编辑runstrender.bat 看到里面除“st_render5_cpp” 后面还有file ,file后面空一格写上你想看的数据文件名，color后面空一格跟0或1或2，0是黑白，1是BD色阶，2是我忘记名字的彩色色阶，不填color和后面的数字就默认0。  
后面还可以加上outpic 然后空一格写上你希望输出的文件的名字，输出的是png格式的图片。
用了7zip的程序解压，lodepng项目输出图片，感谢这些作者们，感谢全世界所有帮助过我的人，我对各种开源协议不是很熟。
