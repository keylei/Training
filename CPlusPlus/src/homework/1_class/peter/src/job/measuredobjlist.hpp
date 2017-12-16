#ifndef MEASUREDOBJLIST_H
#define MEASUREDOBJLIST_H

#include "measuredobj.hpp"

namespace Job
{
    /**
     *  @brief  一组检测过的元件组成的链表，具有一下功能：
     *          1.向链表头插入一个元件
     *          2.项链表尾插入一个元件
     *          3.将链表第一个元件从链表移除
     *          4.将链表最后一个元件从链表移除
     *          5.打印链表中所有元件的信息
     *  @author lynn
     *  @version 1.00 2017-11-24 lynn
     *                note:create it
     */
    class MeasuredObjList
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.constructor & destructor

        /*
        *  @brief   类的构造函数，占无内容
        *  @param   N/A
        *  @return  N/A
        */
        MeasuredObjList();

        /*
        *  @brief   类的析构函数，占无内容
        *  @param   N/A
        *  @return  N/A
        */
        ~MeasuredObjList();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.set & get function

        /*
        *  @brief   获取链表中元素的个数
        *  @param   N/A
        *  @return  链表中元素的个数
        */
        int size() { return this->m_size; }

        /*
        *  @brief   获取链表第一个元素的指针
        *  @param   N/A
        *  @return  链表中第一个元素的指针
        */
        MeasuredObj * pHeadMeasuredObj() { return this->m_pHeadMeasuredObj; }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.member function

        /*
        *  @brief   向链表头插入一个元件
        *  @param   要插入的元素的指针
        *  @return  N/A
        */
        void pushHead(MeasuredObj *pNewMeasuredObj);

        /*
        *  @brief   向链表尾插入一个元件
        *  @param   要插入的元素的指针
        *  @return  N/A
        */
        void pushTail(MeasuredObj *pNewMeasuredObj);

        /*
        *  @brief   将链表第一个元件从链表移除
        *  @param   要移除的元素的指针
        *  @return  N/A
        */
        void pullHead();

        /*
        *  @brief   将链表最后一个元件从链表移除
        *  @param   要移除的元素的指针
        *  @return  N/A
        */
        void pullTail();

        /*
        *  @brief   打印链表中所有元件的信息
        *  @param   N/A
        *  @return  N/A
        */
        void print();
    private:

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //4.member variant
        int m_size{0};                                  //链表元素个数
        MeasuredObj * m_pHeadMeasuredObj{nullptr};      //链表首元素地址
    };

}//End of namespace Job


#endif // MEASUREDOBJLIST_H
