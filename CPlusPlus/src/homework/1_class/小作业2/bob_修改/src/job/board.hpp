#ifndef BOARD_H
#define BOARD_H

#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <vector>

#include "measuredobjlist.hpp"
#include "../sdk/customexception.hpp"
#include "../sdk/Point.hpp"
#include "measuredobj.hpp"


namespace Job
{
    /**
     *  @brief  Board
     *          基板类，操作基板中所有对象的数据
     *              例如,增加删除pad,增加mark,改变基板名称等
     *  @author bob
     *  @version 1.00 2017-11-29 lynn
     *                note:create it
     */
    class Board
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief   类的构造函数
        *  @param   N/A
        *  @return  N/A
        */
        Board();

        /**
        *  @brief   初始化所有成员变量
        *  @param   originX:board的x轴原点坐标
        *           originY:board的y轴原点坐标
        *           sizeX:board的x方向长度
        *           sizeY:board的Y方向长度
        *           name: board的名称
        *  @return  N/A
        */
        Board(double originX,
              double originY,
              double sizeX,
              double sizeY,
              std::string name);

        /**
        *  @brief ~Board
        *           释放动态数组中存放的检测对象,如pad,mark等
        *  @param   N/A
        *  @return  N/A
        */
        virtual ~Board();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //set & get function

        std::string name() { return this->m_name; }
        void setName(std::string name) { this->m_name = name; }

        double sizeX() const {return this->m_sizeX;}
        void setSizeX(double sizeX) {this->m_sizeX = sizeX;}

        double sizeY() const {return this->m_sizeY;}
        void setSizeY(double sizeY){this->m_sizeY = sizeY;}

        SSDK::Shape* & pShape(){return this->m_pShape;}

        std::vector<MeasuredObj *>& pMeasuredObjs(){return this->m_pMeasuredObjs;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //member functions

        /**
        *  @brief  createShape
        *           创建基板的形状,默认为矩形,矩形大小为基板的尺寸
        *  @param  N/A
        *  @return N/A
        */
        void createShape();

        /**
        *  @brief  destoryShape
        *           销毁基板的形状(从内存中释放)
        *  @param  N/A
        *  @return N/A
        */
        void destoryShape();
        //<<<----------------------------------------------------------------------------------------------------------------------------


    private:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //member variants

        std::string m_name{""};                     //基板的名称
        SSDK::Point m_originalPoint;                //基板的原点
        double m_sizeX{0.0};                        //基板的宽度
        double m_sizeY{0.0};                        //基板的高度
        std::vector<MeasuredObj *> m_pMeasuredObjs; //动态数组,存放检测对象的指针
        SSDK::Shape * m_pShape{nullptr};            //基板的形状类型指针
        //<<<----------------------------------------------------------------------------------------------------------------------------

    };

}//End of namespace Job


#endif // BOARD_H
