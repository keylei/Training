#ifndef FORMATCONVERSION_HPP
#define FORMATCONVERSION_HPP

namespace SDK
{
    //将变量中":"后面的字段截取为string类型的字符串
    #define VAR_TO_STR(var)\
        ({\
            std::string name = (#var);\
            int pos = 0;\
            int length = 0;\
            length = name.length();\
            pos = name.find_last_of(':',length);\
            if ( pos == -1 )\
            {\
                pos = 0;\
                name = name.substr(pos,length);\
            }\
            else\
            {\
                name = name.substr(pos+1,length);\
            }\
            (name);\
        })
}//End of namespace SDK


#endif // FORMATCONVERSION_HPP
