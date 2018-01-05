//#include "measuredobjlist.hpp"

//using namespace Job;

//MeasuredObjList::MeasuredObjList()
//{

//}


//MeasuredObjList::~MeasuredObjList()
//{

//}


//void MeasuredObjList::pushHead(MeasuredObj* pNewMeasuredObj)
//{
//    this->m_size++;                                     //元素个数加一
//    MeasuredObj *pOldHead = this->m_pHeadMeasuredObj;   //记录原来的第一个元件地址
//    this->m_pHeadMeasuredObj = pNewMeasuredObj;         //将链首个元素设置为新元素

//    //将新元素的后一个元素指针指向原来的首个元素
//    pNewMeasuredObj->setPNextMeasuredObj(pOldHead);

//    //将原来的首个元素的前一个元素指针指向新元素
//    if( nullptr != pOldHead)
//        pOldHead->setPPreMeasureObj(pNewMeasuredObj);

//    //将新元素的前一个元素指针置为空,表示不存在
//    pNewMeasuredObj->setPPreMeasureObj(nullptr);
//}


//void MeasuredObjList::pushTail(MeasuredObj *pNewMeasuredObj)
//{
//    this->m_size++;    //元素个数加一
//    MeasuredObj *pOldTail = this->m_pHeadMeasuredObj;

//    if( nullptr != pOldTail )
//    {
//        //获取原链表最后一个元素的指针
//        while ( nullptr != (*pOldTail).pNextMeasuredObj() )
//        {
//            pOldTail = (*pOldTail).pNextMeasuredObj();
//        }

//        //将原来的尾元素的后一个元素指针指向新元素
//        pOldTail->setPNextMeasuredObj( pNewMeasuredObj );
//    }
//    else
//    {
//        this->m_pHeadMeasuredObj = pNewMeasuredObj;
//    }

//    //将新元素的前一个元素指针指向原来的尾元素
//    pNewMeasuredObj->setPPreMeasureObj(pOldTail);

//    //将新元素的后一个元素指针置为空,表示不存在
//    pNewMeasuredObj->setPNextMeasuredObj(nullptr);

//}


//void MeasuredObjList::pullHead()
//{
//    if (0 == this->m_size)      //判断链表中是否存在元素
//    {
//        std::cout << "链表无元素" << std::endl;
//        return;
//    }

//    this->m_size--;             //链表中元素个数减一
//    //记录旧的首个元素指针
//    MeasuredObj *pOldHead = this->m_pHeadMeasuredObj;

//    //更新链表的首个元素指针
//    this->m_pHeadMeasuredObj = pOldHead->pNextMeasuredObj();

//    //将链表的新首个元素的前一个元素置为空，表示不存在
//    if( nullptr != this->m_pHeadMeasuredObj )
//        this->m_pHeadMeasuredObj->setPPreMeasureObj(nullptr);
//}


//void MeasuredObjList::pullTail()
//{
//    if (0 == this->m_size)      //判断链表中是否存在元素
//    {
//        std::cout << "链表无元素" << std::endl;
//        return;
//    }

//    this->m_size--;             //链表中元素个数减一

//    //获取原链表最后一个元素的指针
//    MeasuredObj *pOldTail = this->m_pHeadMeasuredObj;
//    while ( nullptr != pOldTail->pNextMeasuredObj() )
//    {
//        pOldTail = pOldTail->pNextMeasuredObj();
//    }

//    //记录新的链表尾元素的地址
//    MeasuredObj *pNewTail = pOldTail->pPreMeasureObj();

//    //将链表的新尾元素的后一个元素置为空，表示不存在
//    if(nullptr != pNewTail)
//        pNewTail->setPNextMeasuredObj(nullptr);
//}


//void MeasuredObjList::print()
//{
//    MeasuredObj *pPrintingMeasuredObj = this->m_pHeadMeasuredObj;

//    for( int i = 0;i < this->m_size ; ++i ) //打印链表中的所有元素
//    {
//        std::cout << pPrintingMeasuredObj->name() << ":" << std::endl
//              << "\tx坐标\t:"
//              << ((*pPrintingMeasuredObj).body()).xPos() << std::endl
//              << "\ty坐标\t:"
//              << ((*pPrintingMeasuredObj).body()).yPos() << std::endl
//              << "\t宽度\t:"
//              << ((*pPrintingMeasuredObj).body()).width() << std::endl
//              << "\t高度\t:"
//              << ((*pPrintingMeasuredObj).body()).height() << std::endl
//              << "\t角度\t:"
//              << pPrintingMeasuredObj->body().angle() <<std::endl;

//        //将待打印元素指针指向链表中的下一个元素
//        pPrintingMeasuredObj = pPrintingMeasuredObj->pNextMeasuredObj();
//    }
//}
