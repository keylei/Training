#ifndef MEASUREDLIST_HPP
#define MEASUREDLIST_HPP

#include <iostream>
#include <iomanip>

#include "measuredobj.hpp"
#include "../SDK/customexception.hpp"

namespace Job
{
    /**
     *  @brief MeasureList
     *
     *      MeasureList类是一个双向链表类,链表中存入的是MeasureObj类型的数据.
     *
     *      类的成员变量包含:
     *          1.链表容量
     *          2.链表第一个元素地址
     *          3.链表最后一个元素地址
     *      类的成员函数功能包含:
     *          1.获取链表容量
     *          2.判断链表是否为空
     *          3.情况链表数据
     *          4.打印链表数据
     *          5.向链表收尾添加,删除元素
     *
     *  @author peter
     *  @version 1.00 2017-11-22 peter
     *                note:create it
     */
    class MeasuredList
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor
        /**
         *  @brief MeasureList
         *      默认构造函数
         *  @param N/A
         *  @return N/A
         */
        MeasuredList();
        /**
         * @brief ~MeasuredList
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual~MeasuredList();


        //>>>--------------------------------------------------------------------------------
        // set & get function
        MeasuredObj* pHead(){return this->m_pHead;}
        void setHead(MeasuredObj* pHead){this->m_pHead = pHead;}

        MeasuredObj* pTail(){return this->m_pTail;}
        void setTail(MeasuredObj* pTail){this->m_pTail = pTail;}


        //>>>--------------------------------------------------------------------------------
        // size & isEmpty & clear &print function
        /**
         * @brief size
         *      获得链表长度
         * @param N/A
         * @return
         *      返回链表长度,类型为整型
         */
        int size(){return m_size;}
        /**
         * @brief isEmpty
         *      判断链表是否为空
         * @param N/A
         * @return
         *      返回true则链表不为空,false为空
         */
        bool isEmpty(){return 0==m_size?true:false;}
        /**
         * @brief clear
         *      清除链表中的数据
         * @param N/A
         * @return N/A
         */
        void clear();
        /**
         * @brief print
         *      打印链表中的信息,当前数据包括:
         *          原件名,中心点坐标,图像面阵长宽信息
         * @param N/A
         * @return N/A
         */
        void print();

        // push & pull function
        /**
         * @brief pushBack
         *      从链表后面添加元素
         * @param measureObj
         *      添加的元素为measureObj类型
         * @return N/A
         */
        void pushBack(MeasuredObj& measureObj);
        /**
         * @brief pushFront
         *      从链表前面添加元素
         * @param measureObj
         *      添加的元素为measureObj类型
         * @return N/A
         */
        void pushFront(MeasuredObj& measureObj);
        /**
         * @brief pullBack
         *      从链表尾部删除元素
         * @param N/A
         * @return N/A
         */
        void pullBack();
        /**
         * @brief pullFront
         *      从链表头部删除元素
         * @param N/A
         * @return N/A
         */
        void pullFront();


    private:
        int m_size {0};
        MeasuredObj* m_pHead {nullptr};
        MeasuredObj* m_pTail {nullptr};
    };
}//End of namespace Job

#endif // MEASUREDLIST_HPP

