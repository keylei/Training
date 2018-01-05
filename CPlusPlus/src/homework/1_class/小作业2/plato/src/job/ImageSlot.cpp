//#include "ImageSlot.hpp"

//using namespace std;
//using namespace Job;

//ImageSlot::ImageSlot()
//{

//}

//ImageSlot::ImageSlot(const int imgCnt, const int imgWidth, const int imgHeight)
//{
//    this->m_imgCnt = imgCnt;
//    this->m_imgWidth = imgWidth;
//    this->m_imgHeight = imgHeight;

//    create();
//}

//ImageSlot::ImageSlot(const ImageSlot& imageSlot)
//{
//    this->m_imgCnt = imageSlot.imgCnt();
//    this->m_imgHeight = imageSlot.imgHeight();
//    this->m_imgWidth = imageSlot.imgWidth();

//    this->m_pImgData = new unsigned char[imgCnt() * imgWidth() * imgHeight()];
//    *(this->m_pImgData) = *(imageSlot.pImgData());
//}

//ImageSlot::~ImageSlot()
//{
//    destroy();
//}

//void ImageSlot::create()
//{
//    this->m_pImgData = new unsigned char[imgCnt() * imgWidth() * imgHeight()];
//}

//void ImageSlot::destroy()
//{
//    if (this->m_pImgData != nullptr)
//    {
//        delete [] this->m_pImgData;
//    }
//}

//void ImageSlot::transmit(unsigned char *pImgData)
//{
//    // 判断传入的指针是否为空
//    if (nullptr == pImgData)
//    {
//        return;
//    }
//    // 获取传入的图像数据
//    int imgDataCnt = imgCnt() * imgWidth() * imgHeight();
//    memcpy(m_pImgData, pImgData, imgDataCnt);
////    for (int i = 0; i < imgDataCnt; ++i)
////    {
//////        this->m_pImgData[i] = pImgData[i];

////        cout << (int)this->m_pImgData[i] << endl;
////    }
//}

