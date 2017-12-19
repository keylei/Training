#include <iostream>
#include <chrono>
#include <time.h>

#include "app/config.hpp"
#include "app/mainwindow.hpp"
#include "./job/ImageSlot.hpp"


#define IMG_SLOT_CNT     10   //图像槽的数量
#define PER_SLOT_IMG_CNT 32   //一个图像槽的图像数
#define IMG_LENGTH       4096 //图像长度
#define IMG_WIDTH        3072 //图像宽度
#define GRAY_MAX         255  //灰度值最大值
#define GRAY_MIN         0    //灰度值最小值


using namespace std;

using namespace App;
using namespace Job;


int main()
{
    ImageSlot imgSlotArr[IMG_SLOT_CNT]; //图像槽数组，存放图像数据
    unsigned char **pImgData = nullptr; //每个imgSlot(图像槽)的数据的首地址
    int imgSize = IMG_WIDTH * IMG_LENGTH * PER_SLOT_IMG_CNT; //单张图像的大小

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step1 为图像数据开辟内存

    pImgData = new unsigned char *[IMG_SLOT_CNT];
    for (int i = 0; i < IMG_SLOT_CNT; ++i)
    {
        pImgData[i] = new unsigned char[imgSize];
        for (int j = 0; j < imgSize; ++j)
        {
            pImgData[i][j] = NumRandom::randomByte(GRAY_MAX,GRAY_MIN);
        }
    }

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step2 传输图像数据&计算此过程时间差

    auto start = chrono::steady_clock::now(); //记录当前时间
    for (int i = 0; i < IMG_SLOT_CNT; ++i)
    {
        //初始化图像数据
        imgSlotArr[i].initImgData(PER_SLOT_IMG_CNT,IMG_WIDTH,IMG_LENGTH);
        //把图像数据传输到图像槽中
        imgSlotArr[i].transferData(pImgData[i]);
    }
    auto end =chrono::steady_clock::now(); //记录当前时间
    cout << chrono::duration <double,milli> (end -start).count()<<endl;

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step3 释放内存

    for (int i = 0; i < IMG_SLOT_CNT; ++i)
    {
        if(nullptr != pImgData[i])
        {
            delete []pImgData[i];
            pImgData[i] = nullptr;
        }
    }
    if(nullptr != pImgData)
    {
        delete []pImgData;
        pImgData = nullptr;
    }

    return 0;
}
