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
    }
    catch(...)
    {
        THROW_EXCEPTION("ImageSlot构造函数错误!");
    }
}

ImageSlot::ImageSlot( ImageSlot &imgSlot)
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
            this->m_pImageData[i] = new unsigned char[imgLen];
            memcpy(this->m_pImageData[i],imgSlot.pImgData(),imgLen);
        }
    }
    catch(...)
    {
        destory();
        THROW_EXCEPTION("mageSlot拷贝构造函数错误!");
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
        THROW_EXCEPTION("ImageSlot析构函数错误!");
    }
}

void ImageSlot::transferImgData(unsigned char *pImgData)
{
    try
    {
        //获取单个图片的总长度
        int imgLen = this->m_imgWidth * this->m_imgHeight;

        if(0 == this->m_imgCnt ||
           0 == this->m_imgHeight ||
           0 == this->m_imgWidth)  //如果imageslot成员变量为0,(即没有开辟空间)对象中
        {
            THROW_EXCEPTION("没有初始化ImageSlot对象!");
        }
        else    //如果初始化成员变量,则开辟存储空间,给图片容器中图片数据赋值
        {
            create();
            //给图片容器中每张图片数据赋值(灰度值)
            for (unsigned int i = 0; i < this->m_imgCnt; ++i)
            {
                memcpy(this->m_pImageData[i],pImgData,imgLen);
            }
        }
    }
    catch(...)
    {
        destory();
        THROW_EXCEPTION("传输图像数据错误!");
    }
}

void ImageSlot::initialize(unsigned int imgCnt,
                           unsigned int imgWidth,
                           unsigned int imgHeight)
{
    try
    {
        this->m_imgCnt = imgCnt;
        this->m_imgWidth = imgWidth;
        this->m_imgHeight = imgHeight;
    }
    catch(...)
    {
        THROW_EXCEPTION("初始化成员变量错误!");
    }
}

void ImageSlot::create()
{
    try
    {
        //获取单张图片的总长度
        int imgLen = this->m_imgWidth * this->m_imgHeight;

        //开辟单个ImageSlot存放所有图片数据的空间
        this->m_pImageData = new unsigned char * [this->m_imgCnt];

        for (unsigned int i = 0; i < this->m_imgCnt; ++i)
        {
            this->m_pImageData[i] = new unsigned char[imgLen];
        }
    }
    catch(...)
    {
        destory();
        THROW_EXCEPTION("开辟ImageSlot对象内存失败!");
    }
}

void ImageSlot::destory()
{
    try
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
    catch(...)
    {
        THROW_EXCEPTION("销毁ImageSlot对象内存失败!");
    }
}
