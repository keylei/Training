#include "customexception.hpp"


SSDK::CustomException::CustomException(std::string &message)
{
    this->m_originalMsg = message;
}

SSDK::CustomException::~CustomException()
{

}

void SSDK::CustomException::addMsg(std::string newMsg)
{
    this->m_originalMsg = newMsg + this->m_originalMsg;
}
