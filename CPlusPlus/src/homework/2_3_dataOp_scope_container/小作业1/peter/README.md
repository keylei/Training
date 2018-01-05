
##项目概述
1.项目名称	:peter_TestingEfficiency
2.创建时间	: 20180101
3.创建人	：peter

##项目根目录结构：
./
├── debug 推荐的调试目录
├── src 项目代码文件
└── READ.ME 当前阅读文档

##配置说明:
1.用qtCreator打开项目根目录下src目录下的.pro文件
2.在弹出的"Setting File for"XXX" from a different Evirnment"提示框上选择否
3.在Projects菜单中单击Confgure Project
4.在Projects菜单中将build directory设置为../debug
5.配置完成

	Build Settings
	Build directory: ../debug

##测试项目
1.比较vector和list的读取容器最后一个元素的时间
2.比较vector和list的从中间插入元素的时间
3.比较vector和array的读取容器最后一个元素的时间
4.比较vector和array 的从中间插入元素的时间

## 测试结论
### vector VS list

1.读取最后一个元素
- vector总是比list慢
- vector和list都随元素所占内存增大二增大

2.在容器中间插入元素
- vector总是比list慢
- vector消耗时间随元素所占内存的增大而增大
- list消耗时间基本不变

### vector VS array

1.读取最后一个元素
- 当元素所占内存为1B时,vector比array慢
- 当元素所占内存大于4KB是,vector毕array快

2.在容器中间插入元素
- 当元素所占内存为1B时,vector和array一样快
- 当元素所占内存大于4KB时,array比vector快