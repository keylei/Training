#include <iostream>
#include <chrono>
#include <time.h>

#include "app/config.hpp"
#include "app/mainwindow.hpp"
#include "./job/ImageSlot.hpp"

#define BYTE_MAX_VALUE 255
#define BYTE_MIN_VALUE 0

using namespace std;//rime 标准库的namespace和自定义的namespace之间需要加空一行
using namespace App;
using namespace Job;

//rime 你的Readme跑哪里去了？

int main()
{
        //rime 为什么有这一大串注释的代码？

//    //定义一个类对象
//    Config config;
//    config.readConfigFiles();

//    //读取程式
//    QString jobDir = "../data/";

//    MainWindow mainWindow;
//    mainWindow.loadJob(jobDir);            //读取目录下的检测程式

//    mainWindow.inspectionData().board().measuredObjs().print();

//    QString filePath = jobDir +"V2.xml";
//    mainWindow.inspectionData().writeToXml(filePath);

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //生成指定数量图片容器中所有图片的数据 //rime 这会怎么没有step1，step2了？

    //rime 请不要用图片，这是图像
    unsigned int imgWidth = 4096;             //FOV中单张图片的宽度
    unsigned int imgHeight = 3072;            //FOV中单张图片的高度
    unsigned int imgCnt = 32;                 //单个FOV中需要获取的图片数量
    unsigned int imgSlotCnt = 10;             //图片容器的数量

    unsigned int imgLen = imgWidth *imgHeight * imgCnt;  //单个图片容器图片的总长度
    unsigned char ** pImgData = nullptr;            //图片容器图片数据的头指针


    //开辟多个图片容器的头地址
    pImgData = new unsigned char *[imgSlotCnt];
    //开辟多个图片容器存放数据的空间,并给图片中每个像素点赋值
    for (unsigned int i = 0; i < imgSlotCnt; ++i)
    {
        pImgData[i] = new unsigned char[imgLen];

        for (unsigned int j = 0; j < imgLen; ++j)
        {
            pImgData[i][j] = NumRandom::randomByte(BYTE_MIN_VALUE,
                                                   BYTE_MAX_VALUE);
        }
    }
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //给图片容器数组中的图片数据赋值

    ImageSlot imgSlotArr[imgSlotCnt];                  //声明一个ImageSlot的数组

    auto start = chrono::steady_clock::now();          //计时器,起始时间

    for (unsigned int i = 0; i < imgSlotCnt; ++i)
    {
        imgSlotArr[i].initialize(imgCnt,imgWidth,imgHeight);   //初始化成员变量
        imgSlotArr[i].setImgData(pImgData[i]);        //给图片容器中的图片数据赋值
    }

    auto end =chrono::steady_clock::now();

    //rime 时间11.4s
    cout << chrono::duration <double,milli> (end -start).count()<<endl;

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //释放存储随机数的空间

    for (unsigned int i = 0; i < imgSlotCnt; ++i)
    {
        delete [] pImgData[i];//rime delete之前要判断是否为nullptr
        pImgData[i] = nullptr;
    }
    delete [] pImgData;//rime delete之前要判断是否为nullptr
    pImgData = nullptr;
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    return 0;
}
