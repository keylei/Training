#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>

namespace SDK
{
/**
 *  @brief Rectangle
 *
 *      Rectangle类是自定义数据结构的类
 *
 *      类的成员变量包含:
 *          1.pad的中心点x坐标
 *          2.pad的中心点y坐标
 *          3.pad的角度
 *          4.pad的长度 //rime -1 谁告诉你是Pad了
 *          5.pad的宽度
 *      类的成员函数:访存函数.
 *
 *  @author peter
 *  @version 1.00 2017-11-21 peter
 *                note:create it
 */
    class Rectangle
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor
        /**
         * @brief Rectangle
         *      构造函数
         * @param N/A
         * @return N/A
         */
        Rectangle();
        /**
         * @brief Rectangle
         *      构造函数
         * @param xPos
         *      图像x轴坐标
         * @param yPos
         *      图像y轴坐标
         * @param width
         *      图像宽度
         * @param height
         *      图像高度
         * @return N/A
         */
        Rectangle( double xPos,
                   double yPos,
                   double width,
                   double height );
        /**
         * @brief Rectangle
         *      构造函数
         * @param xPos
         *      图像x轴坐标
         * @param yPos
         *      图像y轴坐标
         * @param angle
         *      图像旋转角度
         * @param width
         *      图像宽度
         * @param height
         *      图像高度
         * @return N/A
         */
        Rectangle( double xPos,
                   double yPos,
                   double angle,
                   double width,
                   double height );
        /**
         * @brief ~Rectangle
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual ~Rectangle();


        //>>>--------------------------------------------------------------------------------
        // get & set function
        double xPos()const {return this->m_xPos;}
        void setPosX(double xPos){ this->m_xPos = xPos;}

        double yPos()const {return this->m_yPos;}
        void setPosY(double yPos){ this->m_yPos = yPos;}

        double angle()const {return this->m_angle;}
        void setAngle(double angle){ this->m_angle = angle;}

        double width()const {return this->m_width;}
        void setWidth(double width){ this->m_width = width;}

        double height()const {return this->m_height;}
        void setHeight(double height){ this->m_height = height;}


    private:
        double m_xPos {0};
        double m_yPos {0};
        double m_angle {0.0};
        double m_width {100};
        double m_height {100};
    };

}//End of namespace SDK

#endif // RECTANGLE_HPP
