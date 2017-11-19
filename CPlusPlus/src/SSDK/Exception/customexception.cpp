#include "customexception.hpp"
#include "iostream"

using namespace SSDK::Exception;
using namespace SSDK::TypeTraits;
using namespace std;

//>>>--------------------------------------------------------------------------------
//construct & deconstructor

CustomException::CustomException()
{

}
CustomException::CustomException(string& message, IDisposal* pDisposal)
    :m_orginalMsg(message),
     m_stackTraceMsg(message),
     m_pDisposal(pDisposal)
{
//        this->m_pDisposal = std::shared_ptr<IDisposal>(pDisposal);
}
CustomException::CustomException(const CustomException& customException)
{
    this->m_pDisposal =customException.m_pDisposal;
    this->m_orginalMsg = customException.m_orginalMsg;
    this->m_displayMsg = customException.m_displayMsg;
    this->m_stackTraceMsg = customException.m_stackTraceMsg;
    this->m_handlers = customException.m_handlers;
    this->m_isStackTraceMsgShown = customException.m_isStackTraceMsgShown;
}
CustomException::CustomException( CustomException&& customException)//rvalue copy constructor
{
   this->m_pDisposal =customException.m_pDisposal;
    this->m_orginalMsg = std::move(customException.m_orginalMsg);
    this->m_displayMsg = customException.m_displayMsg;
    this->m_stackTraceMsg = std::move(customException.m_stackTraceMsg);
    this->m_handlers = std::move(customException.m_handlers);
    this->m_isStackTraceMsgShown = std::move(customException.m_isStackTraceMsgShown);
}

CustomException::~CustomException()
{
//    this->dispose();
}

//<<<--------------------------------------------------------------------------------

//>>>--------------------------------------------------------------------------------
//operator function

//lvalue assignment operator function
CustomException& CustomException::operator=(const CustomException& customException)
{
    this->m_pDisposal =customException.m_pDisposal;
    this->m_orginalMsg = customException.m_orginalMsg;
    this->m_stackTraceMsg = customException.m_stackTraceMsg;
    this->m_handlers = customException.m_handlers;
    this->m_displayMsg = customException.m_displayMsg;
    this->m_isStackTraceMsgShown = customException.m_isStackTraceMsgShown;
    return *this;
}

//rvalue assignment operator function
CustomException& CustomException::operator=(CustomException&& customException)
{
  this->m_pDisposal =customException.m_pDisposal;
    this->m_orginalMsg = std::move(customException.m_orginalMsg);
    this->m_stackTraceMsg = std::move(customException.m_stackTraceMsg);
    this->m_handlers = std::move(customException.m_handlers);
    this->m_displayMsg = customException.m_displayMsg;
    this->m_isStackTraceMsgShown = std::move(customException.m_isStackTraceMsgShown);
    return  *this;
}

//<<<--------------------------------------------------------------------------------

//This function is used to set m_handlers
void CustomException::setHandlers( ExceptionHandlers handlers)
{
    //    this->m_handlers.clear();

    //    auto iter = handlers.begin();
    //    while (iter!=handlers.end())
    //    {
    //        this->m_handlers.emplace(iter->first,iter->second);
    //        ++iter;
    //    }
    this->m_handlers = handlers;
}

//This function is used to get exceptionMsg,
//    if m_isStackTraceShown is true ,exceptionMsg is m_stackTraceMsg
//    if m_isStackTraceShown is false,exceptionMsg is m_orgMsg
std::string CustomException::getExceptionMsg() const
{
    std::string temp = "";

    if(this->m_isStackTraceMsgShown)
    {
        temp = stackTraceMsg();
    }
    else
    {
        temp = orginalMsg();
    }

    return temp;
}

//This function is used to get  handler name list
const std::list<std::string> CustomException::getHandlerTypeNameList()const
{
    static list<string> handlerTypeNameList;
    if(handlerTypeNameList.size()==0)
    {
        auto allHandlerTypeNameMap = HandlerType::getMap();
        auto hanlders = this->m_handlers;

        auto iter = hanlders.begin();

        while(iter!=hanlders.end())
        {
            handlerTypeNameList.push_back(allHandlerTypeNameMap[iter->first]);
            iter++;
        }
    }

    return handlerTypeNameList;
}

