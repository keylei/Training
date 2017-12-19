#ifndef IMAGESLOT_HPP
#define IMAGESLOT_HPP

#include <iostream>
#include <memory.h>

#include "../sdk/customexception.hpp"

namespace Job
{
/**
 *  @brief ImageSlot
 *         图像槽：存取多张图像数据
 *
 *         功能有：初始化图像数据，为数据开内存，把图像数据传入，释放内存等
 *
 *  @author grace
 *  @version 1.00 2017-12-14 grace
 *                note:create it
 */
class ImageSlot
{
public:
    //>>>----------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    /**
     * @brief ImageSlot:默认构造函数，无任何操作
     */
    ImageSlot();

    /**
     * @brief ImageSlot：初始化成员变量，得到图像的数量、长、宽
     * @param imgWidth：图像宽
     * @param imgHeight：图像长
     * @param imgCnt：图像数量
     */
    ImageSlot(int imgWidth, int imgHeight, int imgCnt);

    /**
     * @brief ImageSlot：深复制构造函数（new）
     *                  成员变量的数据全部复制给传入的对象
     * @param imageSlot：ImageSlot类的实例
     */
    ImageSlot(ImageSlot& imageSlot);

    /**
     * @brief ~ImageSlot：析构函数
     *                    调用成员函数释放此类中开辟的内存
     */
    virtual ~ImageSlot();

    //>>>----------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------
    // get & set functions

    int imgCnt(){return this->m_imgCnt;}
    void setImgCnt(unsigned int imgCnt){ this->m_imgCnt = imgCnt;}

    int imgWidth(){return this->m_imgWidth;}
    void setImgWidth(unsigned int imgWidth){this->m_imgWidth = imgWidth;}

    int imgLength(){return this->m_imgLength;}
    void setImgLength(unsigned int imgLength){this->m_imgLength = imgLength;}

    unsigned char **pImgData(){return this->m_pImgData;}
    void setPImgData(unsigned char **pImgData) {m_pImgData = pImgData;}

    //>>>----------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------
    //member functions

    /**
     * @brief transferData：把pImgData中的数据传到成员变量中
     *                      开辟imgCnt个数的图像内存
     * @param pImgData:外部传入的待复制的数据
     */
    void transferData(unsigned char *pImgData);

    /**
     * @brief initImgData：初始化图像数据
     *                     初始化数据包括图像数量,长度，宽度
     * @param imgCnt:图像数量
     * @param imgWidth:图像宽度
     * @param imgLength:图像长度
     */
    void initImgData(int imgCnt,int imgWidth,int imgLength);

    /**
     * @brief create:开辟图像内存，调用前必须已经初始化图像数据
     */
    void create();

    /**
     * @brief destory:释放此类中开辟的内存
     */
    void destory();

    //<<<---------------------------------------------------------------------------------------------------------------------------

private:
    //>>>---------------------------------------------------------------------------------------------------------------------------
    //member variant

    int m_imgCnt{0};    //图像数量
    int m_imgWidth{0};  //图像宽度
    int m_imgLength{0}; //图像长度
    unsigned char **m_pImgData{nullptr}; //存放所有的图像数据

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};
} //End of namespace Job

#endif // IMAGESLOT_HPP
