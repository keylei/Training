#include <iostream>
#include <iomanip>

#include "CompareEfficiency.hpp"

int main()
{
    // 比较vector和list的读取和插入效率
    int dataCnt {200000};       // 存入容器的数据长度
    int testCnt {3};           // 读取和插入测试10次,取平均值为结果
    compareVectorAndListEfficiency(dataCnt,testCnt);

    // 比较vector和array的读取和插入效率
    std::cout << std::endl;
    dataCnt = 100;
    testCnt = 10;
    compareVectorAndArrayEfficiency(dataCnt,testCnt);

    return 0;
}
