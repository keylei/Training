#include "message.hpp"

using namespace std;
using namespace SSDK::Asio;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

Message::Message()
{
    this->clearData();
}
Message::Message(const std::vector<char>& data)
{
    if(data.size() == 0)
    {
          return;
    }
    else
    {
          this->writeData(data.data(), data.size());
    }
}
Message::Message(const  char *pData, uint len)
{
    //指针为nullptr或者len为0时，创建空值
    if(nullptr == pData || len == 0)
        return;

    this->writeData(pData, len);
}

Message::~Message()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//write functions

void Message::writeHeader(uint len)
{
    if(0 != len)
    {
        this->m_buff.resize(HEADER_LENGTH + len);
        memset(this->m_buff.data(),'\0', this->m_buff.size());

        if(this->m_bodyLength != len)
        {
            this->m_bodyLength = len;

            //把长度数据写入包头，占8个字节
            char header[HEADER_LENGTH];
            std::sprintf(header,"%8d",len);
            memcpy(this->pHeader(), header, HEADER_LENGTH);
        }
    }
}
void Message::writeData(const  char *pData, uint len)
{
    if(len!=this->m_bodyLength)
    {
        this->writeHeader(len);
    }

    memcpy(this->pBody(), pData, len);
}
void Message::writeData(const std::vector<char> &data)
{
    writeData(data.data(),data.size());
}

void Message::clearData()
{
    memset(this->pHeader(),'\0',this->m_buff.size());
    this->m_buff = vector<char>(HEADER_LENGTH);
    this->m_bodyLength = 0;
    memset(this->pHeader(),'\0',HEADER_LENGTH);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//auxiliary functions

uint64_t Message::parseHeader(char* pHeader)
{
    char header[HEADER_LENGTH] = "";
    std::strncat(header, pHeader, HEADER_LENGTH);
    return std::atoi(header);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
