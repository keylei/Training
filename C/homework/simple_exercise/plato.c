/**
 *  @brief 模拟一个容器，可以存放元素，清除元素及销毁元素和容器
 *
 *  @author plato
 *  @version 1.00 2017-11-03 plato
 *                note:create it
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>


//问题:
//1.对于size和capacity的解释过于单薄
//2.push的两层逻辑完全没有说明
//3.pull到底是移除的哪一个元素
//4.dispose的注释中请问容量时如何销毁的?

int* pDynamicArr;       // 声明int型指针变量用于存放动态数组
int size;               // 尺寸
int capacity;           // 容量

/*
*  @brief 初始化动态数组
*  @param elementCnt:动态数组中的元素个数
*  @return N/A
*/
void init(int elementCnt)
{
    pDynamicArr = (int*)malloc(sizeof(int)*elementCnt); // 开辟一个内存空间
    capacity = elementCnt;                              // 将元素个数赋值给容量
    size = 0;                                           // 将尺寸置为0
}

/*
*  @brief 将元素放入动态数组中
*  @param element:动态数组中的元素
*  @return N/A
*/
void push(int element)
{
    // 如果尺寸小于容量
    if(size < capacity )
    {
        pDynamicArr[size++] = element;              // 将元素放入数组中
    }
    // 如果尺寸不小于容量
    else
    {
        int* pTemp = malloc(sizeof(int)*capacity);  // 定义一个临时指针并开辟内存空间
        int tempSize = size;                        // 临时保存尺寸
        // 将pDynamicArr指向的内存块的前几个指定数量的字符复制到pTemp指向的内存块中
        memcpy(pTemp, pDynamicArr, capacity*sizeof(int));
        free(pDynamicArr);                          // 释放动态数组内存

        init(2*capacity);                           // 调用初始化动态数组函数
        // 将临时存放的元素放回动态数组中
        memcpy(pDynamicArr, pTemp, tempSize*sizeof(int));
        size = tempSize;                            // 恢复保存的尺寸

        push(element);                              // 调用push函数

        free(pTemp);                                // 释放临时指针内存
    }
}

/*
*  @brief  清除动态数组中的一个元素
*  @param  N/A
*  @return N/A
*/
void pull()
{
    // 如果尺寸大于0
    if(size > 0)
    {
        pDynamicArr[size--] = 0;    // 将动态数组中的元素置为0
    }
}

/*
*  @brief 清除动态数组中的所有元素
*  @param N/A
*  @return N/A
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
*  @brief 销毁所有元素，包括容量
*  @param N/A
*  @return N/A
*/
void dispose()
{
    capacity = 0;
    size = 0;
    free(pDynamicArr);
    pDynamicArr = NULL;
}

/*
*  @brief 将指定容量中指定尺寸的元素打印出来
*  @param N/A
*  @return N/A
*/
void print()
{
    printf("\n");
    printf("Capacity:%d, Size:%d\n", capacity, size);
    int cnt = size;
    for (int i = 0; i < cnt; ++i)
    {
        printf("%d\t", pDynamicArr[i]);
    }
    printf("\n");
}

int main()
{
    int initialCapacity = 2;
    init(initialCapacity);

    push(1);    // 将元素1存入动态数组中
    push(2);    // 将元素2存入动态数组中

    print();

    push(3);    // 将元素3存入动态数组中
    print();

    pull();     // 清除最近存放的一个元素
    print();

    pull();
    print();

    pull();
    print();

    push(1);    // 将元素1存入动态数组中
    push(2);    // 将元素2存入动态数组中
    push(3);    // 将元素3存入动态数组中
    push(4);    // 将元素4存入动态数组中
    push(5);    // 将元素5存入动态数组中
    print();

    clear();    // 清除所有元素
    print();

    dispose();  // 销毁所有元素及容量空间
    print();
}
