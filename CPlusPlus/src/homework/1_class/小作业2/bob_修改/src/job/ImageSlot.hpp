#ifndef IMAGESLOT_HPP
#define IMAGESLOT_HPP

#include <iostream>
#include <string.h>

#include "../sdk/customexception.hpp"

namespace Job
{

    /**
     *  @brief ImageSlot
     *         单个FOV图像的容器
     *
     *         作用:操作拍照时图像的
     *  @author bob
     *  @version 1.00 2017-12-13 bob
     *                note:create it
     */
    class ImageSlot
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        ImageSlot();

        /**
        *  @brief ImageSlot
        *           1.获取图像的width,height,及单个fov图像的数量
        *           2.开辟指定大小的空间,存放单个FOV的图像
        *  @param  imgWidth: 图像的宽度(单张图像)
        *          imgHeight:图像的高度(单张图像)
        *          imgCnt : ImageSlot内存放图像的数量
        *  @return N/A
        */
        ImageSlot(unsigned int imgWidth,unsigned int imgHeight,unsigned int imgCnt);

        /**
        *  @brief ImageSlot
        *         深复制ImageSlot对象中所有数据,具体如下:
        *             1.图像容器中图像的数量,图像的width,height
        *             2.图像容器中所有图像数据(灰度值)
        *  @param imgSlot:为内存中已经存在的图像容器对象
        *                 (此对象数据深复制给 图像容器 对象)
        *  @return  N/A
        */
        ImageSlot(ImageSlot &imgSlot);

        /**
        *  @brief  ImageSlot
        *           释放ImageSlot的存储空间
        *  @param   N/A
        *  @return  N/A
        */
        ~ImageSlot();
        //>>>----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        int imgCnt() const{return this->m_imgCnt;}
        void setImgCnt(unsigned int imgCnt){ this->m_imgCnt = imgCnt;}

        int imgWidth() const {return this->m_imgWidth;}
        void setImgWidth(unsigned int imgWidth){this->m_imgWidth = imgWidth;}

        int imgHeight() const {return this->m_imgHeight;}
        void setImgHeight(unsigned int imgHeight){this->m_imgHeight = imgHeight;}

        unsigned char ** pImgData(){return this->m_pImageData;}
        //>>>----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //member functions

        /**
        *  @brief  initialize
        *          初始化图像容器类对象中所有成员变量
        *  @param  imgCnt:图像容器中的图像数量
        *          imgWidth:图像容器中每张图像的宽度
        *          imgHeight:图像容器中每张图像的高度
        *  @return N/A
        */
        void initialize(unsigned int imgCnt,
                        unsigned int imgWidth,
                        unsigned int imgHeight);

        /**
        *  @brief  create
        *          创建图像容器存储图像数据的空间
        *  @param  N/A
        *  @return N/A
        */
        void create();

        /**
        *  @brief  destory
        *          销毁图像容器储存图像数据空间
        *  @param  N/A
        *  @return N/A
        */
        void destory();

        /**
        *  @brief  setImgData
        *           给图像容器中每张图像中每个像素点的灰度值赋值
        *  @param  pImgData:传入图像数据的头指针
        *  @return N/A
        */
        void transferImgData(unsigned char * pImgData);
        //<<<---------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------
        //member variants

        unsigned int m_imgCnt{0};                    //ImageSlot中图像的数量
        unsigned int m_imgWidth{0};                  //图像的宽度
        unsigned int m_imgHeight{0};                 //单个图像的高度
        unsigned char ** m_pImageData{nullptr};      //指定图像容器中图像数据的指针
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };

} //End of namespace Job

#endif // IMAGESLOT_HPP
