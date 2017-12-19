#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace SSDK
{
    /**
     *  @brief  表示矩形框，一般矩形框的基本属性
     *  @author lynn
     *  @version 1.00 2017-11-20 lynn
     *                note:create it
     */
    class Rectangle
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.constructor & destructor

        /*
        *  @brief   类的构造函数，占无内容
        *  @param   N/A
        *  @return  N/A
        */
        Rectangle();

        /*
        *  @brief  Rectangle
        *          根据参数,将其赋值给成员变量m_xPos,m_yPos,m_angle,m_width,m_height
        *  @param  xPos: 设置rectangle的x坐标
        *          yPos: 设置rectangle的y坐标
        *          width:设置rectangle的宽度
        *         height:设置rectangle的高度
        *         angle: 设置rectangle的angle角度
        *  @return  N/A
        */
        Rectangle(double xPos,
                  double yPos,
                  double width,
                  double height,
                  double angle);

        /*
        *  @brief   类的析构函数，占无内容
        *  @param   N/A
        *  @return  N/A
        */
        ~Rectangle();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.set & get function
        double xPos() { return this->m_xPos; }
        void setXPos(double xPos) { this->m_xPos = xPos; }

        double yPos() { return this->m_yPos; }
        void setYPos(double yPos) { this->m_yPos = yPos; }

        double width() { return this->m_width; }
        void setWidth(double width) { this->m_width = width; }

        double height() { return this->m_height; }
        void setHeight(double height) { this->m_height = height; }

        double angle() { return this->m_angle; }
        void setAngle(double angle) { this->m_angle = angle; }

    private:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.member function
        double m_xPos{0};         //矩形在x坐标上的位置
        double m_yPos{0};         //矩形在y坐标上的位置
        double m_width{0};        //矩形的宽度
        double m_height{0};       //矩形的高度
        double m_angle{0};        //矩形的旋转角度
    };

}

#endif // RECTANGLE_H
