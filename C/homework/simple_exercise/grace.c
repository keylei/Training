#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

//问题1:
//1.整个文件的用途没有一个纲要性的解释
//2.pDynamicArr为什么没有注释
//3.init 初始化 capacity size 到底时啥意思
//4.push啥叫第size位,调用函数的人是不知道size位是啥意思的/pull函数也是一样
//5.print为什么参数和返回值没有不写NA了呢

int* pDynamicArr;
int size;        //实际元素的个数
int capacity;    //pDynamicArr数组最多存放的元素个数

/*
*  @brief 初始化 capacity size
*         设置pDynamicArr数组最多存放的元素个数
*         capacity记录pDynamicArr数组最多存放的元素个数
*  @param elementCnt：最大元素个数
*  @return NA
*/
void init(int elementCnt)
{
    //开辟 存放elementCnt个整型数据的 内存
    pDynamicArr = (int*)malloc(sizeof(int)*elementCnt);
    capacity = elementCnt;
    size = 0;
}

/*
*  @brief  把pDynamicArr数组第size位的值赋值为element,
*          每次调用函数size加1
*  @param  element:pDynamicArr数组第size位值存为element
*  @return NA
*/
void push(int element)
{
    //如果实际元素的个数小于pDynamicArr数组最多存放的元素个数
    if(size < capacity )
    {
        pDynamicArr[size++] = element;
    }
    //如果实际元素的个数大于pDynamicArr数组最多存放的元素个数
    else
    {
        //定义局部临时数组替代pDynamicArr数组(内存地址和值全部)
        int* pTemp = malloc(sizeof(int)*capacity);
        int tempSize = size;
        //把pDynamicArr所指内存地址 capacity*sizeof(int)) 个字节到 pTemp
        memcpy(pTemp, pDynamicArr, capacity*sizeof(int));
        free(pDynamicArr);

        //扩大pDynamicArr数组最多存放的元素个数
        init(2*capacity);
        //把pDynamicArr替代pTemp
        memcpy(pDynamicArr, pTemp, tempSize*sizeof(int));
        size = tempSize;

        //再次调用push函数对pDynamicArr数组赋size个值
        push(element);

        //释放临时数组内存
        free(pTemp);
    }
}

/*
*  @brief 清空pDynamicArr数组第size位
*         每次调用size减1
*  @param NA
*  @return NA
*/
void pull()
{
    if(size > 0)
    {
        pDynamicArr[size--] = 0;
    }
}

/*
*  @brief 清空pDynamicArr数组全部位，size置为0
*  @param NA
*  @return NA
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
*  @brief capacity置为0,size置为0，释放pDynamicArr指针
*  @param NA
*  @return NA
*/
void dispose()
{
    capacity = 0;
    size = 0;
    free(pDynamicArr);
    pDynamicArr = NULL;
}

/*
*  @brief 打印capacity，size及pDynamicArr数组所有数据
*  @param
*  @return
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

/*
*  @brief 函数调用入口
*  @param NA
*  @return NA
*/
int main()
{
    int initialCapacity = 2;
    init(initialCapacity);

    push(1); //把pDynamicArr数组第size位的值赋值为1,每次调用函数size加1
    push(2); //把pDynamicArr数组第size位的值赋值为2,每次调用函数size加1

    print(); //打印pDynamicArr数组的值

    push(3); //把pDynamicArr数组第size位的值赋值为2,每次调用函数size加1
    print();

    pull(); //清空pDynamicArr数组第size位，每次调用size减1
    print();

    pull();
    print();

    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    print();

    clear(); //清空pDynamicArr数组全部位，size置为0
    print();

    dispose(); //capacity置为0,size置为0，释放pDynamicArr指针
    print();
}
