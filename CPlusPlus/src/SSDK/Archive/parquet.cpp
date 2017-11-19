#include "parquet.hpp"

using namespace std;
using namespace SSDK;
using namespace SSDK::Archive;

using namespace ::arrow::io;
using namespace parquet;

using  parquet::Repetition;
using  parquet::Type;
using  parquet::LogicalType;
using  parquet::schema::PrimitiveNode;
using  parquet::schema::GroupNode;


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

Parquet::Parquet()
{

}
Parquet::Parquet(std::vector<parquet::schema::NodePtr>& fields)
{
    setupSchema(fields);
}
Parquet::Parquet(const string& filePath)
{
    readFromFilePath(filePath);
}

Parquet::~Parquet()
{
//    this->closeReader();//这里不需要手动close, 因为FileReader在析构函数中会自己close
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//read functions

void Parquet::readFromFilePath(const string& filePath)
{
    if(FileInfo::exists(filePath))
    {
        this->m_reader = ParquetFileReader::OpenFile(filePath.c_str());
    }
    else
    {

        THROW_EXCEPTION_WITH_OBJ("FilePath:["+filePath+"] is not exist!");
    }
}

void Parquet::printSchema(ostream &stream, bool isPrintValue)
{
    printSchema(stream, std::list<int>(),isPrintValue);
}
void Parquet::printSchema(ostream &stream, const std::list<int>& selectedColumnIndexs, bool isPrintValue)
{
    if(nullptr==this->m_reader.get())
    {
        THROW_EXCEPTION_WITH_OBJ("Reader is null!");
    }
    else
    {
        PrintSchema(this->m_reader->metadata()->schema()->schema_root().get(), stream);
        this->m_reader->DebugPrint(stream,selectedColumnIndexs,isPrintValue);
    }
}
void Parquet::printSchema(string filePath, ostream &stream, bool isPrintValue)
{
    //判断文件路径是否存在
    if( !FileInfo::exists(filePath))
    {
        THROW_EXCEPTION_WITHOUT_OBJ("File ["+ filePath + "] is not existed!" );
    }

    auto reader = ParquetFileReader::OpenFile(filePath.c_str());
    PrintSchema(reader->metadata()->schema()->schema_root().get(), stream);
    reader->DebugPrint(stream,std::list<int>(),isPrintValue);
}
void Parquet::printSchema(string filePath, ostream &stream, const std::list<int> &selectedColumnIndexs, bool isPrintValue)
{
    //判断文件路径是否存在
    if( !FileInfo::exists(filePath))
    {
        THROW_EXCEPTION_WITHOUT_OBJ("File ["+ filePath + "] is not existed!" );
    }

    auto reader = ParquetFileReader::OpenFile(filePath.c_str());
    PrintSchema(reader->metadata()->schema()->schema_root().get(), stream);
    reader->DebugPrint(stream,selectedColumnIndexs,isPrintValue);
}

uint Parquet::rowsPerRowGroup()
{
       //每一个行组的行数, 这里数值参考了parquet官方example中的值
    static uint rowsPerRowCroup{500};
    return rowsPerRowCroup;
}
const FileMetaData * Parquet::fileMetadataPtr()
{
    if(nullptr==this->m_reader.get())
    {
        THROW_EXCEPTION_WITH_OBJ("Reader is null!");
    }
    else if(nullptr==this->m_reader->metadata())
    {
        THROW_EXCEPTION_WITH_OBJ("Metadata is null!");
    }
    else
    {
        return this->m_reader->metadata().get();
    }
}
int64_t Parquet::rows()
{
    return this->fileMetadataPtr()->num_rows();
}
int64_t Parquet::rowGroups()
{
    return this->fileMetadataPtr()->num_row_groups();
}
int64_t Parquet::columns()
{
    return this->fileMetadataPtr()->schema()->group_node()->field_count();
}
Type::type Parquet::columnType(uint columnIndex)
{
    uint maxIndex =  this->fileMetadataPtr()->num_columns() - 1;
    if(columnIndex > maxIndex)
    {
        std::ostringstream message;
        message<<"Column Index["<<columnIndex<<"is more than maxIndex["<<maxIndex;
        std::string msg = message.str();

        THROW_EXCEPTION_WITHOUT_OBJ(msg);
    }
    else
    {
        return this->fileMetadataPtr()->schema()->Column(columnIndex)->physical_type() ;
    }
}
int64_t Parquet::byteSizeOfRowGroup(uint rowGroupIndex)
{
    uint maxIndex =  this->fileMetadataPtr()->num_row_groups() - 1;
    if(rowGroupIndex > maxIndex)
    {
        std::ostringstream message;\
        message<<"Row Group Index["<<rowGroupIndex<<"is more than maxIndex["<<maxIndex;
        std::string msg = message.str();\

        THROW_EXCEPTION_WITHOUT_OBJ(msg);
    }
    else
    {
        return this->fileMetadataPtr()->RowGroup(rowGroupIndex)->total_byte_size();
    }
}
int64_t Parquet::rowsOfRowGroup(uint rowGroupIndex)
{
    uint maxIndex =  this->fileMetadataPtr()->num_row_groups() - 1;
    if(rowGroupIndex > maxIndex)
    {
        std::ostringstream message;\
        message<<"Row Group Index["<<rowGroupIndex<<"is more than maxIndex["<<maxIndex;
        std::string msg = message.str();\

        THROW_EXCEPTION_WITHOUT_OBJ(msg);
    }
    else
    {
        return this->fileMetadataPtr()->RowGroup(rowGroupIndex)->num_rows();
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//write functions

void Parquet::setupSchema(std::vector<parquet::schema::NodePtr>& fields)
{
    if(fields.size() == 0 )
    {
        return;
    }

    this->m_nodePtr = schema::GroupNode::Make("schema", Repetition::REQUIRED, fields);
    this->m_schemaDescriptor.Init(this->m_nodePtr);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
