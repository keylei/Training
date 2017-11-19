#include "json.hpp"

using namespace std;
using namespace rapidjson;
using namespace SSDK::Archive;
using namespace SSDK::Exception;
using namespace SSDK::TypeTraits;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

Json::Json():m_writer(m_buf)
{

}
Json::Json(const string &str,bool isFromString):m_writer(m_buf)
{
    if(!isFromString)
        this->loadFromFile(str);
    else
        this->parseFromString(str);
}
Json::Json(const QString &str,bool isFromString):m_writer(m_buf)
{
    if(!isFromString)
        this->loadFromFile(str);
    else
        this->parseFromString(str);
}

Json::~Json()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//read function

void Json::loadFromFile( const string &filePath)
{
    try
        {
            FILE* pFile = fopen(filePath.data(),"r");
            if(pFile)
            {
                //>>>--------------------------------------------------------------------------------
                //1.获取需要读取的字符串
                ifstream input;
                input.open(filePath);
                if(!input.is_open())
                {
                    return;
                }

                std::ostringstream out;
                out << input.rdbuf();
                std::string context = out.str();
                input.close();

                //>>>--------------------------------------------------------------------------------
                //2.读取字符串
                parseFromString(context);
            }
            else
            {
                THROW_EXCEPTION("Open File["+filePath+"] error!",this);
            }
        }
        CATCH_THROW_EXCEPTION(string("read Json from file[")+filePath+string("] error!"),this);
}
void Json::loadFromFile( const QString& filePath)
{
    loadFromFile(filePath.toStdString());
}

void Json::parseFromString(const string & jsonString)
{
    try
    {
        if(this->m_doc.Parse<rapidjson::kParseDefaultFlags>(jsonString.c_str()).HasParseError())
            return ;
        this->m_doc.Accept(this->m_writer);
    }
    CATCH_THROW_EXCEPTION(string("parse Json  string[")+jsonString+string("] error!"),this);
}
void Json::parseFromString(const QString &filePath)
{
    parseFromString(filePath.toStdString());
}

const char *Json::toString()
{
    this->m_doc.Accept(this->m_writer);
    return this->m_buf.GetString();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//write function

void Json::writeToFile( const string& filePath)
{
    try
       {
           this->m_buf.Clear();//一定要先clear，否则的话，完成accept后，字符串会发生叠加
           this->m_doc.Accept(this->m_writer);//获取Json的字符串形式，然后退出
           auto pStr = this->m_buf.GetString();
           ofstream ofs(filePath);
           ofs<<pStr;
       }
       CATCH_THROW_EXCEPTION(string("Write Json to file[")+filePath+string("] error!"),this);
}
void Json::writeToFile(const QString& filePath)
{
    writeToFile(filePath.toStdString());
}

void Json::startArray()
{
    this->m_writer.StartArray();
}
void Json::endArray()
{
    this->m_writer.EndArray();
}

void Json::startObject()
{
    this->m_writer.StartObject();
}
void Json::endObject()
{
    this->m_writer.EndObject();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//query string functions

const char *Json::queryString(const char *parentKey, const char *childKey)
{
    bool isFound = false;
    auto& childVal = queryValue(parentKey,childKey,isFound);//找出子Value
    if(isFound)
    {
        bool isTypeMatched = false;
        auto val = queryString(childVal,isTypeMatched);
        if(!isTypeMatched)
        {
             THROW_EXCEPTION("Type of Member["+std::string(childKey)+"] is not string type!",this);
        }
        else
        {
            return val;
        }
    }
    else
    {
           THROW_EXCEPTION("Member["+std::string(childKey)+"] is not found!",this);
    }
}
const char *Json::queryString(const char *key)
{
    bool isFound = false;
    auto& childVal = queryValue(key,isFound);//找出子Value
    if(isFound)
    {
        bool isTypeMatched = false;
        auto val = queryString(childVal,isTypeMatched);
        if(!isTypeMatched)
        {
            THROW_EXCEPTION("Type of Member["+std::string(key)+"] is not matched!",this);
        }
        else
        {
            return val;
        }
    }
    else
    {
        THROW_EXCEPTION("Member["+std::string(key)+"] is not found!",this);
    }
}

const char *Json::queryString(Value &value, bool& isTypeMatched)
{
    isTypeMatched = false;
    if( value.IsString())
    {
        isTypeMatched = true;
        return (const char*)(value.GetString());
    }
    else if(value.IsNull())
    {
        isTypeMatched = true;
        return nullptr;
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//query value functions

Value &Json::queryValue(const char* key, bool &isFound)
{
    if(nullptr == key)
    {
        THROW_EXCEPTION("ParentKey is null!",this);
    }

    isFound = false;
    auto& val = queryValue(this->m_doc,key,isFound);
    if(isFound)
    {
        return val;
    }
}

Value&  Json::queryValue( rapidjson::Value& obj, const char* key, bool& isFound)
{
    if(obj.IsObject())
    {
        auto resIter = obj.FindMember(key);
        if(resIter!=0)//在当前层级找到key的value
        {
            isFound = true;
            return resIter->value;
        }
        else//没有找到
        {
            //遍历子对象
            for(auto subIter = obj.MemberBegin(); subIter != obj.MemberEnd(); ++subIter )
            {
                auto& res  = queryValue(subIter->value, key, isFound);//从子对象中查找
                if(isFound)
                {
                    return res;
                }
            }
        }
    }
}

Value &Json::queryValue(const char* parentKey, const char* childKey, bool &isFound)
{
    if(nullptr == parentKey)
    {
        THROW_EXCEPTION("ParentKey is null!",this);
    }

    if(nullptr == childKey)
    {
        THROW_EXCEPTION("ChildKey is null!",this);
    }

    isFound = false;
    auto& parentVal = queryValue(this->m_doc,parentKey,isFound);//找出父Value
    auto& childVal = queryValue(parentVal,childKey,isFound);//找出子Value
    if(isFound)
    {
        return childVal;
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//query array functions

Value &Json::queryArray(const char* parentObjKey, const char* arrayName, bool &isFound)
{
    isFound = false;
    auto& parentVal = queryArray(this->m_doc, parentObjKey, isFound);
    return  queryArray(parentVal,arrayName,isFound)  ;
}
Value& Json::queryArray(const char* arrayName,bool& isFound)
{
    isFound = false;
    return queryArray(this->m_doc, arrayName, isFound);
}
Value&  Json::queryArray( rapidjson::Value& parentObj, const char* arrayName,  bool& isFound)
{
    isFound = false;
    auto& val =  queryValue(parentObj, arrayName, isFound );
    if(val.IsArray()&&isFound)
    {
        isFound = true;
        return val;
    }
    else
    {
        isFound = false;
    }
}

int Json::getArrayCount(const char *parentObjKey, const char *arrayName)
{
    bool isFound = false;
    auto& val = queryValue(parentObjKey,arrayName,isFound);
    if(isFound)
    {
        return val.GetSize();
    }
    else
    {
        return -1;
    }
}
int Json::getArrayCount(const char *arrayName)
{
    bool isFound = false;
    auto& val = queryValue(this->m_doc,arrayName,isFound);
    if(isFound)
    {
        return val.GetSize();
    }
    else
    {
        return -1;
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//modify string functions

bool Json::modifyString(Value &val, const char *value)
{
    if(val.IsString()||val.IsNull())
    {
        val.SetString(value, strlen(value));
        return true;
    }
    else
    {
        return false;
    }
}

void Json::modifyString(const char *parentKey, const char *childKey, const char *value)
{
    using namespace rapidjson;
    bool isFound{false};
    auto& val = queryValue(parentKey,childKey,isFound);
    if(isFound)//对于rapidjson v1.0 需要判断是否为0, 对于最新的v1.1 要判断是否为EndMember
    {
        if(!modifyString(val, value))
        {
            THROW_EXCEPTION("Member["+std::string(childKey)+"] is bool type!",this);
        }
    }
    else
    {
        THROW_EXCEPTION("Member["+std::string(childKey)+"] is not found!",this);
    }
}

void Json::modifyString(const char *key, const char *value)
{
    using namespace rapidjson;
    bool isFound{false};
    auto& val = queryValue(key,isFound);
    if(isFound)//对于rapidjson v1.0 需要判断是否为0, 对于最新的v1.1 要判断是否为EndMember
    {
        if(!modifyString(val, value))
        {
            THROW_EXCEPTION("Member["+std::string(key)+"] is bool type!",this);
        }
    }
    else
    {
        THROW_EXCEPTION("Member["+std::string(key)+"] is not found!",this);
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//modify array functions

bool Json::pushValBackToArray(const char *parentKey, const char *childkey, Value & newElementVal)
{
    bool isFound = false;
    auto& val =  queryArray(parentKey,childkey,isFound);
    if(isFound)
    {
        val.PushBack(newElementVal, this->m_doc.GetAllocator() );
    }
    else
    {
        return false;
    }
}
bool Json::pushValBackToArray(const char *key, Value & newElementVal)
{
    bool isFound = false;
    rapidjson::Value& val =  queryArray(this->m_doc,key,isFound);
    if(isFound)
    {
        val.PushBack(newElementVal, this->m_doc.GetAllocator() );
    }
    else
    {
        return false;
    }
}

bool Json::pushStringBackToArray(const char *parentKey, const char *childKey, const char *newElementVal)
{
              rapidjson::Value val(newElementVal, strlen(newElementVal));
              return pushValBackToArray(parentKey,childKey,val);
}
bool Json::pushStringBackToArray(const char *key, const char *newElementVal)
{
          rapidjson::Value val(newElementVal, strlen(newElementVal));
          return pushValBackToArray(key,val);
}

bool Json::popBackFromArray(const char *parentKey, const char *childKey)
{
    bool isFound = false;
    auto& val = queryArray(parentKey,childKey,isFound);
    if(isFound)
    {
        val.PopBack();
    }
    else
    {
        return false;
    }
}
bool Json::popBackFromArray(const char *key)
{
    bool isFound = false;
    auto& val = queryArray(this->m_doc,key,isFound);
    if(isFound)
    {
        val.PopBack();
    }
    else
    {
        return false;
    }
}

bool Json::clearArray(const char *parentKey,const char *childKey)
{
    bool isFound = false;
    auto& val  = queryArray(parentKey,childKey,isFound);
    if(isFound)
    {
        val.Clear();
    }
    else
    {
        return false;
    }
}
bool Json::clearArray(const char *key)
{
    bool isFound = false;
    auto& val  = queryArray(this->m_doc,key,isFound);
    if(isFound)
    {
        val.Clear();
    }
    else
    {
        return false;
    }
}

bool Json::modifyStringElementOfArrayBasedOnIndex(const char *parentKey, const char *childKey, int index, const char *value)
{
    using namespace rapidjson;

    bool isFound = false;
    auto& val = queryValue(parentKey,childKey,isFound);
    if(isFound && val.IsArray())
    {
           if(index<0 || index > val.GetSize())
           {
               std::ostringstream stream;
               stream<<"Index["<<index<<"] is invaild, it must be in[0,"<<val.GetSize()<<"]";
               THROW_EXCEPTION( stream.str() ,this);
           }
           else
           {
               modifyString(val[index], value);
           }
    }
    else
    {
         THROW_EXCEPTION("Member["+std::string(childKey)+"] is not found!",this);
    }
}
bool Json::modifyStringElementOfArrayBasedOnIndex(const char *key, int index, const char *value)
{
    using namespace rapidjson;

    bool isFound = false;
    auto& val = queryValue(this->m_doc,key,isFound);
    if(isFound && val.IsArray())
    {
           if(index<0 || index > val.GetSize())
           {
               std::ostringstream stream;
               stream<<"Index["<<index<<"] is invaild, it must be in[0,"<<val.GetSize()<<"]";
               THROW_EXCEPTION( stream.str() ,this);
           }
           else
           {
               modifyString(val[index], value);
           }
    }
    else
    {
         THROW_EXCEPTION("Member["+std::string(key)+"] is not found!",this);
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//modify object function

void Json::addValueToObject(const char *parentKey, const char *childKey,  const char* memName,Value& childValue)
{
    bool isFound{false};
    auto& parentObj = queryValue(parentKey, childKey,isFound);
    if(!isFound  && !parentObj.IsObject())
    {
        THROW_EXCEPTION("Object["+std::string(parentKey)+"] is not found!",this);
    }
    else
    {
        parentObj.AddMember(memName,childValue,this->m_doc.GetAllocator());
    }
}
void Json::addValueToObject(const char *key,  const char* memName,Value &childValue)
{
    bool isFound{false};
    auto& parentObj = queryValue(this->m_doc, key,isFound);
    if(!isFound  && !parentObj.IsObject())
    {
        THROW_EXCEPTION("Object["+std::string(key)+"] is not found!",this);
    }
    else
    {
        parentObj.AddMember(memName,childValue,this->m_doc.GetAllocator());
    }
}

void Json::addStringToObject(const char *parentKey, const char *childKey, const char *memName, const char* memVal)
{
    bool isFound{false};
    auto& parentObj= queryValue(parentKey, childKey,isFound);
    if(!isFound  && !parentObj.IsObject())
    {
        THROW_EXCEPTION("Object["+std::string(childKey)+"] is not found!",this);
    }
    else
    {
        parentObj.AddMember(memName,memVal,this->m_doc.GetAllocator());
    }
}
void Json::addStringToObject( const char *key, const char *memName, const char* memVal)
{
    bool isFound{false};
    auto& parentObj= queryValue(this->m_doc, key,isFound);
    if(!isFound  && !parentObj.IsObject())
    {
        THROW_EXCEPTION("Object["+std::string(key)+"] is not found!",this);
    }
    else
    {
        parentObj.AddMember(memName,memVal,this->m_doc.GetAllocator());
    }
}

void Json::removeMemberFromObject(const char *parentKey, const char *childKey,const char *memName)
{
    bool isFound{false};
    auto& parentObj = queryValue(parentKey, childKey,isFound);
    if(!isFound && !parentObj.IsObject())
    {
        THROW_EXCEPTION("Object["+std::string(childKey)+"] is not found!",this);
    }
    else
    {
        parentObj.RemoveMember(memName);
    }
}
void Json::removeMemberFromObject(const char *key, const char *memName)
{
    bool isFound{false};
    auto& parentObj = queryValue(this->m_doc, key,isFound);
    if(!isFound && !parentObj.IsObject())
    {
        THROW_EXCEPTION("Object["+std::string(key)+"] is not found!",this);
    }
    else
    {
        parentObj.RemoveMember(memName);
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
