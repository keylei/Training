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
    //    this->m_writer.SetMaxDecimalPlaces(10);
}
Json::Json(const string &str,bool isFromString):m_writer(m_buf)
{
    if(!isFromString)
        this->loadFromFile(str);
    else
        this->parseFromString(str);

    //     this->m_writer.SetIndent(10);
}
Json::Json(const QString &str,bool isFromString):m_writer(m_buf)
{
    if(!isFromString)
        this->loadFromFile(str);
    else
        this->parseFromString(str);

    //     this->m_writer.SetMaxDecimalPlaces(10);
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
            THROW_EXCEPTION_WITH_OBJ("Open File["+filePath+"] error!");
        }
    }
    CATCH_THROW_EXCEPTION_WITH_OBJ(string("read Json from file[")+filePath+string("] error!"));
}
void Json::loadFromFile( const QString& filePath)
{
    loadFromFile(filePath.toStdString());
}

//void Json::loadFromDoc(const Document &doc)
//{
//    parseFromString(doc.);
//    this->m_isReAccept = false;
//}

void Json::parseFromString(const char*  jsonStr)
{
    try
    {
        if(this->m_doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr).HasParseError())
            return ;

        this->m_doc.Accept(this->m_writer);
        this->m_isReAccept = false;
    }
    CATCH_THROW_EXCEPTION_WITH_OBJ(string("parse Json  string[")+jsonStr+string("] error!"));
}
void Json::parseFromString(const string & jsonString)
{
    try
    {
        if(this->m_doc.Parse<rapidjson::kParseDefaultFlags>(jsonString.c_str()).HasParseError())
            return ;

        this->m_doc.Accept(this->m_writer);
        this->m_isReAccept = false;
    }
    CATCH_THROW_EXCEPTION_WITH_OBJ(string("parse Json  string[")+jsonString+string("] error!"));
}
void Json::parseFromString(const QString &filePath)
{
    parseFromString(filePath.toStdString());
}

const char *Json::toString()
{
    if(this->m_isReAccept)
    {
        this->m_doc.Accept(this->m_writer);
        this->m_isReAccept = false;
    }
    return this->m_buf.GetString();
}

Json::ValueType Json::docType()
{
    if(this->m_doc.IsArray())
        return ValueType::ARRAY;
    else
        return ValueType::OBJECT;
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//write function

void Json::writeValue(const char* value)//char*
{
    m_writer.String(value);
}

void Json::writeToFile( const string& filePath)
{
    try
    {
        if(m_isReAccept)
        {
            this->m_buf.Clear();//一定要先clear，否则的话，完成accept后，字符串会发生叠加
            this->m_doc.Accept(this->m_writer);//获取Json的字符串形式，然后退出
            this->m_isReAccept = true;
        }

        auto pStr = this->m_buf.GetString();
        ofstream ofs(filePath);
        ofs<<pStr;
    }
    CATCH_THROW_EXCEPTION_WITH_OBJ(string("Write Json to file[")+filePath+string("] error!"));
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
            THROW_EXCEPTION_WITH_OBJ("Type of Member["+std::string(childKey)+"] is not string type!");
        }
        else
        {
            return val;
        }
    }
    else
    {
        THROW_EXCEPTION_WITH_OBJ("Member["+std::string(childKey)+"] is not found!");
    }
}
const char *Json::queryString(const char *key)
{
    return queryString(nullptr, key);
}

const char *Json::queryString(Value &value, bool& isTypeMatched)
{
    isTypeMatched = false;
    if( value.IsString())
    {
        isTypeMatched = true;
        return (const char*)(value.GetString());
    }
    else
    {
        isTypeMatched = true;
        return nullptr;
    }
}

const char *Json::queryString(Value &value, const char *key, bool& isFound)
{
    isFound = false;
    auto& val = queryValue(value,key, isFound);
    return queryString(val,isFound);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//query value functions

Value &Json::queryValue(const char* key, bool &isFound)
{
    return queryValue(nullptr,key,isFound);
}

//注意:这里返回引用的话, 由于无法返回一个空引用,无论抛异常或者还是返回nullptr都会存在一个警告
Value&  Json::queryValue( rapidjson::Value& obj, const char* key, bool& isFound)
{
    if(obj.IsObject())
    {
        auto resIter = obj.FindMember(key);
        if(resIter!=obj.MemberEnd())//在当前层级找到key的value
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
    //注意:这里返回引用的话, 由于无法返回一个空引用,无论抛异常或者还是返回nullptr都会存在一个警告
}

Value &Json::queryValue(const char* parentKey, const char* childKey, bool &isFound)
{
    isFound = false;
    if(nullptr!=parentKey)
    {
        auto& parentVal = queryValue(this->m_doc,parentKey,isFound);//找出父Value
        return queryValue(parentVal,childKey,isFound);//找出子Value
    }
    else
    {
        return  queryValue(this->m_doc,childKey,isFound);//找出子Value
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//query array functions

Value &Json::queryArray(const char* parentObjKey, const char* arrayName, bool &isFound)
{
    isFound = false;
    if(nullptr != parentObjKey)
    {
        auto& parentVal = queryValue(parentObjKey, parentObjKey, isFound);
        return  queryArray(parentVal,arrayName,isFound)  ;
    }
    else if(nullptr != arrayName)
    {
        return queryArray(this->m_doc,arrayName,isFound);
    }
    else
    {
        return this->m_doc;
    }
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
    }
    else
    {
        isFound = false;
    }

    return val;
}

const char *Json::queryStringOfDocArray( int index, const char *elementName)
{
    if(nullptr == elementName)
    {
        THROW_EXCEPTION_WITH_OBJ("Element Name can not be nullptr");
    }

    if(this->m_doc.IsArray())
    {
        int elementCnt = this->m_doc.Size();
        if(index<0 || index>elementCnt-1)
        {
            std::ostringstream stream;
            stream<<"Index["<<index<<"] is invaild, it must be in[0,"<<elementCnt - 1<<"]";
            THROW_EXCEPTION_WITH_OBJ( stream.str() );
        }
        else
        {
            bool isFound {false};
            auto& value = queryValue( this->m_doc[index],elementName,isFound);

            if(!isFound)
            {
                THROW_EXCEPTION_WITH_OBJ("Array[Name:"+std::string(elementName)+"] is not found!" );
            }
            else
            {
                bool isMatched{false};
                return queryString(value,isMatched);
            }
        }
    }
    else
    {
        THROW_EXCEPTION_WITH_OBJ("Doc must be array type");
    }
}

int Json::getArrayCount(const char *parentObjKey, const char *arrayName)
{
    bool isFound = false;
    auto& val = queryValue(parentObjKey,arrayName,isFound);
    if(isFound)
    {
        return val.Size();
    }
    else
    {
        return -1;
    }
}
int Json::getArrayCount(const char *arrayName)
{
    if(nullptr!=arrayName)
        return getArrayCount(nullptr,arrayName);
    else
    {
        if(!this->doc().IsArray())
        {
            THROW_EXCEPTION_WITH_OBJ("ArrayName cannot be nullptr for array root!");
        }
        else
        {
            return this->m_doc.Size();
        }
    }
}
int Json::getArrayCount()
{
    if(this->docType() == ValueType::ARRAY)
        return this->m_doc.Size();
    else
        return -1;
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
            THROW_EXCEPTION_WITH_OBJ("Member["+std::string(childKey)+"] is bool type!");
        }

        this->m_isReAccept = true;
    }
    else
    {
        THROW_EXCEPTION_WITH_OBJ("Member["+std::string(childKey)+"] is not found!");
    }
}

void Json::modifyString(const char *key, const char *value)
{
    modifyString(nullptr,key,value);
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
        this->m_isReAccept = true;
    }
    else
    {
        return false;
    }

    return true;
}
bool Json::pushValBackToArray(const char *key, Value & newElementVal)
{
    return pushValBackToArray(nullptr, key,newElementVal);
}

bool Json::pushStringBackToArray(const char *parentKey, const char *childKey, const char *newElementVal)
{
    rapidjson::Value val(newElementVal, strlen(newElementVal));
    return pushValBackToArray(parentKey,childKey,val);
}
bool Json::pushStringBackToArray(const char *key, const char *newElementVal)
{
    return pushStringBackToArray(nullptr,key,newElementVal);
}

bool Json::popBackFromArray(const char *parentKey, const char *childKey)
{
    bool isFound = false;
    auto& val = queryArray(parentKey,childKey,isFound);
    if(isFound)
    {
        val.PopBack();
        this->m_isReAccept = true;
        return true;
    }
    else
    {
        return false;
    }
}
bool Json::popBackFromArray(const char *key)
{
    return popBackFromArray(nullptr,key);
}

bool Json::clearArray(const char *parentKey,const char *childKey)
{
    bool isFound = false;
    auto& val  = queryArray(parentKey,childKey,isFound);
    if(isFound)
    {
        val.Clear();
        this->m_isReAccept = true;
        return true;
    }
    else
    {
        return false;
    }
}
bool Json::clearArray(const char *key)
{
    return clearArray(nullptr,key);
}

bool Json::modifyStringElementOfArrayBasedOnIndex(const char *parentKey, const char *childKey, uint index, const char *value)
{
    using namespace rapidjson;

    bool isFound = false;
    auto& val = queryValue(parentKey,childKey,isFound);
    if(isFound && val.IsArray())
    {
        if(index > val.Size() - 1)
        {
            std::ostringstream stream;
            stream<<"Index["<<index<<"] is invaild, it must be in[0,"<<val.Size()<<"]";
            THROW_EXCEPTION_WITH_OBJ( stream.str() );
        }
        else
        {
            modifyString(val[index], value);
        }

        return true;
    }
    else
    {
        return false;
        //         THROW_EXCEPTION("Member["+std::string(childKey)+"] is not found!",this);
    }
}
bool Json::modifyStringElementOfArrayBasedOnIndex(const char *key, uint index, const char *value)
{
    return modifyStringElementOfArrayBasedOnIndex(nullptr,key,index,value);
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
        THROW_EXCEPTION_WITH_OBJ("Object["+std::string(parentKey)+"] is not found!");
    }
    else
    {
        parentObj.AddMember(Value::StringRefType(memName),childValue,this->m_doc.GetAllocator());
        this->m_isReAccept = true;
    }
}
void Json::addValueToObject(const char *key,  const char* memName,Value &childValue)
{
    addValueToObject(nullptr,key,memName,childValue);
}

void Json::addStringToObject(const char *parentKey, const char *childKey, const char *memName, const char* memVal)
{
    bool isFound{false};
    auto& parentObj= queryValue(parentKey, childKey,isFound);
    if(!isFound  && !parentObj.IsObject())
    {
        THROW_EXCEPTION_WITH_OBJ("Object["+std::string(childKey)+"] is not found!");
    }
    else
    {
        parentObj.AddMember(Value::StringRefType(memName),Value::StringRefType(memVal),this->m_doc.GetAllocator());
        this->m_isReAccept = true;
    }
}
void Json::addStringToObject( const char *key, const char *memName, const char* memVal)
{
    addStringToObject(nullptr,key,memName,memVal);
}

void Json::removeMemberFromObject(const char *parentKey, const char *childKey,const char *memName)
{
    bool isFound{false};
    auto& parentObj = queryValue(parentKey, childKey,isFound);
    if(!isFound && !parentObj.IsObject())
    {
        THROW_EXCEPTION_WITH_OBJ("Object["+std::string(childKey)+"] is not found!");
    }
    else
    {
        parentObj.RemoveMember(memName);
        this->m_isReAccept = true;
    }
}
void Json::removeMemberFromObject(const char *key, const char *memName)
{
    removeMemberFromObject(nullptr,key,memName);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
