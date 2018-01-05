##项目概述
1.项目名称	:lynn_3DInspection
2.创建时间	: 星期三, 20. 十二月 2017
3.创建人	：lynn

##项目根目录结构：
./
├── debug 推荐的调试目录
├── include 第三方库文件目录
└── src 项目代码文件

##配置说明:
1.用qtCreator打开项目根目录下src目录下的.pro文件
2.在弹出的"Setting File for"XXX" from a different Evirnment"提示框上选择否
3.在Projects菜单中单击Confgure Project
4.在Projects菜单中将build directory设置为../debug
5.配置完成

##项目启动流程
1.在一个基板上生成数据随机的两个FiducialMark和8个Pad
2.计算并打印出所有FiducimalMark和Pad的总面积
3.找出并打印所有不在board范围内的FiducialMark和Pad