#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

#include "app/config.hpp"
#include "app/mainwindow.hpp"
#include "job/ImageSlot.hpp"

#define IMG_CNT 32          // 一组图像的张数
#define IMG_HEIGHT 3072     // 图像的高度值
#define IMG_WIDTH 4096      // 图像的宽度值
#define IMG_SLOT_CNT 10     // 图像组数
#define MIN_IMG_Gray 0      // 图像灰度值的最小值 //rime 下面大写, 上面又小写
#define MAX_IMG_GRAY 255    // 图像灰度值的最大值

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
    //    //将检测数据显示在终端上
    //    mainWindow.inspectionData().board().measuredObjs().print();
    //    //将检测数据写入到xml文件中
    //    QString filePath = jobDir +"V2.xml";
    //    mainWindow.inspectionData().writeToXml(filePath);


    // 1.一组图像的像素点个数
    int pixCnt = IMG_CNT*IMG_HEIGHT*IMG_WIDTH;

    // 2.生成一组图像的数据
    BYTE* pRawImgData = nullptr;
    pRawImgData = new BYTE[sizeof(BYTE)*pixCnt];
    //rime 上次说了DataGenerator，为什么这里又是DataGeneration

    //rime 为什么有这种命名，数据生成和图像有啥关系，为什么叫RawImageData
    DataGeneration::generateRawImageData( pRawImgData,pixCnt );

    // 3.将图像存入ImageSlot中
    ImageSlot imgSlotArr[IMG_SLOT_CNT];
    auto start = chrono::steady_clock::now();
    for(int i = 0; i < IMG_SLOT_CNT; ++i)
    {
        imgSlotArr[i].setImgHeight(IMG_HEIGHT);
        imgSlotArr[i].setImgWidth(IMG_WIDTH);
        imgSlotArr[i].setImgCnt(IMG_CNT);

        imgSlotArr[i].setRawImgData(pRawImgData);
    }
    auto end = chrono::steady_clock::now();
    //rime 需要10.7s
    cout << chrono::duration <double, milli> (end-start).count() <<endl;

    // 4.删除图像数据，并将指针置为nullptr
    delete [] pRawImgData; //rime delete之前要判断是否为nullptr
    pRawImgData = nullptr;
    return 0;
}
