#include "ImageSlot.hpp"

using namespace Job;

ImageSlot::ImageSlot()
{

}

ImageSlot::ImageSlot(int imgHeight, int imgWidth)
{
    try
    {
        if(imgHeight <= 0 || imgWidth <= 0)
        {
            THROW_EXCEPTION("传入错误的图像尺寸");
        }

        this->m_imgHeight = imgHeight;
        this->m_imgWidth = imgWidth;
    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

ImageSlot::ImageSlot(ImageSlot& imagSlot)
{
    try
    {
        if(imagSlot.imgHeight() < 0 || imagSlot.imgWidth() < 0)
        {
            THROW_EXCEPTION("传入错误的图像槽");
        }

        this->m_imgHeight = imagSlot.imgHeight();
        this->m_imgWidth = imagSlot.imgWidth();

        //复制源图像槽中的所有图像
        for(unsigned int i = 0;i < imagSlot.pImg().size();i++)
        {
            this->m_pImg.push_back(new Image(*(imagSlot.pImg()[i])));

            if(nullptr == this->m_pImg.back())
            {
                THROW_EXCEPTION("new函数内存开辟出错");
            }
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("复制函数出错")
}

ImageSlot::~ImageSlot()
{
    try
    {
        //调用释放函数释放图像槽中所有用于存放图像的空间
        this->destroy();
    }
    catch(...)
    {
        this->destroy();
    }
}

void ImageSlot::addImg(Image& img)
{
    try
    {
        if(img.height() == this->imgHeight() && img.width() == this->imgWidth())
        {
            this->m_pImg.push_back(new Image(img));

            if(nullptr == this->m_pImg.back())
            {
                THROW_EXCEPTION("new函数内存开辟出错");
            }
        }
        else
        {
            THROW_EXCEPTION("传入图片与图片槽长宽不符");
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("向图片槽添加图片失败")
}

void ImageSlot::destroy()
{
    try
    {
        //释放图像槽中所有用于存放图像的空间:
        for (int i = this->m_pImg.size(); i!=0 ;i--)
        {
            if( nullptr != this->pImg()[i-1] )
            {
                delete this->pImg()[i-1];
                this->m_pImg.pop_back();
            }
        }
    }
    catch(...)  //若捕捉到异常，则释放未释放的空间
    {
        for (int i = this->m_pImg.size(); i!=0 ;i--)
        {
            if( nullptr != this->pImg()[i-1])
            {
                delete this->pImg()[i-1];
                this->m_pImg.pop_back();
            }
        }
    }
}
