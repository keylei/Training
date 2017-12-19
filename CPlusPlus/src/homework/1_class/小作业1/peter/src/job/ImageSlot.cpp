#include "memory.h"

#include "ImageSlot.hpp"

using namespace std;
using namespace Job;
using namespace SSDK;
//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// constructor & destructor

ImageSlot::ImageSlot()
{
    int imgWidth = 4096;
    int imgHeight = 3072;
    int imgCnt = 32;
    this->m_imgWidth = imgWidth;
    this->m_imgHeight = imgHeight;
    this->m_imgCnt = imgCnt;
}

ImageSlot::ImageSlot(int imgWidth, int imgHeight, int imgCnt)
{
    //rime 没有防呆工作，大小和张数是可以输出负值的，也没有异常保护
    this->m_imgWidth = imgWidth;
    this->m_imgHeight = imgHeight;
    this->m_imgCnt = imgCnt;
}

ImageSlot::ImageSlot(ImageSlot &imageSlot)
{
    this->m_imgCnt = imageSlot.imgCnt();
    this->m_imgWidth = imageSlot.imgWidth();
    this->m_imgHeight = imageSlot.imgHeight();
}

ImageSlot::~ImageSlot()
{
    //rime 没有异常保护
    destroyMemory();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Assignment operator

ImageSlot& ImageSlot::operator = (const ImageSlot& imageSlot)
{
    try
    {
        // self-assignment guard
        if( this != &imageSlot )//rime 引用传进来就不可能为null了，多此一举
        {
            this->m_imgCnt = imageSlot.imgCnt();
            this->m_imgWidth = imageSlot.imgWidth();
            this->m_imgHeight = imageSlot.imgHeight();

            if(nullptr != this->rawImg())
            {
                createMemory();
                int cnt = m_imgCnt*m_imgWidth*m_imgHeight;
                for(int i = 0; i < cnt; ++i)
                {
                    //rime 万一imageSlot的指针也为null呢，会出现啥后果
                    this->m_pRawImg[i] = (imageSlot.rawImg())[i];
                }
            }
        }
        return *this;
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("Catch exception and rethrow!");
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//

void ImageSlot::createMemory()
{
    try
    {
        if(nullptr == m_pRawImg)
        {
            int cnt = m_imgCnt*m_imgWidth*m_imgHeight;
            this->m_pRawImg = new BYTE[ sizeof(BYTE) * cnt];
        }
        if(nullptr == m_pRawImg)
        {
            THROW_EXCEPTION("Create memory error!")
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("Catch exception and rethrow!");
}

//rime 这个命名不合理， destory就可以了，destory是销毁对象的意思， 你加个Memory就变成销毁内存了
void ImageSlot::destroyMemory()
{
    if(nullptr != m_pRawImg)
    {
        delete [] m_pRawImg;
        m_pRawImg = nullptr;
    }
}

//rime 这是个访存函数，不能出现在源文件中，再说如果涉及到深复制已经不能用访存函数了，因为人家
//从函数名上已经无法分辨你是深复制还是浅复制了
void ImageSlot::setRawImgData(BYTE *imgData)//rime p前缀讲过多少遍了
{
    try
    {
        if(nullptr == this->rawImg())
        {
            this->createMemory();
            int cnt = m_imgCnt*m_imgWidth*m_imgHeight;
//            for(int i = 0; i < cnt; ++i)
//            {
//                m_pRawImg[i] = imgData[i];
//            }

            //rime 使用memcpy复制
            memcpy(m_pRawImg, imgData,cnt);
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("Catch exception and rethow!");
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
