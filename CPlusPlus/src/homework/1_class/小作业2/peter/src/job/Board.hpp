#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>

#include <QFile>
#include <QDomDocument>
#include <QTextStream>

#include "MeasuredObj.hpp"
#include "MeasuredObjList.hpp"
#include "../sdk/CustomException.hpp"

namespace Job
{
    /**
     *  @brief Board
     *      基板类，在成员变量中存储基板的基本信息(包括基板的长宽、坐标、名字)，
     * 能够将基板中的信息（含基板中元件的信息）存出为xml格式.
     *  @author lynn
     *  @version 1.00 2017-11-29 lynn
     *                note:create it
     */
    class Board
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        Board();
        Board(double xPos,double yPos,double sizeX,double sizeY);
        virtual~Board();

        //>>>-------------------------------------------------------------------
        // set & get function
        double sizeX() { return this->m_sizeX; }
        void setSizeX(double sizeX) { this->m_sizeX = sizeX; }

        double sizeY() { return this->m_sizeY; }
        void setSizeY(double sizeY) { this->m_sizeY = sizeY; }

        double xPos() { return this->m_xPos; }
        void setPosX(double originalX) { this->m_xPos = originalX; }

        double yPos() { return this->m_yPos; }
        void setPosY(double originalY) { this->m_yPos =originalY; }

        std::string name() { return this->m_name; }
        void setName(std::string name) { this->m_name = name; }

        std::string version(){return this->m_version;}
        void setVersion(std::string version) { this->m_version = version; }

        Job::MeasuredObjList & measuredObjs(){ return this->m_measuredObjs; }

        //rime 请写全，不接受为了修改不方便而写出可读性不好的代码
        std::vector<MeasuredObj*>& objs(){return this->m_objs;}

        //>>>-------------------------------------------------------------------
        // member function
        /**
         *  @brief   将基板中的信息（含基板中元件的信息）存出为xml格式
         *  @param   导出的xml文件的路径
         *  @return  N/A
         */
        void writeToXml(QString path);
        //<<<-------------------------------------------------------------------


    private:
        //>>>-------------------------------------------------------------------
        // member variant
        std::string m_name {"\0"};               // 基板名称
        std::string m_version {"\0"};            // 版本号
        double m_sizeX {0};                      // 基板宽度
        double m_sizeY {0};                      // 基板长度
        double m_xPos {0};                       // 基板相对于机器原点的x坐标
        double m_yPos {0};                       // 基板相对于机器原点的y坐标
        Job::MeasuredObjList m_measuredObjs;     // 存放检测对象的自定义链表
        //rime 如果vector中的对象是指针的话，也需要加上p，如m_pObjs
        std::vector<MeasuredObj*> m_objs;        // 存放检测对象的vector列表
        //<<<-------------------------------------------------------------------
    };

}//End of namespace Job


#endif // BOARD_HPP
