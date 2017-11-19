//#include <iostream>
//#include <chrono>

//#include "job.hpp"

//using namespace std;

//void loadJob()
//{
//    try
//    {
//        Job job;
//        job.readInspectionData();
//    }
//    catch(const std::string& ex)
//    {
//        // catch异常，进行处理，异常可以通过日志文件或者消息框提示，对于某些异常可以给予
//        // 选项让用户选择，但是这种情况很少，因为异常往往属于bug，不可预见的错误，所以很难给予合适的选项

//        //因为异常需要包含完整的调用堆栈信息, 所以需要加上文件, 行数和调用的函数等信息
//        std::ostringstream message;
//        message<<"File: "<<__FILE__<<"\n"
//              <<"Line:"<<__LINE__<<"\n"
//             <<"Func:"<<__FUNCTION__<<"\n"
//            <<" "<<"\n"
//           <<"Detail:"<<ex.data()<<"\n";
//        std::string msg = message.str();

//        cout << msg <<endl;
//    }
//}


//int main()
//{
//    loadJob();

//    return 0;
//}
