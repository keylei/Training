#ifndef BOARD_H
#define BOARD_H

#include <vector>

#include "FiducialMark.hpp"
#include "Pad.hpp"
#include "sdk/customexception.hpp"

namespace Job
{
    /**
     *  @brief Board
     *              基板信息：
     *                  1.基板长宽和原点坐标
     *                  2.被测对象信息
     *  @author lynn
     *  @version 1.00 2017-11-29 lynn
     *                note:create it
     *                2017-12-18 plato
     *                note:rewrite it
     */
    class Board
    {
    public:

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        Board();
        virtual ~Board();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        double sizeX() { return this->m_sizeX; }
        void setSizeX(double sizeX) { this->m_sizeX = sizeX; }

        double sizeY() { return this->m_sizeY; }
        void setSizeY(double sizeY) { this->m_sizeY = sizeY; }

        double originX() { return this->m_originX; }
        void setOriginX(double originX) { this->m_originX = originX; }

        double originY() { return this->m_originY; }
        void setOriginY(double originY) { this->m_originY =originY; }

        std::vector<MeasuredObj *>& pMeasuredObjs() { return this->m_pMeasuredObjs; }

    private:
        double m_sizeX{0};                //基板宽度
        double m_sizeY{0};                //基板长度
        double m_originX{0};              //基板相对于机器原点的x坐标
        double m_originY{0};              //基板相对于机器原点的y坐标
        std::vector<MeasuredObj *> m_pMeasuredObjs; // 被测对象指针
    };

}//End of namespace Job


#endif // BOARD_H
