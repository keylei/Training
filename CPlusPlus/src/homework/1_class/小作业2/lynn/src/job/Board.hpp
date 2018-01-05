#ifndef BOARD_H
#define BOARD_H

#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <vector>

#include "MeasuredObject.hpp"
#include "../sdk/CustomException.hpp"
#include "../sdk/Shape.hpp"

namespace Job
{
    /**
     *  @brief 基板类，在成员变量中存储基板的基本信息,包括:
     *          1.基板的长宽、坐标、名字
     *          2.基板上的所有检测元件
     *
     *          能够将基板中的信息（含基板中元件的信息）存出为xml格式
     *  @author lynn
     *  @version 1.00 2017-11-29 lynn
     *                note:create it
     */
    class Board
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /*
        *  @brief   类的默认构造函数
        *  @param   N/A
        *  @return  N/A
        */
        Board();

        /*
        *  @brief   析构函数
        *  @param   N/A
        *  @return  N/A
        */
        virtual ~Board();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //set & get function

        double sizeX() { return this->m_sizeX; }
        void setSizeX(double sizeX) { this->m_sizeX = sizeX; }

        double sizeY() { return this->m_sizeY; }
        void setSizeY(double sizeY) { this->m_sizeY = sizeY; }

        double originX() { return this->m_originX; }
        void setOriginX(double originX) { this->m_originX = originX; }

        double originY() { return this->m_originY; }
        void setOriginY(double originY) { this->m_originY =originY; }

        std::string name() { return this->m_name; }
        void setName(std::string name) { this->m_name = name; }

        void setVersion(std::string version) { this->m_version = version; }

        std::vector<MeasuredObject*>& pMeasuredObjects(){ return this->m_pMeasuredObjects; }

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //member function

        /*
        *  @brief   判断元件是否在基板范围以内
        *  @param   pObject:指向元件的指针
        *  @return  true :表示元件在基板范围内
        *           false:表示元件不在基板范围内
        */
        bool canContainObj(MeasuredObject *pMeasuredObjects);

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    private:

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //member variant

        std::string m_name{"\0"};
        std::string m_version{"\0"};

        double m_sizeX{0};      //基板宽度
        double m_sizeY{0};      //基板长度
        double m_originX{0};    //基板相对于机器原点的x坐标
        double m_originY{0};    //基板相对于机器原点的y坐标

        std::vector<MeasuredObject*> m_pMeasuredObjects;    //指向所有元件

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    };

}//End of namespace Job


#endif // BOARD_H
