# GeekTrack

**功能描述：一个无线姿态追踪模块，可以追踪姿态。可以用于全身动作捕捉也可以用于人体步态追踪, GeekTrack实际是GeekMotion阉割屏幕减少尺寸的版本，目的是为了方便固定在身体上，用于姿态追踪**

**GeekMotion:** https://github.com/Logzhan/GeekMoton

状态：PCB已经打样测试完成，设备WIFI正常，信号对比PCB天线弱一些。IMU、气压计读取数据正常、SD卡识别正常。

- WIFI通信功能
- IMU、MAG传感器。
- LettleShell命令行模块，可以采用命令行和ESP32交互。
- 计步器
- 运动识别(待实现)
- 电梯识别(待实现)
- SD卡存储

<img src=".\6.Image\Board.jpg" alt=".\6.I" style="zoom: 50%;" />

<img src=".\6.Image\Board_Real.jpg" alt=".\6.I" style="zoom: 50%;" />

命令行支持(移植letter shell)：

<img src=".\6.Image\GeekMotion-Shell.png" alt=".\6.I" style="zoom: 50%;" />

支持：

- 命令行自动补全
- 历史命令行记忆
- ...

**更新日志：**

**2022-09-03 :**    1）上传第一版原理图和PCB图



**lettleShell移植支持说明：** 需要适配esp32的ld文件。

样例：
C:\Users\Administrator\esp\esp-idf\components\esp32\ld\
在这个文件夹里面，把原来的esp32.project.ld.in替换当前目前的id文件，用于支持命令行，替换前记得备份

```c++
  /* 核心原理是找到这个.flash.appdesc, 然后加入_shell_command_start和*_shell_command_end/  
.flash.appdesc : ALIGN(0x10)
  {
    _rodata_start = ABSOLUTE(.);

    *(.rodata_desc .rodata_desc.*)               /* Should be the first.  App version info.        DO NOT PUT ANYTHING BEFORE IT! */
    *(.rodata_custom_desc .rodata_custom_desc.*) /* Should be the second. Custom app version info. DO NOT PUT ANYTHING BEFORE IT! */
	
	_shell_command_start = ABSOLUTE(.);
	KEEP (*(shellCommand))
	_shell_command_end = ABSOLUTE(.);

    /* Create an empty gap within this section. Thanks to this, the end of this
     * section will match .flah.rodata's begin address. Thus, both sections
     * will be merged when creating the final bin image. */
    . = ALIGN(ALIGNOF(.flash.rodata));
  } >default_rodata_seg
```

