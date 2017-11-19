#include <iostream>
#include <memory>

#include "lightcheck.hpp"
#include "image.hpp"

using namespace std;
using namespace APP;
using namespace Job;

void alloc(Image** pImg, int imgCnt)
{
    int cnt = imgCnt;
    for (int i = 0; i < imgCnt; ++i)
    {
        auto size = pImg[i]->imgCnt() * pImg[i]->imgLen();
        unsigned char tempData[size];
        for (int j = 0; j < size; ++j)
        {
                tempData[j] = j;
        }

        pImg[i]->setRawData(tempData);
    }
}

void print(Image** pImg, int imgCnt)
{
    int cnt = imgCnt ;
    for (int i = 0; i < cnt; ++i)
    {
           cout << "No:" << i << "Image" <<endl;
           for (int j = 0; j < pImg[i]->imgCnt(); ++j)
           {
               for (int k = 0; k < pImg[i]->imgLen(); ++k)
               {
                   auto ptr =  pImg[i]->getRawData();
                    cout <<  (int)ptr[j*pImg[i]->imgLen()+k] << " ";
               }
                          cout << " "<<endl;
           }
           cout << " "<<endl;
    }
}

int main()
{
    //实例创建
    //    LightCheck lightCheck;
    //    int exposureTime[]{1,2,3,4};
    //    cout << lightCheck.snap(exposureTime,4) <<endl;

    //指针创建
    //    LightCheck* pLightCheck = new LightCheck();
    //    int exposureTime[]{45,56,3,43};
    //    cout << pLightCheck->snap(exposureTime,4) <<endl;

    //    //引用创建
    //    LightCheck& lightCheck(*pLightCheck);
    //    cout << pLightCheck->snap(exposureTime,4) <<endl;

    //    delete pLightCheck;

    // 联系题
    Image* pImgArr[] = { new Image(2,2), new Image(3,4) };
    alloc(pImgArr,2);
    print(pImgArr,2);
}

