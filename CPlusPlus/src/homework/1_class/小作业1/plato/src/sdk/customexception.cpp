#include "customexception.hpp"


SSDK::CustomException::CustomException(std::string &message)
{
    this->m_originalMsg = message;
}

SSDK::CustomException::~CustomException()
{

}
