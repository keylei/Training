#include "Image.hpp"

using namespace Job;

Image::Image()
{

}

Image::Image(int height, int width)
{
    try
    {
        if(height <= 0 || width <= 0)
        {
            THROW_EXCEPTION("传入错误的图像尺寸");
        }

        this->m_height = height;
        this->m_width = width;

        //开辟适合图像尺寸的用于存放每个像素点灰度值的空间：
        this->m_pGrayPerPixel = new unsigned char[height*width];

        if(nullptr == this->m_pGrayPerPixel)
        {
            THROW_EXCEPTION("new函数开辟空间出错");
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("双参构造函数出错");
}

Image::Image(Image &img)
{
    try
    {
        if(img.height() <= 0 || img.width() <= 0)
        {
            THROW_EXCEPTION("传入的图像数据异常");
        }

        this->m_height = img.height();
        this->m_width = img.width();

        //开辟用于保存源图像上每个像素点灰度值的空间
        this->m_pGrayPerPixel = new unsigned char[this->m_height * this->m_width];

        if(nullptr == this->m_pGrayPerPixel)
        {
            THROW_EXCEPTION("new函数开辟空间出错");
        }

        //保存源图像上每个像素点的灰度值
        memcpy(this->m_pGrayPerPixel,img.pBody(), this->m_height * this->m_width);

    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("复制构造函数出错");
}

Image::~Image()
{
    try
    {
        if (nullptr != this->pBody())
        {
            delete this->m_pGrayPerPixel;
            this->m_pGrayPerPixel = nullptr;
        }
    }
    catch(...)
    {
        if (nullptr != this->pBody())
        {
            delete this->m_pGrayPerPixel;
            this->m_pGrayPerPixel = nullptr;
        }
    }
}
