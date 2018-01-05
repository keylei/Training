#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include <iostream>

#include "./job/MeasuredObj.hpp"
#include "./job/Pad.hpp"
#include "./job/FiducialMark.hpp"
#include "../sdk/CustomException.hpp"
#include "../sdk/Point.hpp"
#include "../sdk/Shape.hpp"

namespace Job
{
/**
 *  @brief  Board
 *          基板类，在成员变量中存储基板的基本信息(包括基板的长宽、坐标等)
 *
 *  @author grace
 *  @version 1.00 2017-11-29 grace
 *                note:create it
 */
class Board
{
public:
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    Board();
    Board(SSDK::Shape *pShape);
    virtual ~Board();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //get & set function

    double sizeX() { return m_sizeX; }
    void setSizeX(double sizeX) { m_sizeX = sizeX; }

    double sizeY() { return m_sizeY; }
    void setSizeY(double sizeY) { m_sizeY = sizeY; }

    std::vector<MeasuredObj *> &pMeasuredObjs() {return m_pMeasuredObjs;}
    void setPMeasuredObjs(const std::vector<MeasuredObj *> &pMeasuredObjs) {m_pMeasuredObjs = pMeasuredObjs;}

    SSDK::Point pt() const {return m_pt;}
    void setPt(const SSDK::Point &value) {m_pt = value;}

    SSDK::Shape *pShape() const {return m_pShape;}
    void setPShape(SSDK::Shape *pShape) {m_pShape = pShape;}

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


private:
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //member variant

    std::vector<MeasuredObj*>m_pMeasuredObjs; //存放基板里的测量对象信息
    double m_sizeX{0}; //基板宽度
    double m_sizeY{0}; //基板长度
    SSDK::Point m_pt;  //基板中心点
    SSDK::Shape *m_pShape; //基板形状

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};
}//End of namespace Job


#endif // BOARD_H
