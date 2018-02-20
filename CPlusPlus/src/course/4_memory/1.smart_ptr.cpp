#include <iostream>
#include <chrono>
#include <vector>

//智能指针必须引用该头文件
#include <memory>

using namespace std;

class Box
{

};

class Student
{
public:
    Student()
    {
        this->m_pID = new int[11];
    }

    ~Student()
    {
        cout << "调用了Student的析构函数"<<endl;
        delete[] this->m_pID;
    }

private:
    int* m_pID{ nullptr };
};

struct Driver;
struct Bus;
struct Driver
{
    //    std::shared_ptr<Bus> bus; //×  循环引用
    std::weak_ptr<Bus> bus;
};
struct Bus
{
    std::shared_ptr<Driver> driver; //×  循环引用
};

class Person
{
public:
    ~Person()
    {
        cout << "调用了Person的析构函数"<<endl;
    }

    shared_ptr<Person> getSelf()
    {
        return shared_ptr<Person>(this);// ×
    }
};

class Cat:public enable_shared_from_this<Cat>
{
public:
    ~Cat()
    {
        cout << "调用了Cat的析构函数"<<endl;
    }

    shared_ptr<Cat> getSelf()
    {
        return shared_from_this();// √
    }
};

class Pad
{
    int m_id;
    std::string m_name;
    double m_posX;
    double m_posY;
    double m_sizeX;
    double m_sizeY;
    double m_angle;

public:
    void inspect(){}
};

class Teacher
{
public:
    Teacher()
    {
        init();
    }
    ~Teacher(){ cout <<"调用Teacher析构函数" << endl;}

    void init(){ m_favoriteCodes =new int[100];}
    void release(){delete[] m_favoriteCodes; }

private:
    int* m_favoriteCodes ;
};

class Teacher1
{
public:
    Teacher1()
    {
        init();
    }
    ~Teacher1(){cout <<"调用Teacher析构函数" << endl;release();}

    void init(){ m_favoriteCodes =new int[100];}
    void release(){delete[] m_favoriteCodes; }

private:
    int* m_favoriteCodes ;
};

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    //1. new/delete、new[]/delete[]
    {
        //1. new/delete、new[]/delete[]
        //对于内置类型
        //    int* pArray = new int[10];
        //    delete pArray;//×  虽然这样可以使用，但公司禁止这么写
        //    delete[] pArray;//√

        //对于自定义类型
        //    Box* pBox = new Box[10];
        //    delete pBox;//×  只有boxes[0]被释放了
        //    delete[] pBox;//√
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //2.智能指针
    {
        //    关于智能指针的原理见(主要参考那个手写的智能指针类)：
        //            https://www.geeksforgeeks.org/smart-pointers-cpp/

        //    std::shared_ptr：使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。
        //    在最后一个shared_ptr析构的时候，内存才会被释放。

        //        int* pNum = new int(10);
        //        std::shared_ptr<int> nums(pNum);
        //        std::shared_ptr<int> nums1(pNum);

        //1) 不能将一个原始指针直接赋值给一个智能指针。
        //    nums = new int[10];//×
        //        nums =std::shared_ptr<int> (pNum);

        //2) 指定删除器
        //        std::shared_ptr<int> nums2(new int[10] , [] (int* p) { cout<<"准备删除指针！"<< endl;delete[ ] p ; });
        //        cout<<"这里还没有开始删除指针！"<< endl;//删除工作会在出了指针对应的{}后进行

        //3)不要用一个原始指针初始化多个shared_ptr
        //        上面的代码虽然可以编译和运行，然而会造成重复析构，如果类的析构函数没有设计好，
        //        类的动态对象在析构函数中删除前没有进行nullptr的判断，就会导致异常发生
        //        Student* pStudent = new Student();
        //        shared_ptr<Student> wang(pStudent);
        //        //        shared_ptr<Student> wu(pStudent);
        //        shared_ptr<Student> wu = wang;//shared_ptr可以进行复制，不会发生重复析构的情况

        //4) 避免循环引用
        //这个使用循环引用的后果是导致两个对象都不会被删除
        //  weak_ptr可以解决循环引用的问题。把上例对象中的任意一个成员变量改为weak_ptr。
        //        std::shared_ptr<Bus> bus(new Bus());
        //        std::shared_ptr<Driver> driver(new Driver());
        //        bus->driver= driver;
        //        driver->bus = bus;

        //5) 不要在函数实参中创建shared_ptr。这个例子知道就好了，不在实现
        //6) 通过shared_from_this()返回this指针

        //  在这个例子中，由于用同一个指针(this)构造了两个智能指针，他们之间是没有任何关系的，
        //  在离开作用域后this将会被构造的两个智能指针各自析构，导致重复析构的错误

        //        shared_ptr<Person> wang( new Person() );
        //        shared_ptr<Person> wu = wang->getSelf();

        //        正确返回this的shared_ptr做法是让目标类通过派生std:enable_shared_from_this<T>类，
        //         然后使用基类的成员函数shared_from_this来返回this的shared_ptr。
        //        shared_ptr<Cat> cat( new Cat() );
        //        shared_ptr<Cat> cat1 = cat->getSelf();


        //    std::unique_ptr：不允许其他的智能指针共享其内部的指针，不允许通过赋值将一个
        //            unique_ptr赋值给另一个unique_ptr

        // 7) 指针不允许复制的场合请使用unique_ptr
        //        Student* pStudent1 = new Student();
        //        unique_ptr<Student> wang1(pStudent1);
        //        unique_ptr<Student> wu1 = wang1;//shared_ptr可以进行复制，不会发生重复析构的情况

        //        //容器中指针的管理
        //        int testCnt = 1000000;
        //        //把数据创建的时间排除
        //        Pad* pads[testCnt];
        //        for(int i = 0;i < testCnt; ++i)
        //        {
        //            pads[i] = new Pad();
        //        }

        //        vector<Pad*> rawPads;
        //        vector<shared_ptr<Pad>> sharedPads;
        //        vector<unique_ptr<Pad>> uniquePads;
        //        rawPads.reserve(testCnt);
        //        sharedPads.reserve(testCnt);
        //        uniquePads.reserve(testCnt);

        //        //原始指针
        //        auto start= std::chrono::steady_clock::now();
        //        for(int i = 0;i < testCnt; ++i)
        //        {
        //            rawPads.emplace_back(pads[i]);
        //            rawPads[i]->inspect();//再调用inspect函数
        //        }
        //        auto end = std::chrono::steady_clock::now();
        //        auto duration= std::chrono::duration<double,std::milli>(end - start).count();
        //        cout<<"原始指针:"<< duration<<endl;

        //        //shared_ptr
        //        start= std::chrono::steady_clock::now();
        //        for(int i = 0;i < testCnt; ++i)
        //        {
        //            sharedPads.emplace_back(shared_ptr<Pad>(pads[i]));
        //            sharedPads[i]->inspect();//再调用inspect函数
        //        }
        //        end = std::chrono::steady_clock::now();
        //        duration= std::chrono::duration<double,std::milli>(end - start).count();
        //        cout<<"shared_ptr:"<<duration<<endl;

        //        //unique_ptr
        //        start= std::chrono::steady_clock::now();
        //        for(int i = 0;i < testCnt; ++i)
        //        {
        //            uniquePads.emplace_back(unique_ptr<Pad>(pads[i]));
        //            uniquePads[i]->inspect();//再调用inspect函数
        //        }
        //        end = std::chrono::steady_clock::now();
        //        duration= std::chrono::duration<double,std::milli>(end - start).count();
        //        cout<<"unique_ptr:"<<duration<<endl;

        //        //        测试结果：
        //        //                原始指针:3.36904
        //        //                shared_ptr:37.4934
        //        //                unique_ptr:4.53451

        // 9) 建议多使用智能指针管理第三方库，这个例子知道就好了，不再实现

    }

    //>>>----------------------------------------------------------------------------------------------------------
    //3.内存越界
    {
//        int data[3] = { 1, 2, 3 };     //申请3个字节的int数组
//        cout << data[4] << endl;    //访问第4个元素

//        //使用容器
//        vector<int> datas{1,2,3};
//        cout << datas.at(4) << endl;//会抛出异常
//        cout << datas[3] << endl;   //不会抛出异常
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //4.使用RA||
    {
//        try
//        {
//            Teacher teacher;

//            //如果发生了异常，将引发内存泄露
//            throw  0;

//            teacher.release();
//        }
//        catch(...)
//        {
//cout <<"捕获到异常" << endl;
//        }

        //使用RAII
        try
        {
            Teacher1 teacher;

            //如果发生了异常，将引发内存泄露
            throw  0;

            teacher.release();
        }
        catch(...)
        {
            cout <<"捕获到异常" << endl;
        }
    }

    return 0;
}
