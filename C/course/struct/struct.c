#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

#include "student.h"
#include "teacher.h"


//这章结合<<Linux环境C程序设计>>

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    //1. 结构体类型变量的定义

//    //结构体的一般形式 struct 结构体名 结构体变量名, struct可以省略
//    struct Student stu1;

//    //使用.操作符引用结构体成员
//    stu1.no = 20090001;

//    //使用{}进行初始化,这种初始化的原理是, 结构体的成员在内存的连续空间中顺序存储
//    //首地址依次开始将相匹配的数据类型保存在对应的内存单元中
//    struct Student stu2 ={"Rime", "Software", 20, {99.9,1,2}};

//    //逐个进行初始化
//    strcpy(stu1.name, "Lynn");
//    strcpy(stu1.dept, "msl");
////    stu1.name = "lynn";
//    stu1.no = 2017;
//    stu1.score[0] = 87.5;
//    stu1.score[1] = 87.5;
//    stu1.score[2] = 87.5;
//    stu1.score[3] = 87.5;

//    struct Teacher teacher={"rime",{"plato", "philosophy", 20,  {99.9,1,2,3}}};

    //>>>----------------------------------------------------------------------------------------------------------
    //2.结构体数组的定义和引用
//    struct Student studArr[2] =
//    {
//        {"Lynn", "msl", 20 ,{1,2,3,4}},
//        {"plato", "philosophy", 20,  {5,6,7,8}}
//    };

//    int cnt = 2;
//    for (int i = 0; i < cnt; ++i)
//    {
//        printf("%s  %s  %ld %5.2f %5.2f %5.2f %5.2f\n",
//               studArr[i].name,
//               studArr[i].dept,
//               studArr[i].no,
//               studArr[i].score[0],
//               studArr[i].score[1],
//               studArr[i].score[2],
//               studArr[i].score[3]);
//    }

    //>>>----------------------------------------------------------------------------------------------------------
    // 3. 结构体指针的定义和引用

    typedef struct Student Student;
    Student rime = {"Rime", "Learner", 20 ,{1,2,3,4}};
    Student* pRime;

    //引用到一个实例
    pRime = &rime;
    printf("%s\n", pRime->name);

    //修改结构体的值
     strcpy(pRime->name, "lei.zhai");
     printf("%s\n", rime.name);

    Student* pLynn = malloc(sizeof(Student));
    strcpy(pLynn->name, "Lynn");
    printf("%s\n", pLynn->name);

    Student students[2];
    memcpy(students,  pRime, sizeof(Student));
    memcpy(students+1,  pLynn, sizeof(Student));

//    int cnt = 2;
//    for (int i = 0; i < cnt; ++i)
//    {
//        printf("%s  %s  %ld %5.2f %5.2f %5.2f %5.2f\n",
//               students[i].name,
//               students[i].dept,
//               students[i].no,
//               students[i].score[0],
//               students[i].score[1],
//               students[i].score[2],
//               students[i].score[3]);
//    }

    free(pLynn); // 堆变量需要释放

    return 0;
}
