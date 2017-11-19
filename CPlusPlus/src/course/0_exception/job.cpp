#include "job.hpp"

using namespace std;

Job::Job()
{

}

void Job::readInspectionData()
{
    try
    {
           SDK sdk;
           sdk.readFromFile();
    }
    catch(const std::string& ex)
    {
        //rethrow异常, 只需要把捕获的异常往上抛, 并附加调用的退栈信息
        std::ostringstream message;
        message << "File: " << __FILE__ <<"\n"
                     << "Line:" << __LINE__ <<"\n"
                     << "Func:" << __FUNCTION__ <<"\n"
                     <<" "<<"\n"
                     << "Detail:" << ex.data() <<"\n";
        std::string msg = message.str();

        //底层用于抛出异常, 只是包含了异常的基本错误信息
        throw msg;
    }
}
