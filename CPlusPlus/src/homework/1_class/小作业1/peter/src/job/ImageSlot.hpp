#ifndef IMAGESLOT_HPP
#define IMAGESLOT_HPP

#include <iostream>

#include "sdk/customexception.hpp"

typedef unsigned char BYTE;

namespace Job
{
    /**
     *  @brief ImageSlot
     *      ImageSlot类是存放一组图像的类，
     *  @author peter
     *  @version 1.00 2017-12-13 peter
     *                note:create it
     */
    class ImageSlot
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        /**
         * @brief ImageSlot
         *      默认构造函数
         */
        ImageSlot();
        /**
         * @brief ImageSlot
         *      带参数构造函数
         * @param imgWidth
         *      图像的宽度
         * @param imgHeight
         *      图像的高度
         * @param imgCnt
         *      这一组图像的张数
         */
        ImageSlot(int imgWidth,int imgHeight,int imgCnt) ;
        /**
         * @brief ImageSlot
         *      复制构造函数
         * @param imageSlot
         *      传入的ImageSlot对象的引用
         */
        ImageSlot(ImageSlot& imageSlot);
        /**
         * @brief ~ImageSlot
         *      析构函数
         */
        virtual~ImageSlot();

        //>>>-----------------------------------------------------------------------
        // Assignment operator
        ImageSlot& operator = (const ImageSlot &imageSlot);

        //>>>-------------------------------------------------------------------
        // get & set function
        int imgCnt()const{return this->m_imgCnt;}
        void setImgCnt(const int imgCnt){this->m_imgCnt = imgCnt;}

        int imgWidth()const{return this->m_imgWidth;}
        void setImgWidth(const int imgWidth){this->m_imgWidth = imgWidth;}

        int imgHeight()const{return this->m_imgHeight;}
        void setImgHeight(const int imgHeight){this->m_imgHeight = imgHeight;}

        BYTE* rawImg()const{return this->m_pRawImg;}
        void setRawImg( BYTE* rawImgData){this->m_pRawImg = rawImgData;}

        //>>>-------------------------------------------------------------------
        // set raw image data
        /**
         * @brief setRawImgData
         *      将传入的图片数据存入内存中
         * @param imgData
         *      传入的图片在内存中的位置
         * @return N/A
         */
        void setRawImgData(BYTE* imgData);

    private:
        //>>>-----------------------------------------------------------------------
        // create & destroy memory function
        /**
         * @brief createMemory
         *      创建内存空间，内存大小为传入的图片的大小
         * @param N/A
         * @return N/A
         */
        void createMemory();
        /**
         * @brief destroyMemory
         *      销毁存放图片的内存空间
         * @param N/A
         * @return N/A
         */
        void destroyMemory();

    private:
        int m_imgCnt {32};                  // 一组图片的张数
        int m_imgWidth {4096};              // 每张图片的宽度
        int m_imgHeight {3072};             // 每张图片的高度
        BYTE* m_pRawImg {nullptr};          // 这一组图片在内存中的位置
    };
}//End of namespace Job


#endif // IMAGESLOT_HPP
