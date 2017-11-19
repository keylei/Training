#include "sdk.hpp"

using namespace std;

SDK::SDK()
{

}

void SDK::readFromFile()
{
    //因为异常需要包含完整的调用堆栈信息, 所以需要加上文件, 行数和调用的函数等信息
    std::ostringstream message;
    message <<"File: "<<__FILE__<<"\n"
                 <<"Line:"<<__LINE__<<"\n"
                 <<"Func:"<<__FUNCTION__<<"\n"
                 <<"Detail:"<<"没有合法的文件路径"<<"\n";
    std::string msg = message.str();

    //底层用于抛出异常, 只是包含了异常的基本错误信息
    throw msg;
}
