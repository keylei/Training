#ifndef MEASUREDOBJ_HPP
#define MEASUREDOBJ_HPP

#include <iostream>

#include "../sdk/Rectangle.hpp"
#include "../sdk/CustomException.hpp"

namespace Job
{
    enum class MeasuredObjType
    {
        PAD,            // 检测对象为pad(焊盘)
        FIDUCIALMARK    // 检测对象为FiducialMark(基准点)
    };

    /**
     *  @brief  MeasuredObj
     *      MeasuredObj类表示一个检测过的元件。
     *  (具有双向链表中元素的特性，可以通过成员指针变量记录上一个元件和下一个
     *  元件,若指向nullptr则表示为没有上一个/下一个元件。)
     *  @author lynn
     *  @version 1.00 2017-11-20 lynn
     *                note:create it
     */
    class MeasuredObj
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        MeasuredObj();
        MeasuredObj(std::string name,SSDK::Shape* pShape);
        virtual~MeasuredObj();


        //>>>-------------------------------------------------------------------
        // set & get function
        /*
            *  @brief   获取元件名称
            *  @param   N/A
            *  @return  元件名陈
            */
        std::string name() { return this->m_name; }
        /*
            *  @brief   设置元件名陈
            *  @param   要设置的元件名称
            *  @return  N/A
            */
        void setName(std::string name) { this->m_name = name; }

        /*
            *  @brief   获取元件的基本信息
            *  @param   N/A
            *  @return  元件的基本信息
            */
        SSDK::Rectangle& body() { return this->m_body; }

        /*
            *  @brief   获取上一个元件的指针
            *  @param   N/A
            *  @return  上一个元件的指针
            */
        Job::MeasuredObj* pPreMeasureObj() {return this->m_pPreMeasuredObj;}
        /*
            *  @brief   设置上一个元件的指针
            *  @param   要设置的上一个元件的指针
            *  @return  N/A
            */
        void setPreMeasureObj(Job::MeasuredObj *pPreMeasuredObj)
        {
            this->m_pPreMeasuredObj = pPreMeasuredObj;
        }

        /*
            *  @brief   获取下一个元件的指针
            *  @param   N/A
            *  @return  下一个元件的指针
            */
        Job::MeasuredObj* pNextMeasuredObj(){return this->m_pNextMeasuredObj;}
        /*
            *  @brief   设置下一个元件的指针
            *  @param   要设置的下一个元件的指针
            *  @return  N/A
            */
        void setNextMeasuredObj(Job::MeasuredObj *pNextMeasuredObj)
        {
            this->m_pNextMeasuredObj = pNextMeasuredObj;
        }

        SSDK::Shape* shape(){return this->m_pShape;}
        void setShape(SSDK::Shape* pShape){this->m_pShape = pShape;}
        //<<<-------------------------------------------------------------------


    private:
        //>>>-------------------------------------------------------------------
        // member variant
        std::string m_name {""};
        SSDK::Rectangle m_body;
        Job::MeasuredObj* m_pPreMeasuredObj {nullptr};
        Job::MeasuredObj* m_pNextMeasuredObj {nullptr};
        SSDK::Shape* m_pShape {nullptr};
        //<<<-------------------------------------------------------------------
    };

}//End of namespace Job

#endif // MEASUREDOBJ_HPP
