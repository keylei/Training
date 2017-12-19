#include <iostream>

#include "app/config.hpp"
#include "app/mainwindow.hpp"
#include "job/ImageSlot.hpp"
#include "job/Image.hpp"

using namespace std;

using namespace App;
using namespace Job;

int main()
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.读取配置文件：

        Config config;
        config.readConfigFiles();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.在堆上生成图片

        int imgCntPerSlot = 32;         //每个图片槽放的图片数量

        Job::Image* pRandomImg[imgCntPerSlot];

        for(int i = 0; i < imgCntPerSlot;i++)
        {
            //2.1.在堆上开辟用于存放图片的空间
            pRandomImg[i] = new Job::Image( config.captureSetting().imgHeight(),
                                config.captureSetting().imgWidth() );

            if(nullptr == pRandomImg[i])
            {
                THROW_EXCEPTION("new内存出错")
            }

            //2.2.随机生成图片数据
            DataGenerator::generateByteData(
                        config.captureSetting().imgHeight()*
                        config.captureSetting().imgWidth(),
                        pRandomImg[i]->pBody());
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.随机生成图片并放入图片槽

        int imgSlotCnt = 10;            //图片槽总数

        Job::ImageSlot imgSlotArr[imgSlotCnt];

        srand((unsigned)time(NULL));    //初始化随机数

        auto start = chrono::steady_clock::now();   //记录将图片放入图片槽开始时间

        for(int i = 0;i < imgSlotCnt;i++)
        {
            //3.1.设置图片槽的长宽
            imgSlotArr[i].imgHeight() = config.captureSetting().imgHeight();
            imgSlotArr[i].imgWidth() = config.captureSetting().imgWidth();

            //3.2.将随机生成的一组图片放入图片槽
            for(int j = 0; j < imgCntPerSlot;j++)
            {
                imgSlotArr[i].addImg(*(pRandomImg[j])); //将一张图片放入图片槽
            }
        }

        auto end = chrono::steady_clock::now();    //记录将图片放入图片槽结束时间
        cout << "将图像放入图像槽共耗时"
             << chrono::duration <double, milli> (end-start).count()
             << "ms" <<endl;

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //4.销毁随机图片的空间

        for(int i = 0; i < imgCntPerSlot;i++)
        {
            if(nullptr != pRandomImg[i])
            {
                delete pRandomImg[i];
            }

            pRandomImg[i] = nullptr;
        }
    }
    catch(...)
    {
        throw;  //将捕获到的异常继续上抛以显示到终端
    }
    return 0;
}
