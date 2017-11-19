//#include <iostream>
//#include <chrono>

//using namespace std;

//void normalTest(int cnt)
//{
//    double temp;
//    for (int i = 0; i < cnt; ++i)
//    {
//        temp=(0.4*2+i)/2;
//    }
//}

//void tryTest(int cnt)
//{
//    double temp;
//    for (int i = 0; i < cnt; ++i)
//    {
//        try
//        {
//            temp= (0.4*2+i)/2;
//        }
//        catch(const exception& ex)
//        {

//        }
//    }
//}

//void catchTest(int cnt)
//{
//    double temp;
//    for (int i = 0; i < cnt; ++i)
//    {
//        try
//        {
//            temp= (0.4*2+i)/2;

//            if(i==0)
//                throw 0;
//        }
//        catch(...)
//        {
//            continue;
//        }
//    }
//}

//int main()
//{
//    int testCnt = 1000;

//    //>>>----------------------------------------------------------------------------------------------------------
//    //1. 普通测试
//    auto start = chrono::steady_clock::now();
//    normalTest(testCnt);
//    auto end = chrono::steady_clock::now();
//    cout << "Normal:" << chrono::duration <double, micro> (end-start).count() <<endl;


//    //>>>----------------------------------------------------------------------------------------------------------
//    //2.带try的测试
//    start = chrono::steady_clock::now();
//    tryTest(testCnt);
//    end = chrono::steady_clock::now();
//    cout << "Try:" << chrono::duration <double, micro> (end-start).count() <<endl;

//    //>>>----------------------------------------------------------------------------------------------------------
//    //3.仅仅带一次catch的测试
//    start = chrono::steady_clock::now();
//    catchTest(testCnt);
//    end = chrono::steady_clock::now();
//    cout << "Catch:" << chrono::duration <double, micro> (end-start).count() <<endl;


//    return 0;
//}
