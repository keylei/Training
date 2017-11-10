#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

int* pDynamicArr;
int size;
int capacity;

void init(int elementCnt)
{
    pDynamicArr = (int*)malloc(sizeof(int)*elementCnt);
    capacity = elementCnt;
    size = 0;
}

void push(int element)
{
    if(size < capacity )
    {
        pDynamicArr[size++] = element;
    }
    else
    {
        int* pTemp = malloc(sizeof(int)*capacity);
        int tempSize = size;
        memcpy(pTemp, pDynamicArr, capacity*sizeof(int));
        free(pDynamicArr);

        init(2*capacity);
        memcpy(pDynamicArr, pTemp, tempSize*sizeof(int));
        size = tempSize;

        push(element);

        free(pTemp);
    }
}

void pull()
{
    if(size > 0)
    {
        pDynamicArr[size--] = 0;
    }
}

void clear()
{
    int cnt = size;
    for (int i = 0; i < cnt; ++i)
    {
        pDynamicArr[i] = 0;
    }
    size = 0;
}

void dispose()
{
    capacity = 0;
    size = 0;
    free(pDynamicArr);
    pDynamicArr = NULL;
}

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

    push(1);
    push(2);

    print();

    push(3);
    print();

    pull();
    print();

    pull();
    print();

    pull();
    print();

    push(1);
    push(2);
    push(3);
    push(4);
    push(5);
    print();

    clear();
    print();

    dispose();
    print();
}
