#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

//问题1:
//1.整个文件的用途没有一个纲要性的解释
//2.capacity解释错误,并不是内存大小,而是数组当前的最大长度
//3.push的注释中没有说明新的元素添加在数组中哪一个位置
//4.pull的注释太简单,看不懂
//5.print注释没有细节,至少应该告诉别人的格式


int* pDynamicArr;           // 所开辟的内存头指针
int size;                   // 开辟的空间中存储的元素个数
int capacity;               // 需要开辟的内存空间大小

/**
 * @brief init              开辟一块指定大小的内存空间
 * @param elementCnt        需要开辟的内存空间大小
 */
void init(int elementCnt)
{
    pDynamicArr = (int*)malloc(sizeof(int)*elementCnt);     // 开辟内存
    capacity = elementCnt;                  // 开辟的大小为传入的参数
    size = 0;                               // 存储的元素个数为0
}

/**
 * @brief push              将数据写入开辟好的内存中
 * @param element           写入的数据
 */
void push(int element)
{
    // 判断存储的元素个数是否小于空间大小
    if(size < capacity )
    {
        // 将传入的数据写入当前地址
        pDynamicArr[size++] = element;
    }
    else // 存储的元素个数大于空间大小
    {
        // 重新开辟一块一样大小的内存空间
        int* pTemp = malloc(sizeof(int)*capacity);
        int tempSize = size;
        // 将pDynamicArr中的数据拷贝到临时内存pTemp中
        memcpy(pTemp, pDynamicArr, capacity*sizeof(int));
        // 释放pDynamicArr
        free(pDynamicArr);

        // 重新开辟pDynamicArr,大小为原来的两倍
        init(2*capacity);
        // 将临时存放的数据拷贝回pDynamicArr中
        memcpy(pDynamicArr, pTemp, tempSize*sizeof(int));
        size = tempSize;

        // 将传入的数据写入扩大后的内存空间
        push(element);
        // 释放临时开辟的内存空间
        free(pTemp);
    }
}

/**
 * @brief pull 删除开辟的内存中当前地址上的数据
 */
void pull()
{
    // 判断内存中是否有数据
    if(size > 0)
    {
        // 删除当前地址上的数据
        pDynamicArr[size--] = 0;
    }
}

/**
 * @brief clear 清空开辟的内存中所有的数据
 */
void clear()
{
    int cnt = size;
    for (int i = 0; i < cnt; ++i)
    {
        // 删除当前地址上的数据
        pDynamicArr[i] = 0;
    }
    size = 0;       // 内存中的数据置为0
}

/**
 * @brief dispose 释放开辟的内存空间,并置为NULL
 */
void dispose()
{
    capacity = 0;           // 需要开辟的内存大小置为0
    size = 0;               // 内存中存入的数据置为0
    free(pDynamicArr);      // 释放内存
    pDynamicArr = NULL;     // 指针置为NULL
}

/**
 * @brief print 逐个打印写入内存中的数据
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
    init(initialCapacity);      // 开辟两个字节的整型空间

    push(1);                    // 连续赋值两个数据并打印结果
    push(2);
    print();

    push(3);                    // 赋值第三个数据并打印结果
    print();

    pull();                     // 删除上个数据并打印结果
    print();

    pull();                     // 删除上个数据并打印结果
    print();

    pull();                     // 删除上个数据并打印结果
    print();

    push(1);                    // 连续赋值五个数据并打印
    push(2);
    push(3);
    push(4);
    push(5);
    print();

    clear();                    // 清除所有数据并打印结果
    print();

    dispose();                  // 释放开辟的内存并打印结果
    print();
}





















