//#include <iostream>

//using namespace std;

//class Animal
//{
//public:
//    Animal(){ cout << "Animal Constructor " << endl; }
//    Animal(const Animal& d){ cout << "Animal Constructor " << endl;}

//    virtual void sleep() const
//    {
//        cout<< "Animal Sleep ..."<<endl;
//    }
//};

//class Dog: public Animal
//{
//public:
//    Dog(){ cout << "Dog Constructor " << endl; }
//    Dog(const Dog& d){ cout << "Dog Constructor " << endl;}

//    virtual void sleep()const override
//    {
//        cout<< "Dog Sleep ..."<<endl;
//    }
//};

//void throwDog()
//{
//    throw Dog();
//}

//void catchValue()
//{
//    try
//    {
//        throw Dog();
//    }
//    catch(Animal animal) // 按值传递参数
//    {
//        animal.sleep();//无法引用到正确的类型
//    }
//}
//void catchPtr()
//{
//    try
//    {
//        throw new Dog();
//    }
//    catch(const Animal* pAnimal) // 按指针传递参数
//    {
//        pAnimal->sleep();//能够引用到正确的类型
//        //一定要销毁指针, 否则会内存泄露
//        delete pAnimal;
//    }
//}
//void catchRef()
//{
//    try
//    {
//        throw Dog();
//    }
//    catch(Animal& animal) // 按引用传递参数
//    {
//        animal.sleep();//可以引用到正确的类型
//    }
//}

//void catchDog()
//{
//    try
//    {
//        throwDog();
//    }
//    catch( Animal& animal)//这里使用 catch( Animal& )也可以,缺点是不能够调用到对象了, 只能做一次传递
//            //    catch(...)//使用...保持可以捕获任意类型, 但是这样不够安全
//    {
//        throw ;
////        throw animal;
//    }
//}

//void func3()
//{
//    throw 1;
//}

//void func2()
//{
//    try
//    {
//        func3();
//    }
//    catch(...)
//    {
//        throw;
//    }
//}

//void func1()
//{
//    try
//    {
//        func2();
//    }
//    catch(...)
//    {
//        throw;
//    }
//}

//int main()
//{
//    //>>>----------------------------------------------------------------------------------------------------------
//    //0.异常调用栈
////    func1();


//    //>>>----------------------------------------------------------------------------------------------------------
//    //1. catch子句的参数类型
//    //1.1 按值传递参数
////    catchValue(); // 调用了2次构造函数
////    cout << endl;

////    //1.2 按指针传递
////    catchPtr(); // 调用了1次构造函数
////    cout << endl;

////    //1.3 按引用传递
////    catchRef();// 调用了1次构造函数
////    cout << endl;

//    //>>>----------------------------------------------------------------------------------------------------------
//    //2. throw 和 catch
////    try
////    {
////        catchDog();
////    }
////    catch(Animal& animal)
////    {
////        //如果是throw,就是Dog
////        //如果是throw e, 就是Animal
////        animal.sleep();
////    }

//    return 0;
//}
