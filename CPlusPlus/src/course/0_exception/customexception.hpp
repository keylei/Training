#ifndef CUSTOMEXCEPTION_HPP
#define CUSTOMEXCEPTION_HPP

#include <exception>
#include <string>
#include <sstream>
#include <iostream>

#define THROW_EXCEPTION(exMsg)\
{\
     std::ostringstream message;\
     message<<"File: "<<__FILE__<<"\n"\
                  <<"Line:"<<__LINE__<<"\n"\
                  <<"Func:"<<__FUNCTION__<<"\n"\
                  <<"Detail:"<< exMsg <<"\n";\
     std::string msg = message.str();\
     throw  CustomException(msg);\
}

class CustomException: public std::exception
{
public:

    CustomException();
    CustomException(std::string& message);
    virtual ~CustomException();

    const std::string originalMsg ( )const{return this->m_originalMsg;}

    virtual const char* what() const _GLIBCXX_USE_NOEXCEPT override
    {
        return m_originalMsg.data();
    }


private:
    std::string m_originalMsg;
};

#endif // CUSTOMEXCEPTION_HPP
