# GEEKIMU

**功能描述：类似稚晖君Peak的小组件，带有WIFI、IMU、MAG传感器。采用原生ESP-IDF开发，移植X-Track交互框架 + LVGL。移植LettleShell命令行模块，可以采用命令行和ESP32交互。**

**更新日志：**

**2022-08-23 ：**1) 修改lettleSell部分函数，修改void为返回值为int, 减少由于函数指针转换造成的GCC Warning。2) 优化Page/SystemInfosModel.cpp，定义部分结构体后，采用memset函数初始化，减少GCC Warning。3）优化Page\StartUp部分宏定义、减少GCC Warning。 4）注释部分不使用函数，减少GCC Warning。

**lettleShell移植支持说明：**需要适配esp32的ld文件。

样例：
C:\Users\Administrator\esp\esp-idf\components\esp32\ld\
在这个文件夹里面，把原来的esp32.project.ld.in替换当前目前的id文件，用于支持命令行，替换前记得备份

