#include "ImageSlot.hpp"

using namespace std;

using namespace Job;
using namespace SSDK;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// constructor & destructor
ImageSlot::ImageSlot()
{
    try
    {
        int imgWidth = 4096;
        int imgHeight = 3072;
        int imgCnt = 32;
        this->m_imgWidth = imgWidth;
        this->m_imgHeight = imgHeight;
        this->m_imgCnt = imgCnt;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");

}

ImageSlot::ImageSlot(int imgWidth, int imgHeight, int imgCnt)
{
    try
    {
        this->m_imgWidth = imgWidth;
        this->m_imgHeight = imgHeight;
        this->m_imgCnt = imgCnt;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

ImageSlot::ImageSlot(ImageSlot &imageSlot)
{
    try
    {
        this->m_imgCnt = imageSlot.imgCnt();
        this->m_imgWidth = imageSlot.imgWidth();
        this->m_imgHeight = imageSlot.imgHeight();
        this->m_pRawImg = imageSlot.rawImg();
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

ImageSlot::~ImageSlot()
{
    try
    {
        destroy();
    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor error!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Assignment operator
ImageSlot& ImageSlot::operator = (const ImageSlot& imageSlot)
{
    try
    {
        // self-assignment guard
        if( this != &imageSlot )
        {
            this->m_imgCnt = imageSlot.imgCnt();
            this->m_imgWidth = imageSlot.imgWidth();
            this->m_imgHeight = imageSlot.imgHeight();

            if(nullptr == this->rawImg())
            {
                if(nullptr != imageSlot.rawImg())
                {
                    create();
                }
                else
                {
                    THROW_EXCEPTION("No data!");
                }
                int cnt = m_imgCnt*m_imgWidth*m_imgHeight;
                memcpy(this->m_pRawImg,imageSlot.rawImg(),cnt);
                if(nullptr == this->m_pRawImg)
                {
                    THROW_EXCEPTION("Transform data error!");
                }
            }
        }
        return *this;
    }
    CATCH_AND_RETHROW_EXCEPTION("Catch exception and rethrow!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// add raw data
void ImageSlot::transformRawData(BYTE *imgData)
{
    try
    {
        if(nullptr == this->rawImg())
        {
            if(nullptr != imgData)
            {
                create();
            }
            else
            {
                THROW_EXCEPTION("No data!");
            }

            int cnt = m_imgCnt*m_imgWidth*m_imgHeight;
            memcpy(m_pRawImg,imgData,cnt);
            if(nullptr == this->m_pRawImg)
            {
                THROW_EXCEPTION("Transform data error!")
            }
        }
    }
    CATCH_AND_RETHROW_EXCEPTION("Catch exception and rethow!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// create & destory function
void ImageSlot::create()
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
    CATCH_AND_RETHROW_EXCEPTION("Catch exception and rethrow!");
}

void ImageSlot::destroy()
{
    try
    {
        if(nullptr != m_pRawImg)
        {
            delete [] m_pRawImg;
            m_pRawImg = nullptr;
        }
        if(nullptr != m_pRawImg)
        {
            THROW_EXCEPTION("Destory error!")
        }
    }
    CATCH_AND_RETHROW_EXCEPTION("Catch exception and rethrow!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

