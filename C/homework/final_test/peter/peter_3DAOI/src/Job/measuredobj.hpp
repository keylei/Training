#ifndef MEASUREDOBJ_HPP
#define MEASUREDOBJ_HPP

#include <iostream>

#include "../SDK/rectangle.hpp"

namespace Job
{
    /**
     *  @brief MeasureObj
     *
     *      MeasureObj类是链表中的元素类.
     *
     *      类的成员变量包含:
     *          1.元素名
     *          2.元素体(自定义结构类)
     *          3.链表中上一个元素节点的地址
     *          4.链表中下一个元素节点的地址
     *      类的成员函数:访存函数.
     *
     *  @author peter
     *  @version 1.00 2017-11-22 peter
     *                note:create it
     */
    class MeasuredObj
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor
        /**
         * @brief MeasuredObj
         *      构造函数
         * @param N/A
         * @return N/A
         */
        MeasuredObj();
        /**
         * @brief ~MeasuredObj
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual~MeasuredObj();


        //>>>--------------------------------------------------------------------------------
        // get & set function
        std::string name(){return this->m_name;}
        void setName(std::string name){this->m_name = name;}

        SDK::Rectangle& body(){return this->m_body;}

        MeasuredObj *pPre(){return this->m_pPre;}
        void setPre(MeasuredObj* pPre){this->m_pPre = pPre;}

        MeasuredObj *pNext(){return this->m_pNext;}
        void setNext(MeasuredObj* pNext){this->m_pNext = pNext;}


    private:
        std::string m_name;
        SDK::Rectangle m_body;
        MeasuredObj* m_pPre {nullptr};
        MeasuredObj* m_pNext {nullptr};
    };
}//End of namespace Job

#endif // MEASUREDOBJ_HPP
