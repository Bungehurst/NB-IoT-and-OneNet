==================================================================

名称		* Z18B_PP0_FW_V001_DPL_181125

------------------------------------------------------------------

固件版本		* v1.0

------------------------------------------------------------------

编译器版本		

IDE-Version:
μVision V5.24.2.0
Copyright (C) 2017 ARM Ltd and ARM Germany GmbH. All rights reserved.

Toolchain:          MDK-ARM Professional  Version: 5.24.1
C Compiler:         Armcc.exe        	V5.06 update 5 (build 528)
Assembler:          Armasm.exe        	V5.06 update 5 (build 528)
Linker/Locator:     ArmLink.exe        	V5.06 update 5 (build 528)
Library Manager:    ArmAr.exe        	V5.06 update 5 (build 528)
Hex Converter:      FromElf.exe        	V5.06 update 5 (build 528)
CPU DLL:            SARMCM3.DLL         V5.24.1
Dialog DLL:         DARMSTM.DLL         V1.68.0.0
Target DLL:         Segger\JL2CM3.dll   V2.99.26.0
Dialog DLL:         TARMSTM.DLL         V1.66.0.0

------------------------------------------------------------------	

创建日期	      * 11/25/2018

------------------------------------------------------------------

作者		* DPL

------------------------------------------------------------------

程序说明
	* ARM-Cortex-M3	是STM32F103系列支持文件
	* Datasheet 	是数据手册及参考资料，原理图等
	* Project	是项目程序
		* ALG		是算法文件
		* APP		是应用层文件
		* BSP		是板级文件
		* OBJ		是编译中间文件
		* PTC 		是协议层文件
		* USR		是工程主文件

------------------------------------------------------------------

2018/11/25
	* 全局变量建议采用首字母改成大写
	* u8 和unsigned char 都统一到u8
	* 宏定义采用define，不用const
	* 修改部分变量名称
	
2018/12/05
	* 修改了TransferBuffer的数据类型
	* 修改了O3,CO2,CO,NO2的数据类型 改为float
	* 修改了ADS1115的引脚PCB对应顺序，现在顺序正确

2018/12/20
	* 修改了 单片机温度数据格式 u8->char ,可以传递正负值
	* 修改了 app 温度解析函数，可以解析并显示温度正负值
	* 修改了 单片机 SHT31 BMP180 的PTC文件，可以判断是否得到设备响应并表示在数值上（无响应自动归零）

2018/12/29
	* 增加 BC-35G 模块 NB-IoT OneNet 编程
	* 程序只保留了 NB部分 其他部分已经注释

2019/1/15
	* BC-35G调通，测试稳定30分钟
------------------------------------------------------------------

其他
	keilkill.bat 可以清除中间文件

==================================================================	
