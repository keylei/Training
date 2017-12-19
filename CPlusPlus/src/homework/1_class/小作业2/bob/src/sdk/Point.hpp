#ifndef POINT_HPP
#define POINT_HPP

namespace SSDK
{
/**
 *  @brief Point
 *          操作点的信息,例如设置&获取点的坐标等
 *  @author bob
 *  @version 1.00 2017-12-17 bob
 *                note:create it
 */
    class Point
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        Point();

        /**
        *  @brief Point
        *          初始化点的x,y轴坐标
        *  @param xPos:点的x轴坐标
        *         yPos:点的y轴坐标
        *  @return N/A
        */
        Point(double xPos,double yPos);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Point();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        double xPos(){return this->m_xPos;}
        void setXPos(double xPos){this->m_xPos = xPos;}

        double yPos(){return this->m_yPos;}
        void setYPos(double yPos){this->m_yPos = yPos;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //member variants

        double m_xPos{0.0};                       //点x轴坐标
        double m_yPos{0.0};                       //点y轴坐标
        //<<<----------------------------------------------------------------------------------------------------------------------------
    };
} //End of namespace SSDK

#endif // POINT_HPP
