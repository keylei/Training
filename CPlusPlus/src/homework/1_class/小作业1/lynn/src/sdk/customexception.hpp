/**
 *  @brief  自定义异常，传入错误信息，返回格式化的全套异常信息
 *  @author lynn
 *  @version 1.00 2017-11-21 lynn
 *                note:create it
 */

#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <sstream>
#include <iostream>

namespace SSDK
{
    /*
    *  @brief   追加异常信息并抛出异常
    *  @param   原来的异常信息
    *  @return  N/A
    */
    #define THROW_EXCEPTION(exMsg)\
    {\
        std::ostringstream message;\
        message << "File:"<<__FILE__<<"\n"\
                << "Line:"<<__LINE__<<"\n"\
                << "Func:"<<__FUNCTION__<<"\n"\
                << "Detail:"<<exMsg<<"\n";\
        std::string msg = message.str();\
        throw SSDK::CustomException(msg);\
    }

    #define CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ(appendedMsg)\
    catch (SSDK::CustomException& ex )\
    {\
        std::ostringstream message;\
        message << "File:"<<__FILE__<<"\n"\
                << "Line:"<<__LINE__<<"\n"\
                << "Func:"<<__FUNCTION__<<"\n"\
                << "Detail:"<<appendedMsg<<"\n" "\n"\
                << ex.what() <<"\n";\
        std::string msg = message.str();\
        throw SSDK::CustomException(msg);\
    }

    /**
     *  @brief 自定义异常类
     *
     *  @author lynn
     *  @version 1.00 2017-11-25 lynn
     *                note:create it
     */
    class CustomException : public std::exception
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.constructor & destructor

        /*
        *  @brief   将作为参数的异常信息存到成员变量
        *  @param   N/A
        *  @return  异常信息
        */
        CustomException(std::string & message);

        /*
        *  @brief   类的析构函数，占无内容
        *  @param   N/A
        *  @return  N/A
        */
        ~CustomException();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.set & get function

        /*
        *  @brief   获取异常信息
        *  @param   N/A
        *  @return  返回存储的异常信息
        */
        virtual const char * what() const _GLIBCXX_USE_NOEXCEPT override
        {
            return m_originalMsg.data();
        }

    private :
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.member function
        std::string m_originalMsg{"\0"};  //异常信息
    };
}//End of namespace SDK

#endif // CUSTOMEXCEPTION_H
