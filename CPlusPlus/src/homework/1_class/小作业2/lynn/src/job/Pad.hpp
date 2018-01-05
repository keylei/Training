#ifndef PAD_HPP
#define PAD_HPP

#include "MeasuredObject.hpp"

namespace Job
{

/**
 *  @brief 表示一个焊盘，存有焊盘的:
 *          1.形状信息
 *          2.尺寸信息
 *          3.坐标信息
 *          4.焊盘名称
 *
 *  @author lynn
 *  @version 1.00 2017-12-18 lynn
 *                note:create it
 */
class Pad:public MeasuredObject
{
public:

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    /**
    *  @brief   默认构造函数
    *  @param   N/A
    *  @return  N/A
    */
    Pad();

    /**
    *  @brief   将传入的形状设置为pad的形状
    *  @param   pShape:指向要设置的形状
    *  @return  N/A
    */
    explicit Pad(SSDK::IShape *pShape);

    /**
    *  @brief   析构函数
    *  @param   N/A
    *  @return  N/A
    */
    virtual ~Pad();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};

}//End of namespace Job

#endif // PAD_HPP
