#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

//问题1:
//1.整个文件的用途没有一个纲要性的解释
//2.init解释错误:
//      size才是元素个数,而capacity为数组的最大元素数
//      elementCnt也不是开辟空间的大小,而是数组的初始开辟内存的数组长度
//3.push的注释中没有说明新的元素添加在数组中哪一个位置


int* pDynamicArr = NULL;                //指向存放数据空间的指针
int size;                               //已用的空间大小
int capacity;                           //开辟的空间大小


/*
*  @brief   以pDynamicArr为头地址开辟指定大小的空间，并将全局变量capacity设置为元素个数
*  @param   elementCnt为要开辟的空间大小
*  @return  N/A
*/
void init(int elementCnt)
{
    pDynamicArr = (int*)malloc(sizeof(int)*elementCnt);
    capacity = elementCnt;
    size = 0;
}


/*
*  @brief   向pDynamicArr加入新元素，若空间不够则增大其空间为原来的两倍再加入新元素
*  @param   element为要加入对的数组元素
*  @return  N/A
*/
void push(int element)
{
    if(size < capacity )            //若内存空间足够放新元素
    {
        pDynamicArr[size++] = element;
    }
    else                            //若内存空间不足加入新的元素
    {
        //1.将原来的首地址为pDynamicArr的空间复制到临时空间
        int* pTemp = malloc(sizeof(int)*capacity);
        int tempSize = size;
        memcpy(pTemp, pDynamicArr, capacity*sizeof(int));

        //2.回收以首地址为pDynamicArr开辟的空间
        free(pDynamicArr);

        //3.以pDynamicArr为首地址开辟大小为原来两倍的空间并将原来空间的数据恢复
        init(2*capacity);
        memcpy(pDynamicArr, pTemp, tempSize*sizeof(int));
        size = tempSize;

        //4.向pDynamicArr加入新的元素
        push(element);

        //5.回收开辟的临时空间
        free(pTemp);
    }
}


/*
*  @brief   删除以pDynamicArr为首地址的空间的最后一个元素
*  @param   N/A
*  @return  N/A
*/
void pull()
{
    if(size > 0)            //若以pDynamicArr为首地址的空间中存在元素
    {
        pDynamicArr[size--] = 0;
    }
}


/*
*  @brief   清空以pDynamicArr为首地址的空间的所有元素
*  @param   N/A
*  @return  N/A
*/
void clear()
{
    int cnt = size;
    for (int i = 0; i < cnt; ++i)
    {
        pDynamicArr[i] = 0;
    }
    size = 0;
}


/*
*  @brief   回收为pDynamicArr开辟的空间
*  @param   N/A
*  @return  N/A
*/
void dispose()
{
    capacity = 0;
    size = 0;
    free(pDynamicArr);
    pDynamicArr = NULL;
}


/*
*  @brief   显示以pDynamicArr为首地址空间的已用空间、总空间、空间中的所有元素
*  @param   N/A
*  @return  N/A
*/
void print()
{
    //1.打印以pDynamicArr为首地址空间的已用空间和总空间：
    printf("\n");
    printf("Capacity:%d, Size:%d\n", capacity, size);

    //2.打印以pDynamicArr为首地址空间的所有元素：
    int cnt = size;
    for (int i = 0; i < cnt; ++i)
    {
        printf("%d\t", pDynamicArr[i]);
    }
    printf("\n");
}

int main()
{
    int initialCapacity = 2;        //为pDynamicArr指针初始化的空间大小

    init(initialCapacity);          //以pDynamicArr为首地址开辟空间

    push(1);                        //将“1”放到pDynamicArr中
    push(2);                        //将“2”放到pDynamicArr中

    print();                        //显示以pDynamicArr为首地址的空间的信息

    push(3);                        //将“3”放到pDynamicArr中
    print();                        //显示以pDynamicArr为首地址的空间的信息

    pull();                         //删除以pDynamicArr中的最后一个元素
    print();                        //显示以pDynamicArr为首地址的空间的信息

    pull();                         //删除以pDynamicArr中的最后一个元素
    print();                        //显示以pDynamicArr为首地址的空间的信息

    pull();                         //删除以pDynamicArr中的最后一个元素
    print();                        //显示以pDynamicArr为首地址的空间的信息

    push(1);                        //将“1”放到pDynamicArr中
    push(2);                        //将“2”放到pDynamicArr中
    push(3);                        //将“3”放到pDynamicArr中
    push(4);                        //将“4”放到pDynamicArr中
    push(5);                        //将“5”放到pDynamicArr中
    print();                        //显示信息

    clear();                        //清空以pDynamicArr为首地址的空间的所有元素
    print();                        //显示以pDynamicArr为首地址的空间的信息

    dispose();                      //回收为pDynamicArr开辟的空间
    print();                        //显示以pDynamicArr为首地址的空间的信息
}
