#include "image.hpp"

using namespace Job;

Image::Image(int imgCnt, int imgLen)
{
    this->m_rawImg = new unsigned char[imgCnt*imgLen];
    this->m_imgCnt = imgCnt;
    this->m_imgLen = imgLen;
}

Image::~Image()
{

}

