#include "protocolbuffer.hpp"

using namespace std;
using namespace SSDK::Archive;
using namespace google::protobuf::compiler;
using namespace google::protobuf;

/**
  * @brief g_pProtocFactory
  *             这是一个在源文件范围内的全库变量, 程序结束时会自动销毁, 不需要进行delete, 使用valgrint不会产生内存泄露
  */
 google::protobuf::DynamicMessageFactory* g_pProtocFactory = new DynamicMessageFactory(
    new google::protobuf::DescriptorPool(google::protobuf::DescriptorPool::generated_pool()));

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

ProtocolBuffer::ProtocolBuffer()
{

}
ProtocolBuffer::ProtocolBuffer(const string& filePath)
{
    loadTypeFromFilePath(filePath);
}
ProtocolBuffer::~ProtocolBuffer()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//read functions

void ProtocolBuffer::loadTypeFromFilePath(const string& filePath)
{
    //判断文件是否存在
    FileInfo fileInfo(filePath);

    if(!fileInfo.exists(filePath))
    {
        THROW_EXCEPTION_WITH_OBJ("File Path[" + filePath + "] is not existed!" );
    }

    auto fileName = fileInfo.getNameWithExtension().toStdString();
    auto foldPath = fileInfo.getParentPath().toStdString();

    DiskSourceTree sourceTree;
    sourceTree.MapPath("", foldPath);
    this->m_importer = unique_ptr<google::protobuf::compiler::Importer>(new Importer(&sourceTree,nullptr) );
    this->m_pFile   = this->m_importer->Import(fileName);
    if(nullptr == m_pFile)
    {
        THROW_EXCEPTION_WITH_OBJ("Failed to load  File [" +  filePath + "]");
    }
}

const Descriptor* ProtocolBuffer::findMessageTypeByName(const string &name)const
{
    CHECK_FILE_DESCRIPTION
            return  this->m_importer->pool()->FindMessageTypeByName(name);
}

uint ProtocolBuffer::fieldCount(const Descriptor *pDescriptor)
{
     CHECK_DESCRIPTION(pDescriptor);
     return pDescriptor->field_count();
}

const FieldDescriptor* ProtocolBuffer::findFieldByName(
        const Descriptor* pDescriptor,
        const string &name)
{
    CHECK_DESCRIPTION(pDescriptor);
    return   pDescriptor->FindFieldByName(name.data());
}
const EnumDescriptor *ProtocolBuffer::findEnumByName(const Descriptor *pDescriptor, const string &name)
{\
    CHECK_DESCRIPTION(pDescriptor);
    return   pDescriptor->FindEnumTypeByName(name.data());
}

string ProtocolBuffer::debugString(const Descriptor* pDescriptor)
{
    CHECK_DESCRIPTION(pDescriptor);
    return pDescriptor->DebugString();
}

string ProtocolBuffer::debugString()
{
     CHECK_FILE_DESCRIPTION;
     return this->m_pFile->DebugString();
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//serializaion & deserialization functions

void ProtocolBuffer::deserializeFromFilePath(Message& message, const string &filePath)
{
    //判断文件的目录是否存在
    FileInfo fileInfo(filePath);
    FileInfo folderPathInfo(fileInfo.getParentPath().toStdString());
    if(!folderPathInfo.exists())
    {
        THROW_EXCEPTION_WITHOUT_OBJ("Folder of File["+ filePath + "] is not existed!");
    }

    int file = open(filePath.c_str(), O_RDONLY | O_BINARY);
    message.ParseFromFileDescriptor(file);
}
void ProtocolBuffer::parseFromStream(Message &message, istream &inputStream)
{
     message.ParseFromIstream(&inputStream);
}

void ProtocolBuffer::serializeToFilePath(Message &message, const string &filePath)
{
    //判断文件的目录是否存在
    FileInfo fileInfo(filePath);
    FileInfo folderPathInfo(fileInfo.getParentPath().toStdString());
    if(!folderPathInfo.exists())
    {
        THROW_EXCEPTION_WITHOUT_OBJ("Folder of File["+ filePath + "] is not existed!");
    }

    ofstream  ofs(filePath.data());
    serializeToStream( message,ofs);
}
void ProtocolBuffer::serializeToStream(Message &message,  ostream &outputStream)
{
    message.SerializeToOstream(&outputStream);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//create functions

 std::unique_ptr<Message>ProtocolBuffer::createMessageInstance(const string &name)
{
    CHECK_FILE_DESCRIPTION;

    const Descriptor* pDescriptor =    this->m_importer->pool()->FindMessageTypeByName(name);

    if(nullptr == pDescriptor)
    {
         THROW_EXCEPTION_WITH_OBJ("Pointer of Message Descriptor is nullptr!" );
    }

    const Message *pMessage = g_pProtocFactory->GetPrototype(pDescriptor);
    return  std::unique_ptr<Message>(pMessage->New());
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

