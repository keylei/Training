#include "ImageSlot.hpp"

using namespace std;

using namespace Job;

ImageSlot::ImageSlot()
{

}

ImageSlot::ImageSlot(int imgWidth, int imgHeight, int imgCnt)
{
    try
    {
        this->m_imgWidth = imgWidth;
        this->m_imgLength = imgHeight;
        this->m_imgCnt = imgCnt;
    }
    catch(...)
    {
        destory();
    }
}

ImageSlot::ImageSlot(ImageSlot& imageSlot)
{
    try
    {
        //将图像数量
        this->m_imgCnt = imageSlot.imgCnt();
        this->m_imgWidth = imageSlot.imgWidth();
        this->m_imgLength = imageSlot.imgLength();

        //单张图片的大小
        int imgSize = this->m_imgWidth * this->m_imgLength;

        //将值深复制到图片槽中
        this->m_pImgData = new unsigned char * [this->m_imgCnt];
        for (int i = 0; i < this->m_imgCnt; ++i)
        {
            imageSlot.m_pImgData[i] = new unsigned char[imgSize];
            memcpy(this->m_pImgData[i],imageSlot.m_pImgData,imgSize);
        }
    }
    catch(...)
    {
        destory();
    }
}

ImageSlot::~ImageSlot()
{
    try
    {
        destory();
    }
    catch(...)
    {
        //释放开辟的内存
        for (int i = 0; i < this->m_imgLength; ++i)
        {
            if(this->m_pImgData[i] != nullptr)
            {
                delete []this->m_pImgData[i];
                this->m_pImgData[i] = nullptr;
            }
        }
        if(this->m_pImgData != nullptr)
        {
            delete []this->m_pImgData;
            this->m_pImgData = nullptr;
        }
    }
}

void ImageSlot::transferData(unsigned char *pImgData)
{
    try
    {
        create(); //为图像数据开辟内存
        int imgSize = this->m_imgWidth * this->m_imgLength;
        for (int i = 0; i < this->m_imgCnt; ++i)
        {
            memcpy(this->m_pImgData[i],pImgData,imgSize);
        }
    }
    catch(...)
    {
        destory();
        THROW_EXCEPTION("图像数据传输失败");
    }

}

void ImageSlot::initImgData(int imgCnt, int imgWidth, int imgLength)
{
    try
    {
    this->m_imgCnt = imgCnt;
    this->m_imgWidth = imgWidth;
    this->m_imgLength = imgLength;
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("初始化数据失败");
}

void ImageSlot::create()
{
    try
    {
        if(this->m_imgCnt != 0 &&
                this->m_imgLength !=0 &&
                this->m_imgWidth !=0)
        {
            int imgSize = this->m_imgWidth * this->m_imgLength;
            //为(this->m_imgCnt张)图像开辟内存
            this->m_pImgData = new unsigned char * [this->m_imgCnt];
            for (int i = 0; i < this->m_imgCnt; ++i)
            {
                this->m_pImgData[i] = new unsigned char [imgSize];
            }
        }
    }
    catch(...)
    {
        destory();
        THROW_EXCEPTION("为图像开辟内存失败");
    }
}

void ImageSlot::destory()
{
    try
    {
        for (int i = 0; i < this->m_imgCnt; ++i)
        {
            //释放图像数据部分内存
            if(nullptr != this->m_pImgData[i])
            {
                delete []this->m_pImgData[i];
                this->m_pImgData[i] = nullptr;
            }
        }
        //释放存放图像张数内存
        if(nullptr != this->m_pImgData)
        {
            delete []this->m_pImgData;
            this->m_pImgData = nullptr;
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("销毁内存失败");
}
