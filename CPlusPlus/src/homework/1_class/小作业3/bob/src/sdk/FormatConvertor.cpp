#include "FormatConvertor.hpp"

using namespace SDK;

FormatConvertor::FormatConvertor()
{

}

FormatConvertor::~FormatConvertor()
{

}

string FormatConvertor::intToString(int value)
{
    try
    {
        //定义一个字符串流对象
        stringstream string;
        //将整形数值赋值给字符串流
        string <<value;
        //将转换后的字符串作为返回值
        return string.str();
    }
    CATCH_AND_RETHROW_EXCEPTION("将整形转换成字符串错误!");
}
