________________________________________________________________________
	   FFT  阅读指南
-------------------------------------------------------------------------
工程描述：FFT IP设计，并加载物理约束、时序约束、GAO配置等，实现整个设计流程。
---------------------------------------------------------------------------
目标器件：GW2A-18C, GW2A-LV18PG256C8/I7
---------------------------------------------------------------------------
文件列表：
---------------------------------------------------------------------------
.
|-- project
|   `-- readme.txt                          -->  自述文件
|   `-- FFT.gprj                      	    -->  参考设计工程
|   `-- FFT.gprj.user                       -->  参考设计工程
|   |-- impl
|   	|-- project_process_config.json     -->  工程配置文件
|   |-- src                          
|       |-- testfft_top.v                   -->  工程文件 
|       |-- testfft.v                       -->  工程文件
|       |-- counter.v                       -->  工程文件
|       |-- test.cst                        -->  工程文件
|       |-- deUstb.v                        -->  工程文件
|       |-- downCnt.v                       -->  工程文件
|       |-- gowin_rpll.v                    -->  工程文件
|       `-- FFT_ToP          
|           |-- fft.v                   -->  IP文件
|           |-- fft.vo                  -->  仿真使用vo文件
|           |-- fft.ipc                 -->  IP配置文件
|           |-- fft_tmp.v		           -->	 例化模板文件
|       |-- FFT.cst  	 		              -->	 CST文件
|       |-- FFT.sdc  	 		              -->	 SDC文件
|       |-- FFT.rao			                 -->	 GAO文件

________________________________________________________________________
	   FFT  Readme
-------------------------------------------------------------------------
Project description：FFT IP design, with physical constraints, timing constraints, Gao configuration file, etc. to realize the whole design process.
---------------------------------------------------------------------------
Object device:GW2A-18C, GW2A-LV18PG256C8/I7
---------------------------------------------------------------------------
File List:
---------------------------------------------------------------------------
.
|-- project
|   `-- readme.txt                          -->  Read Me file (this file)
|   `-- FFT.gprj                      	    -->  GowinYunYuan Project File for Example Design
|   `-- FFT.gprj.user                       -->  GowinYunYuan Project File for Example Design
|   |-- impl
|   	|-- project_process_config.json     -->  Configuration File for Example Design
|   |-- src                          
|       |-- testfft_top.v                   -->  File for GowinYunYuan Project 
|       |-- testfft.v                       -->  File for GowinYunYuan Project
|       |-- counter.v                       -->  File for GowinYunYuan Project
|       |-- test.cst                        -->  File for GowinYunYuan Project
|       |-- deUstb.v                        -->  File for GowinYunYuan Project
|       |-- downCnt.v                       -->  File for GowinYunYuan Project
|       |-- gowin_rpll.v                    -->  File for GowinYunYuan Project
|       `-- FFT_ToP          
|           |-- fft.v                   -->  IP file
|           |-- fft.vo                  -->  Verilog simulation File for tb
|           |-- fft.ipc                 -->  IP configuration file
|           |-- fft_tmp.v		           -->	 Template file for instantiation
|       |-- FFT.cst  	 		              -->	 CST File
|       |-- FFT.sdc  	 		              -->	 SDC File
|       |-- FFT.rao			                 -->	 GAO File

