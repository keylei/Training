//问题1:
//1.整个文件的用途没有一个纲要性的解释
//2.main函数中有注释错误
//3.push的注释中没有说明新的元素添加在数组中哪一个位置

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

int * pDynamicArr;                  //定义动态指针数组
int size;                           //动态数组中元素的个数
int capacity;                       //动态数组的容量

/*
*  @brief  初始化动态数组,给动态数组开辟空间
*  @param  elementCnt : 将数组中元素的数量(即根据数组元素数量开辟内存空间)
*  @return N/A
*/
void init(int elementCnt)
{
    pDynamicArr = (int *) malloc (sizeof(int) * elementCnt);   //开辟内存空间
    capacity = elementCnt;              //将数组的容量赋值(即数组中的元素个数)
    size = 0;                           //数组总元素的数量
}

/*
*  @brief  向动态数组中的元素赋值
*          如果数组中元素的总数超过动态数组的存放空间
*               1.开辟一个临时数组
*               2.将动态数组中的数据复制到临时数组中,并释放动态数组
*               3.重新开辟动态数组,数组的容量为上次数组容量的两倍
*               4.将临时数组中的数据复制到新初始化的动态数组中,并释放空间
*  @param  element : 向动态数组中的元素赋值
*  @return N/A
*/
void push(int element)
{
    //如果动态数组的元素个数小于容量时,将动态数组的元素赋值,并将数组中的总元素数量累加
    if(size < capacity )
    {
        //将参数element赋值给动态数组元素,并将元素数量累加
        pDynamicArr[size++] = element;
    }
    else   //如果动态数组中数组的元素总数超过动态数组容量
    {
        //定义临时整型指针,并开辟内存
        int* pTemp = malloc(sizeof(int)*capacity);
        //临时变量,记录当前数组元素的总量
        int tempSize = size;
        //将当前动态数组的所有数据赋值给临时指针
        memcpy(pTemp, pDynamicArr, capacity*sizeof(int));
        //释放动态数组空间
        free(pDynamicArr);

        //重新开辟,动态数组的容量为上次开辟时的两倍
        init(2*capacity);
        //将临时数组中的元素赋值给新创建的动态数组
        memcpy(pDynamicArr, pTemp, tempSize*sizeof(int));
        //重新获取新创建数组的元素个数
        size = tempSize;

        //再调用此函数,将值赋值到动态数组中
        push(element);
        //释放临时数组空间
        free(pTemp);
    }
}

/*
*  @brief  将动态数组的最后一个元素初始化为0,
*  @param  N/A
*  @return N/A
*/
void pull()
{
    //如果动态数组的元素个数大于0,将动态数组的最后一个元素赋值为0,并将动态数组中元素个数累减
    if(size > 0)
    {
        pDynamicArr[size--] = 0;
    }
}

/*
*  @brief  将动态数组的各个元素赋值为0,并将动态数组的元素总数初始化为0
*  @param  N/A
*  @return N/A
*/
void clear()
{
    int cnt = size;                                 //将数组的元素个数数组给临时变量
    //将动态数组中每个元素的值初始化为0
    for (int i = 0; i < cnt; ++i)
    {
        pDynamicArr[i] = 0;
    }
    // 将动态数组的元素个数初始化为0
    size = 0;
}

/*
*  @brief  释放动态数组,并将动态数组的容量,数组中元素个数初始化
*  @param  N/A
*  @return N/A
*/
void dispose()
{
    capacity = 0;               //将动态数组的容量初始化为0
    size = 0;                   //将动态数组的元素个数初始化为0
    free(pDynamicArr);          //释放动态数组空间
    pDynamicArr = NULL;         //将动态数组指针指向NULL
}

/*
*  @brief  输出动态数组的 容量,元素个数,将动态数组中每个元素
*  @param  N/A
*  @return N/A
*/
void print()
{
    printf("\n");               //输出空行
    //输出动态数组中的容量及元素个数
    printf("Capacity:%d, Size:%d\n", capacity, size);
    //将动态数组的元素个数赋值给变量数量
    int cnt = size;
    //输出动态数组的每个元素
    for (int i = 0; i < cnt; ++i)
    {
        printf("%d\t", pDynamicArr[i]);
    }
    printf("\n");
}

int main()
{
    int initialCapacity = 2;
    //根据数组的容量,初始化动态数组,动态数组的容量为2(单位整型元素),数组中元素个数为0
    init(initialCapacity);

    push(1); //向动态数组中第一个元素赋值为1
    push(2); //向动态数组中第二个元素赋值为2

    print(); //输出动态数组的 容量,元素总数,各个元素的值

     //向动态数组中第三个元素赋值为3,因为动态数组中的容量为2,
    // 因此新开辟一个数组容量为上次开辟容量的2倍,存放数组中的元素
    push(3);
    print(); //输出动态数组的 容量,元素总数,各个元素的值

    pull();  //将动态数组中的元素总量减去1个
    print(); //输出动态数组的 容量,元素总数,各个元素的值

    pull();  //将动态数组中的元素总量减去1个
    print(); //输出动态数组的 容量,元素总数,各个元素的值

    pull();  //将动态数组中的元素总量减去1个
    print(); //输出动态数组的 容量,元素总数,各个元素的值

    push(1);  //向动态数组中第一个元素赋值为1
    push(2);  //向动态数组中第一个元素赋值为2
    push(3);  //向动态数组中第一个元素赋值为3
    push(4);  //向动态数组中第一个元素赋值为4

    //向动态数组中第五个元素赋值为5,因为动态数组中的容量为4
    // 因此新开辟一个数组容量为上次开辟容量的2倍(即为8),存放数组中第五个的元素
    push(5);
    print();  //输出动态数组的 容量,元素总数,各个元素的值

    clear();  //将数组中元素的总数
    print();  //输出动态数组的 容量,元素总数,各个元素的值

    dispose();  //释放动态数组,并将动态数组的容量,元素个数全部初始化
    print();    //输出动态数组的 容量,元素总数,各个元素的值
}

//动态数组的空间可以根据实际的需求自动分配空间
//普通数组的空间需一次性开辟完成,如果元素的数量超过数组的容量,则会出现越界
