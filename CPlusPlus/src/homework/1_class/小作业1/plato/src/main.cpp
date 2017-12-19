#include "app/config.hpp"
#include "app/mainwindow.hpp"
#include "job/ImageSlot.hpp"

using namespace std;

using namespace App;
using namespace Job;

int main()
{
    int imgCnt = 32;
    int imgWidth = 4096;
    int imgHeight = 3072;
    int imageSlotCnt = 10;

    int imgDataCnt = imgCnt * imgWidth * imgHeight;

    unsigned char *pImgData = nullptr;
    pImgData = new unsigned char[imgDataCnt];

    DataGeneration::generateImgData(imgDataCnt, pImgData);

    auto start = chrono::steady_clock::now();
    ImageSlot *imageSlot[imageSlotCnt];
    for (int i = 0; i < imageSlotCnt; ++i)
    {
        imageSlot[i] = new ImageSlot(imgCnt, imgWidth, imgHeight);
        imageSlot[i]->transmit(pImgData);

    }
    auto end = chrono::steady_clock::now();
    cout << chrono::duration<double, milli>(end-start).count()<< endl;

    if (nullptr != pImgData)
    {
        delete [] pImgData;
    }

    for (int i = 0; i < imageSlotCnt; ++i)
    {
        if (nullptr != imageSlot[i])
        {
            delete imageSlot[i];
            imageSlot[i] = nullptr;
        }
    }
    return 0;
}
