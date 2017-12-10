# 目录说明
##### src目录下为源代码目录
##### debug目录下为调试模式下生成的调试文件的目录
##### include为第三方库的头文件目录
##### lib为编译的静态库目录
##### flowchart.xml是软件运行流程图

# 3D_AOI（V2.0）
## 一.功能
- 启动软件，加载AppSetting.ini和CaptureSetting.ini
- 在2个配置都加载成功的基础上，扫描JobFolderPath目录下的程式
- 如果JobFolderPath没有文件的话，自动生成程序
- 如果JobFolderPath有文件的话，列出程式供用户选择
- 加载用户选择的程式，若为V1版本程式自动将其转换为V2版本程式
- 读取成功后把所有的InspectionData信息在屏幕上打印出来
- 读取成功后把所有的InspectionData信息以xml格式输出

## 二.配置文件说明
### 1.AppSetting.ini

Theme使用枚举: Black/White\
Lang使用枚举: CN/EN\
LaneMode: Simulator/SingleLane/DualLane\
MachineName改为枚举->MachineType: 目前有SPI/3DAOI\
CompanyName使用字符床，如“Sciject”“Sung"\
JobFolderPath:记录job的目录路径
### 2.CaptureSetting.ini

ImgWidth: 相机的图像面阵宽度\
ImgHeight: 相机的图像面阵高度\
ImgBits： 支持8位和16位

## 三.程式文件说明


软件的版本信息\
上次程式的编辑时间\
板子的名称，大小和原点\
所有的measuredObj的名称，坐标位置，大小，角度信息\
程式放在程序根目录的data目录下面


##  四.Change Log
给measuredObj加入了角度属性，读V1程式的时候考虑到兼容问题自动将V1程式转换为V2程式。
