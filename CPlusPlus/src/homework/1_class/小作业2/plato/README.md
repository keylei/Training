### 项目需求:

1. 实现一个Board类,有以下基本属性:
     1. 原点坐标X
     2. 原点坐标Y
     3. 板子的宽度
     4. 板子的高度

2. 实现FiducialMark类, 有以下基本属性:
     1. X坐标位置
     2. Y坐标位置
     3. 形状信息,可能有(圆形和矩形两种情况)
     4. name字符串信息

3. 实现Pad类, 有以下基本属性:
     1. X坐标位置
     2. Y坐标位置
     3. 形状信息,可能有(圆形和矩形两种情况)
     4. name字符串信息

4. 形状中矩形的数据结构有:中心点坐标和长宽和角度,有计算面积的功能

5. 形状中的圆有:中心点和半径,有计算面积的功能

6. 生成2个FiducialMark和8个Pad,求出所有FiducialMark和Pad的总面积

7. 打印出所有在板子之外的FiducialMark和Pad对象

### 背景知识
---
本项目基于SMT(表面组装技术)生产线上的检测设备3DAOI(自动光学检测)，
主要检测对象为PCB(印刷电路板),这里Board(基板)代指PCB，
MeasuredObj(被测对象)为PCB上需检测的对象总称，
FiducialMark(基准点)和Pad(焊盘)是被测对象的两种类型，
对象有两种形状Rectangle(矩形)和Circle(圆形)
***

### 目录树

```
├── Debug
├── src
│   ├── app
│   │   ├── Datagenerator.cpp
│   │   └── Datagenerator.hpp
│   ├── job
│   │   ├── Board.cpp
│   │   ├── Board.hpp
│   │   ├── Pad.cpp
│   │   ├── Pad.hpp
│   │   ├── FiducialMark.cpp
│   │   ├── FiducialMark.hpp
│   │   ├── MeasuredObj.cpp
│   │   └── MeasuredObj.hpp
│   ├── main.cpp
│   ├── plato_3DInspection.pro
│   └── sdk
│       ├── Circle.cpp
│       ├── Circle.hpp
│       ├── Rectangle.cpp
│       ├── Rectangle.hpp
│       ├── Shape.cpp
│       ├── Shape.hpp
│       ├── NumRandom.cpp
│       ├── NumRandom.hpp
│       ├── CustomException.cpp
│       └── customexception.hpp
└── README.md
```

### 项目环境
---
Qt 5.9.0
***
- 启动
    1. 打开 Qt 5.9.0
    2. Open Project → src/plato_3DInspection.pro
    3. Build Settings → 勾选 Shadow build → Build directory 设置为该项目根目录下的Debug，例如:“/home/plato/plato_3DInspection/Debug”
---

### 项目说明

#### app
- DataGenerator类负责生成被测对象的数据结构

#### job
- Board类中有基板的原点坐标、长宽及被测对象信息，组合MeasuredObj类
- MeasuredObj类中有对象名及形状信息，组合Shape类
- FiducialMark类和Pad类继承于MeasuredObj类

#### sdk
- Shape类中有对象中心点坐标信息
- Rectangle类和Circle类继承于Shape类
- Rectangle类中有矩形长宽和角度信息、计算面积功能、判断对象是否在基板之内的功能
- Circle类中有圆形半径信息、计算面积功能、判断对象是否在基板之内的功能
- NumRandom类负责生成随机数
- CustomException类负责处理异常

