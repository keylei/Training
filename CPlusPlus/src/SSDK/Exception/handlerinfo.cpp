#include "handlerinfo.hpp"

using namespace std;
using namespace SSDK;
using namespace SSDK::Exception;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

HandlerInfo::HandlerInfo()
{

}

HandlerInfo::HandlerInfo(HandlerType handlerType,std::string msg,HandlerFunc func):
    m_handlerType(handlerType),
    m_sourceMsg(msg),
    m_func(func)
{

}

HandlerInfo::HandlerInfo(
        HandlerType handlerType,
        std::string msg,
        QString displayMsg,
        HandlerFunc func):
    m_handlerType(handlerType),
    m_sourceMsg(msg),
    m_displayMsg(displayMsg),
    m_func(func)
{

}

HandlerInfo::HandlerInfo(
        HandlerType handlerType,
        QString displayMsg,
        HandlerFunc func):
    m_handlerType(handlerType),
    m_displayMsg(displayMsg),
    m_func(func)
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

