#include "customexception.hpp"

CustomException::CustomException()
{

}

CustomException::CustomException(std::string &message)
{
    this->m_originalMsg = message;
}

CustomException::~CustomException()
{

}
