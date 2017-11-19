#ifndef TESTPROTOCOLBUFFER_H
#define TESTPROTOCOLBUFFER_H

#include <fstream>

#include <QString>
#include <QObject>

#include "unittester.hpp"
#include "Archive/protocolbuffer.hpp"
#include "Protoc/protocolBuffer.typeCollection.pb.h"
//#include "Protoc/protocolBuffer.performance.pb.h"

using namespace std;
using namespace SSDK;
using namespace SSDK::Archive;

namespace UnitTester
{
    namespace SSDK
    {
    /**
     *  @brief TestProtocolBuffer
     *              测试SSDK中的ProtocolBuffer类
     *
     *  @author rime
     *  @version 1.00 2017-06-05 rime
     *                note:create it
     */
    class TestProtocolBuffer: public QObject
    {
        Q_OBJECT

    private slots:

        void initTestCase()
        {
        }

        /**
         * @brief testStaticCompile
         *             测试静态编译
         *
         * 测试数据:
         *          protocolBuffer.typeCollection.proto
         *
         * 测试内容:
         *          调用protoc静态编译的头文件和源文件, 调用其存取函数及序列化和反序列化函数
         *
         * 测试逻辑:
         *         按照定义的结构创建对象, 调用其序列化接口, 然后反序列化, 如果反序列化得到的对象与
         * 之前创建的对象完全相等, 则测试通过
         */
        void testStaticCompile()
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.创建对象

            protocolBuffer::typeCollection obj;
            obj.set_int32id(1);
            obj.set_int64id(2);
            obj.set_uint32id(3);
            obj.set_uint64id(4);
            obj.set_sint32id(5);
            obj.set_sint64id(6);
            obj.set_fint32id(7);
            obj.set_fint64id(8);
            obj.set_sfint32id(9);
            obj.set_sfint64id(10);
            obj.set_isnull(true);
            obj.set_name("name");
            obj.set_height(0.2);
            obj.set_with(0.223232444);

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //2.序列化对象
            QString filePath = m_parquetDataPath+"typeCollection_staticComplieTest";
            FileInfo fileInfo(filePath.toStdString());
            if(fileInfo.exists())
            {
                fileInfo.remove();
            }

//            fstream output(filePath.toStdString().data(), ios::out | ios::trunc | ios::binary);
//            obj.SerializeToOstream(&output);
//            output.close();

            ProtocolBuffer::serializeToFilePath(obj, filePath.toStdString());

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //3.反序列化对象
            protocolBuffer::typeCollection obj1;
//            fstream input(filePath.toStdString().data(), ios::in | ios::binary);
//            obj1.ParseFromIstream(&input);
//            input.close();
            ProtocolBuffer::deserializeFromFilePath(obj1, filePath.toStdString());

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //4.验证
            QVERIFY(obj.int32id() == obj1.int32id() );
            QVERIFY(obj.int64id() == obj1.int64id() );
            QVERIFY(obj.uint32id() == obj1.uint32id() );
            QVERIFY(obj.uint64id() == obj1.uint64id() );
            QVERIFY(obj.sint32id() == obj1.sint32id() );
            QVERIFY(obj.sint64id() == obj1.sint64id() );
            QVERIFY(obj.fint32id() == obj1.fint32id() );
            QVERIFY(obj.fint64id() == obj1.fint64id() );
            QVERIFY(obj.sfint32id() == obj1.sfint32id() );
            QVERIFY(obj.sfint64id() == obj1.sfint64id() );
            QVERIFY(obj.isnull() == obj1.isnull() );
            QVERIFY(obj.name() == obj1.name() );
            QVERIFY(obj.height() == obj1.height() );
            QVERIFY(obj.with() == obj1.with() );
        }

        /**
         * @brief testDynamicCompile
         *             测试动态编译
         *
         * 测试数据:
         *              protocolBuffer.typeCollection.proto
         *
         * 测试函数:
         *              loadTypeFromFilePath
         *              findMessageTypeByName
         *              findFieldByName
         *              getValue
         *              setValue
         *
         *测试逻辑:
         *         1.动态加载提前定义好的proto文件
         *         2.创建对应的对象
         *         3.给对象赋值
         *         4.序列化对象到二进制文件
         *         5.反序列化二进制文件到对象
         *         6.验证反序列化对象的属性和序列化之前对象的属性是否相等
         */
        void testDynamicCompile()
        {
             protocolBuffer::typeCollection obj;

             QString filePath = m_parquetDataPath+"protocolBuffer.typeCollection.proto";
             ProtocolBuffer protoc(filePath.toStdString());

             //>>>-------------------------------------------------------------------------------------------------------------------------------------
             //1. 获取其message
             auto message = protoc.findMessageTypeByName("protocolBuffer.typeCollection");
             uint fieldCount = ProtocolBuffer::fieldCount(message);
             QVERIFY(fieldCount == 15);
             std::string debugString = protoc.debugString();
             qDebug()<<QString::fromStdString( debugString);


             //>>>-------------------------------------------------------------------------------------------------------------------------------------
             //2.创建对象并赋值
             auto newObj = protoc.createMessageInstance("protocolBuffer.typeCollection");

             auto pField =  ProtocolBuffer::findFieldByName(message, "int32ID");
             ProtocolBuffer::setValue(newObj, pField, 1);

             pField = ProtocolBuffer::findFieldByName(message, "int64ID");
             ProtocolBuffer::setValue(newObj, pField, 2);

             pField = ProtocolBuffer::findFieldByName(message, "uint32ID");
             ProtocolBuffer::setValue(newObj, pField, 3);

              pField = ProtocolBuffer::findFieldByName(message, "uint64ID");
             ProtocolBuffer::setValue(newObj, pField, 4);

              pField = ProtocolBuffer::findFieldByName(message, "sint32ID");
             ProtocolBuffer::setValue(newObj, pField, 5);

              pField = ProtocolBuffer::findFieldByName(message, "sint64ID");
             ProtocolBuffer::setValue(newObj, pField, 6);

              pField =ProtocolBuffer::findFieldByName(message, "fint32ID");
             ProtocolBuffer::setValue(newObj, pField, 7);

              pField = ProtocolBuffer::findFieldByName(message, "fint64ID");
             ProtocolBuffer::setValue(newObj, pField, 8);

              pField = ProtocolBuffer::findFieldByName(message, "sfint32ID");
             ProtocolBuffer::setValue(newObj, pField, 9);

             pField = ProtocolBuffer::findFieldByName(message, "sfint64ID");
            ProtocolBuffer::setValue(newObj, pField, 10);

              pField =ProtocolBuffer::findFieldByName(message, "isNull");
             ProtocolBuffer::setValue(newObj, pField, true);

              pField = ProtocolBuffer::findFieldByName(message, "name");
             ProtocolBuffer::setValue(newObj, pField,  std::string("name"));

              pField = ProtocolBuffer::findFieldByName(message, "height");
             ProtocolBuffer::setValue(newObj, pField, 0.2);

              pField = ProtocolBuffer::findFieldByName(message, "with");
             ProtocolBuffer::setValue(newObj, pField, 0.223232444);

             pField = ProtocolBuffer::findFieldByName(message, "enumVal");
             ProtocolBuffer::setValue(newObj, pField, 1);

             //>>>-------------------------------------------------------------------------------------------------------------------------------------
             //3.序列化
             QString objFilePath = m_parquetDataPath+QString("typeCollection_dynamicComplieTest");
             ProtocolBuffer::serializeToFilePath(*newObj.get(), objFilePath.toStdString());

             //>>>-------------------------------------------------------------------------------------------------------------------------------------
             //4.反序列化
             auto newObj1 = protoc.createMessageInstance("protocolBuffer.typeCollection");
             ProtocolBuffer::deserializeFromFilePath(*newObj1.get(), objFilePath.toStdString());

             //>>>-------------------------------------------------------------------------------------------------------------------------------------
             //5.读取验证
             pField =  ProtocolBuffer::findFieldByName(message, "int32ID");
             QVERIFY(ProtocolBuffer::getValue<int32_t>(newObj, pField) == ProtocolBuffer::getValue<int32_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "int64ID");
             QVERIFY(ProtocolBuffer::getValue<int64_t>(newObj, pField) == ProtocolBuffer::getValue<int64_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "uint32ID");
             QVERIFY(ProtocolBuffer::getValue<uint32_t>(newObj, pField) == ProtocolBuffer::getValue<uint32_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "uint64ID");
             QVERIFY(ProtocolBuffer::getValue<uint64_t>(newObj, pField) == ProtocolBuffer::getValue<uint64_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "sint32ID");
             QVERIFY(ProtocolBuffer::getValue<int32_t>(newObj, pField) == ProtocolBuffer::getValue<int32_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "sint64ID");
             QVERIFY(ProtocolBuffer::getValue<int64_t>(newObj, pField) == ProtocolBuffer::getValue<int64_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "fint32ID");
             QVERIFY(ProtocolBuffer::getValue<uint32_t>(newObj, pField) == ProtocolBuffer::getValue<uint32_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "fint64ID");
             QVERIFY(ProtocolBuffer::getValue<uint64_t>(newObj, pField) == ProtocolBuffer::getValue<uint64_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "sfint32ID");
             QVERIFY(ProtocolBuffer::getValue<int32_t>(newObj, pField) == ProtocolBuffer::getValue<int32_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "sfint64ID");
             QVERIFY(ProtocolBuffer::getValue<int64_t>(newObj, pField) == ProtocolBuffer::getValue<int64_t>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "isNull");
             QVERIFY(ProtocolBuffer::getValue<bool>(newObj, pField) == ProtocolBuffer::getValue<bool>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "height");
             QVERIFY(ProtocolBuffer::getValue<float>(newObj, pField) == ProtocolBuffer::getValue<float>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "with");
             QVERIFY(ProtocolBuffer::getValue<double>(newObj, pField) == ProtocolBuffer::getValue<double>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "enumVal");
             QVERIFY(ProtocolBuffer::getValue<int>(newObj, pField) == ProtocolBuffer::getValue<int>(newObj1, pField));

             pField =  ProtocolBuffer::findFieldByName(message, "name");
             QVERIFY(ProtocolBuffer::getValue<string>(newObj, pField) == ProtocolBuffer::getValue<string>(newObj1, pField));
        }

        void cleanupTestCase()
        {

        }

    private:
        //测试数据路径
        QString m_parquetDataPath{dataPath+"ProtoBuf/"};


    };//End of TestProtocolBuffer

    //注册测试类
    DECLARE_TEST(TestProtocolBuffer)
    }//End of namespace SSDK
}//End of namespace TestParquet

#endif // TESTPROTOCOLBUFFER_H
