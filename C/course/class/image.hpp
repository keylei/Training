#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <memory.h>
#include   <stdlib.h>

namespace Job
{
    class Image
    {
    public:
        Image(int imgCnt, int imgLen);
        virtual ~Image();

        int imgCnt() const{ return this->m_imgCnt; }
        int imgLen() const{ return this->m_imgLen; }
        void setRawData(unsigned char* rawData)
        {
            memcpy(m_rawImg, rawData, m_imgCnt*m_imgLen);
        }
        unsigned char* getRawData(){return this->m_rawImg;}

    private:
        unsigned char* m_pRawImg;
        int m_imgCnt;
         int m_imgLen;
    };
}//End of namespace Job



#endif // IMAGE_HPP
