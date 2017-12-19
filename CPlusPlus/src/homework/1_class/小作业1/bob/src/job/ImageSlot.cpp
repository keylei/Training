#include "ImageSlot.hpp"

using namespace Job;


ImageSlot::ImageSlot()
{

}

ImageSlot::ImageSlot(unsigned int imgWidth, unsigned int imgHeight, unsigned int imgCnt)
{
    try
    {
        //初始化图片容器中成员变量
        this->m_imgWidth = imgWidth;
        this->m_imgHeight = imgHeight;
        this->m_imgCnt = imgCnt;

        //开辟图片容器的存储空间
        create();
    }
    catch(...)
    {
        destory();
        throw;
    }
}

ImageSlot::ImageSlot(ImageSlot& imgSlot)
{
    try
    {
        //获取图片容器的图片数量,图片宽度及图片高度
        this->m_imgCnt = imgSlot.imgCnt();
        this->m_imgWidth = imgSlot.imgWidth();
        this->m_imgHeight = imgSlot.imgHeight();

        //获取单张图片的长度
        unsigned int imgLen = this->m_imgWidth * this->m_imgHeight;

        //开辟存放图片数据的存储空间,并将值深赋值到图片容器中
        this->m_pImageData = new unsigned char * [this->m_imgCnt];

        for (unsigned int i = 0; i < this->m_imgCnt; ++i)
        {
             //rime 万一imageSlot的指针也为null呢，会出现啥后果
            this->m_pImageData[i] = new unsigned char [imgLen];

            for (unsigned int j = 0; j < imgLen; ++j)
            {
                this->m_pImageData[i][j] = imgSlot.pImgData()[i][j];
            }
        }
    }
    catch(...)
    {
        destory();
        throw;//rime 不需要throw了
    }
}

ImageSlot::~ImageSlot()
{
    destory();
}

void ImageSlot::initialize(unsigned int imgCnt,
                           unsigned int imgWidth,
                           unsigned int imgHeight)
{
    this->m_imgCnt = imgCnt;
    this->m_imgWidth = imgWidth;
    this->m_imgHeight = imgHeight;
}

void ImageSlot::create()
{
    try
    {
        //获取单张图片的总长度
        int imgLen = this->m_imgWidth * this->m_imgHeight;

        //开辟指定数量的图片
        this->m_pImageData = new unsigned char * [this->m_imgCnt];

        //开辟图片数据的空间
        for (unsigned int i = 0; i < this->m_imgCnt; ++i)
        {
            this->m_pImageData[i] = new unsigned char [imgLen];
        }
    }
    catch(...)
    {
        destory();
        throw;
    }
}

void ImageSlot::destory()
{
    for (unsigned int i = 0; i < this->m_imgCnt; ++i)
    {
        if(nullptr != this->m_pImageData[i])
        {
            delete [] this->m_pImageData[i];
            this->m_pImageData[i] = nullptr;
        }
    }

    if(nullptr != this->m_pImageData)
    {
        delete [] this->m_pImageData;
        this->m_pImageData = nullptr;
    }
}
