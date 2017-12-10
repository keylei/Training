#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>

#include <QDomDocument>
#include <QTextStream>
#include <QFile>

#include "measuredlist.hpp"

namespace Job
{
    /**
     *  @brief Board
     *
     *     Board类中存放的是板子的名称,大小,原点和数据等信息;
     *
     *     类的成员变量包含:
     *          1.类型为MeasureList的成员(存放板子上的元器件信息的类)
     *          2.板子的名称
     *          3.板子的原点x轴位置
     *          4.板子的原点y轴位置
     *          5.板子的长度
     *          6.板子的宽度
     *      类的成员函数功能包含:
     *          1.访存函数
     *          2.打印当前板子的名称,大小和原点信息.
     *
     *  @author peter
     *  @version 1.00 2017-11-22 peter
     *                note:create it
     */
    class Board
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor function
        /**
         * @brief Board
         *      默认构造函数
         * @param N/A
         * @return N/A
         */
        Board();
        /**
         * @brief ~Board
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual~Board();


        //>>>--------------------------------------------------------------------------------
        // get & set function
        Job::MeasuredList& measuredList(){return this->m_measureList;}

        std::string& name(){return this->m_name;}
        void setName(std::string name){this->m_name = name;}

        double& originalX(){return this->m_originalX;}
        void setOriginalX(double originalX){this->m_originalX = originalX;}

        double& originalY(){return this->m_originalY;}
        void setOriginalY(double originalY){this->m_originalY = originalY;}

        double& sizeX(){return this->m_sizeX;}
        void setSizeX(double sizeX){this->m_sizeX = sizeX;}

        double& sizeY(){return this->m_sizeY;}
        void setSizeY(double sizeY){this->m_sizeY = sizeY;}


        //>>>--------------------------------------------------------------------------------
        // print
        /**
         * @brief print
         *      打印检测程式文件中Board信息
         *      当前Board包含:
         *          1.程式名
         *          2.中心点x坐标    3.中心点y坐标
         *          4.Board长        5.Board宽
         * @param N/A
         * @return N/A
         */
        void print();


    private:
        Job::MeasuredList m_measureList;
        std::string m_name {"iPhone"};
        double m_originalX {0};
        double m_originalY {0};
        double m_sizeX {200};
        double m_sizeY {200};

    };
}//End of namespace Job


#endif // BOARD_HPP
