#ifndef TESTPARQUET_HPP
#define TESTPARQUET_HPP

#include <math.h>

#include <QString>
#include <QObject>

#include "unittester.hpp"
#include "Archive/parquet.hpp"
#include "Exception/customexception.hpp"
#include "commontool.hpp"

using namespace std;
using namespace SSDK;
using namespace SSDK::Archive;
using namespace SSDK::Exception;

using namespace ::arrow::io;
using parquet::Repetition;
using parquet::Type;
using parquet::LogicalType;
using parquet::schema::PrimitiveNode;
using parquet::schema::GroupNode;

namespace UnitTester
{
    namespace SSDK
    {
        /**
         *  @brief TestParquet
         *              测试SSDK中的Parquet类
         *
         *  @author rime
         *  @version 1.00 2017-06-04 rime
         *                note:create it
         */
        class TestParquet:public QObject
        {
            Q_OBJECT

        private slots:

            void initTestCase()
            {
            }

            /**
             * @brief testRead
             *             测试Parquet的读取
             *
             * 测试数据:
             *          alltypes_plain.snappy.parquet(来自于官方测试文件, 包含了所有类型)
             *
             * 测试函数:
             *          1.rows/rowGroups/columns/columnType(读取基本属性)
             *          2.readIndicatedColumn(查询指定列)
             *             readAllColumns(查询所有列)
             */
            void testRead()
            {
                string filePath  =  (m_parquetDataPath+"alltypes_plain.snappy.parquet").toStdString();
                Parquet parquet(filePath);

                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //1.验证基本属性
                QVERIFY(parquet.rows() == 2);
                QVERIFY(parquet.rowGroups() ==  1);
                QVERIFY(parquet.columns() ==  11);
                QVERIFY(parquet.columnType(0) ==  parquet::Type::INT32);
                QVERIFY(parquet.columnType(1) ==  parquet::Type::BOOLEAN);
                QVERIFY(parquet.columnType(2) ==  parquet::Type::INT32);
                QVERIFY(parquet.columnType(3) ==  parquet::Type::INT32);
                QVERIFY(parquet.columnType(4) ==  parquet::Type::INT32);
                QVERIFY(parquet.columnType(5) ==  parquet::Type::INT64);
                QVERIFY(parquet.columnType(6) ==  parquet::Type::FLOAT);
                QVERIFY(parquet.columnType(7) ==  parquet::Type::DOUBLE);
                QVERIFY(parquet.columnType(8) ==  parquet::Type::BYTE_ARRAY);
                QVERIFY(parquet.columnType(9) ==  parquet::Type::BYTE_ARRAY);
                QVERIFY(parquet.columnType(10) ==  parquet::Type::INT96);

                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //2.验证打印信息
                //打印schema信息
                std::ostringstream printString;
                parquet.printSchema(printString,  std::list<int>(),true);
                qDebug()<<printString.str().data();
                QVERIFY(printString.str().size() != 0);


                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //3.查询值

                Parquet::ColumnVector<int> colIntVecor1(2);
                Parquet::ColumnVector<bool> colBoolVecor(2);
                Parquet::ColumnVector<int> colIntVecor2(2);
                Parquet::ColumnVector<int> colIntVecor3(2);
                Parquet::ColumnVector<int> colIntVecor4(2);
                Parquet::ColumnVector<int64_t> colInt64Vecor(2);
                Parquet::ColumnVector<float> colFloatVecor(2);
                Parquet::ColumnVector<double> colDoubleVecor(2);
                Parquet::ColumnVector<parquet::ByteArray> colByteArrayVecor1(2);
                Parquet::ColumnVector<parquet::ByteArray> colByteArrayVecor2(2);
                Parquet::ColumnVector<parquet::Int96> colInt96Vecor(2);
                 parquet.readAllColumns(
                             colIntVecor1,
                             colBoolVecor,
                             colIntVecor2,
                             colIntVecor3,
                             colIntVecor4,
                             colInt64Vecor,
                             colFloatVecor,
                             colDoubleVecor,
                             colByteArrayVecor1,
                             colByteArrayVecor2,
                             colInt96Vecor);

                 //读取验证
                 QVERIFY(colIntVecor1.values()[0] == 6);
                 QVERIFY(colIntVecor1.values()[1] == 7);

                 QVERIFY(colBoolVecor.values()[0] == true);
                 QVERIFY(colBoolVecor.values()[1] == false);

                 QVERIFY(colInt64Vecor.values()[0] == 0);
                 QVERIFY(colInt64Vecor.values()[1] == 10);
                 QVERIFY(fabs(colFloatVecor.values()[0] - 0) < 0.0000001);
                 QVERIFY(fabs(colFloatVecor.values()[1] - 1.100000) <0000001);
                 QVERIFY(fabs(colDoubleVecor.values()[0] - 0) < 0.000000000000001);
                 QVERIFY(fabs(colDoubleVecor.values()[1] -  10.100000)<0.000000000000001);


                 std::string str1((char*)colByteArrayVecor1.values()[0].ptr,colByteArrayVecor1.values()[0].len);
                 QVERIFY(str1 == std::string("04/01/09"));
                 std::string str2((char*)colByteArrayVecor1.values()[1].ptr, colByteArrayVecor1.values()[1].len);
                 QVERIFY(str2 == std::string("04/01/09"));

                 //如果时ByteArray时,需要手动释放
                 colByteArrayVecor1.dispose();
                 colByteArrayVecor2.dispose();

                 QVERIFY(colInt96Vecor.values()[0].value[0]== 0);
                 QVERIFY(colInt96Vecor.values()[0].value[1]== 0);
                 QVERIFY(colInt96Vecor.values()[0] .value[2]== 2454923);
                 QVERIFY(colInt96Vecor.values()[1] .value[0]== 4165425152);
                 QVERIFY(colInt96Vecor.values()[1].value[1] == 13);
                 QVERIFY(colInt96Vecor.values()[1].value[2]== 2454923);
            }     

            /**
             * @brief testWriteSimpleDataPerformancePrimitively
             *              测试写的效率,这里使用最基础的函数, 代码基于parquet的demo中, 没有经过任何封装, 所以代表了
             *        写效率的上限
             *
             *  测试函数:
             *          None
             *
             * 测试数据:
             *          创建的30W条记录, 20列, 为了简单起见 , 所有类型设置为double
             *          数据量: 8*8*300000*20/1024/1024 = 36M
             *
             * 测试结果:
             * rime PC i7  16G  1070 ubuntu
             *              Debug:2.41 s
             *              Release:2.30 s
             */
            void testWriteSimpleDataPerformancePrimitively()
            {
                string filePath  =  (m_parquetDataPath+"test_primitively.parquet").toStdString();

                //按照写入记录的行数创建rowGroup
                int rowCnt =1; /*300000;*///平时, 为了方便测试, 这里的数据量改为1
                int rowGroupCnt = rowCnt/ Parquet::rowsPerRowGroup()+1;//rowGroup的数量
                int colCnt = 20;//20列数据

                QBENCHMARK
                {
                    std::shared_ptr<::arrow::io::FileOutputStream> outFile;
                    FileOutputStream::Open(filePath,&outFile);//确认这行代码是否必要

                    //开始按照rowGroup写parquet文件
                    parquet::schema::NodeVector fields;
                    setupSimplySchema(fields);

                    std::shared_ptr<parquet::ParquetFileWriter> fileWriter = parquet::ParquetFileWriter::Open(
                                outFile,
                                std::static_pointer_cast<GroupNode>( GroupNode::Make("schema", Repetition::REQUIRED, fields)));

                    //除去最后一个Group, 其它Group都存了固定的行数
                    for( int groupIndex = 0; groupIndex < rowGroupCnt - 1; ++groupIndex)
                    {
                        parquet::RowGroupWriter* rowGroupWriter =
                                fileWriter->AppendRowGroup(Parquet::rowsPerRowGroup());

                        //开始遍历列
                        for(int colIndex = 0 ; colIndex<colCnt;++colIndex)
                        {
                            parquet::DoubleWriter* doubleWriter =
                                    static_cast<parquet::DoubleWriter*>(rowGroupWriter->NextColumn());
                            std::vector<double> value( Parquet::rowsPerRowGroup(),-1);

                            doubleWriter->WriteBatch( Parquet::rowsPerRowGroup(), nullptr, nullptr, value.data());
                        }
                    }

                    int remainRowCnt = rowCnt% Parquet::rowsPerRowGroup();
                    parquet::RowGroupWriter* rowGroupWriter1 =
                            fileWriter->AppendRowGroup(remainRowCnt);
                    //开始遍历列
                    for(int colIndex = 0 ; colIndex<colCnt;++colIndex)
                    {
                        parquet::DoubleWriter* doubleWriter1 =
                                static_cast<parquet::DoubleWriter*>(rowGroupWriter1->NextColumn());
                        std::vector<double> value(remainRowCnt,-1);

                        doubleWriter1->WriteBatch( remainRowCnt, nullptr, nullptr, value.data());
                    }

                    fileWriter->Close();
                    outFile->Close();
                }

                Parquet parquet(filePath);
                QVERIFY(parquet.rows() == rowCnt);
                QVERIFY(parquet.columns() == colCnt);
            }

            /**
             * @brief testWrite
             *         测试Parquet的写入效率, 测试在相同情况下经过Parquet.cpp封装过一道的write函数相比与不封装情况下
             * 的效率对比.
             *
             * 测试函数:
             *              writeToFilePath
             *
             * 测试数据:
             *              和testWriteSimpleDataPerformancePrimitively一样的数据
             *
             * 测试结果
             * rime PC i7  16G  1070 ubuntu
             *              Debug: 2.36 s    (效率和不封装的效率基本一样, 说明了使用Parquet.cpp封装一道没有影响效率)
             *              Release:2.24 s
             *
             */
            void testWriteSimpleDataPerformance()
            {
                 string filePath  =  (this->m_parquetDataPath +"testSimple.parquet").toStdString();

                //按照写入记录的行数创建rowGroup
               int rowCnt =1; /*300000;*///平时, 为了方便测试, 这里的数据量改为1

                QBENCHMARK
                {
                    //>>>-------------------------------------------------------------------------------------------------------------------------------------
                    //1.不带压缩, 基础类型(全部为double)
                    Parquet::ColumnVector<double> datas(rowCnt);

                    Parquet parquet;
                    parquet::schema::NodeVector fields;
                    setupSimplySchema(fields);

                    parquet.setupSchema(fields);
                    parquet.writeToFilePath(
                                filePath,
                                parquet::Compression::type::UNCOMPRESSED,
                                rowCnt,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas,
                                datas
                                );
                }
            }

            /**
             * @brief testWriteComplexDataPerformance
             *              测试复杂数据结构的写入效率
             *
             * 测试数据:
             *             通过setupComplexSchema定义的数据结构, 定义和Sqlite中的测试数据相同
             *
             * 测试函数
             *              writeToFilePath
             *
             * 测试结果
             *
             * rime PC i7  16G  1070 ubuntu
             *              Debug: 3.12 s
             *              Release: 2.96 s
             *              存储大小:48.4M
             *
             */
            void testWriteComplexDataPerformance()
            {
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //1. 创建需要写入的数据

                string filePath   = m_parquetDataPath.toStdString()+string("testComplex.parquet");
                FileInfo fileInfo(filePath);
                if(fileInfo.exists(filePath))
                {
                    fileInfo.remove();
                }

               //按照写入记录的行数创建rowGroup
              int rowCnt =1; /*300000;*///平时, 为了方便测试, 这里的数据量改为1
               int colCnt = 20;//20列数据

               Parquet::ColumnVector<int> idDatasIn;
               Parquet::ColumnVector<int> kPIIDDatasIn;
               Parquet::ColumnVector<int> codeDatasIn;
               Parquet::ColumnVector<int> v1DatasIn;
               Parquet::ColumnVector<int> v2DatasIn;
               Parquet::ColumnVector<double> v3DatasIn;
               Parquet::ColumnVector<parquet::ByteArray> v4DatasIn;
               Parquet::ColumnVector<double> v5DatasIn;
               Parquet::ColumnVector<double> v6DatasIn;
               Parquet::ColumnVector<double> v7DatasIn;
               Parquet::ColumnVector<double> v8DatasIn;
               Parquet::ColumnVector<double> v9DatasIn;
               Parquet::ColumnVector<double> v10DatasIn;
               Parquet::ColumnVector<double> v11DatasIn;
               Parquet::ColumnVector<double> v12DatasIn;
               Parquet::ColumnVector<double> v13DatasIn;
               Parquet::ColumnVector<double> v14DatasIn;
               Parquet::ColumnVector<double> v15DatasIn;
               Parquet::ColumnVector<double> v16DatasIn;
               Parquet::ColumnVector<double> v17DatasIn;

               //>>>-------------------------------------------------------------------------------------------------------------------------------------
               //2. 写入测试

               Parquet parquet;
               QBENCHMARK
               {
                   idDatasIn.init(rowCnt);
                   kPIIDDatasIn.init(rowCnt);
                   codeDatasIn.init(rowCnt);
                   v1DatasIn.init(rowCnt);
                   v2DatasIn.init(rowCnt);
                   v3DatasIn.init(rowCnt);
                   v4DatasIn.init(rowCnt);
                   v5DatasIn.init(rowCnt);
                   v6DatasIn.init(rowCnt);
                   v7DatasIn.init(rowCnt);
                   v8DatasIn.init(rowCnt);
                   v9DatasIn.init(rowCnt);
                   v10DatasIn.init(rowCnt);
                   v11DatasIn.init(rowCnt);
                   v12DatasIn.init(rowCnt);
                   v13DatasIn.init(rowCnt);
                   v14DatasIn.init(rowCnt);
                   v15DatasIn.init(rowCnt);
                   v16DatasIn.init(rowCnt);
                   v17DatasIn.init(rowCnt);

                   for(int i = 0; i<rowCnt;++i)
                   {
                       idDatasIn.values()[i] = i;
                       kPIIDDatasIn.values()[i] = i + 1;
                       codeDatasIn.values()[i] = i+2;
                       v1DatasIn.values()[i] = i + 3;
                       v2DatasIn.values()[i] = i + 4;
                       v3DatasIn.values()[i] = i * 3.14159;

                       std::string str("It's a test");
                       v4DatasIn.values()[i] = parquet::ByteArray(str.size(), (const uint8_t*)str.data());
                       v5DatasIn.values()[i] = i * 1.1;
                       v6DatasIn.values()[i] = i * 1.11;
                       v7DatasIn.values()[i] = i * 1.12;
                       v8DatasIn.values()[i] = i * 1.13;
                       v9DatasIn.values()[i] = i * 1.14;
                       v10DatasIn.values()[i] = i * 1.15;
                       v11DatasIn.values()[i] = i * 1.16;
                       v12DatasIn.values()[i] = i * 1.17;
                       v13DatasIn.values()[i] = i * 1.18;
                       v14DatasIn.values()[i] = i * 1.19;
                       v15DatasIn.values()[i] = i * 1.20;
                       v16DatasIn.values()[i] = i * 1.21;
                       v17DatasIn.values()[i] = i * 1.22;
                   }


                   parquet::schema::NodeVector fields;
                   setupComplexSchema(fields);

                   parquet.setupSchema(fields);
                   parquet.writeToFilePath(
                               filePath,
                               parquet::Compression::type::UNCOMPRESSED,
                               rowCnt,
                               idDatasIn,
                               kPIIDDatasIn,
                               codeDatasIn,
                               v1DatasIn,
                               v2DatasIn,
                               v3DatasIn,
                               v4DatasIn,
                               v5DatasIn,
                               v6DatasIn,
                               v7DatasIn,
                               v8DatasIn,
                               v9DatasIn,
                               v10DatasIn,
                               v11DatasIn,
                               v12DatasIn,
                               v13DatasIn,
                               v14DatasIn,
                               v15DatasIn,
                               v16DatasIn,
                               v17DatasIn
                               );
               }

               //>>>-------------------------------------------------------------------------------------------------------------------------------------
               //3.读取写入的Parquet文件

               Parquet::ColumnVector<int> idDatasOut(rowCnt);
               Parquet::ColumnVector<int> kPIIDDatasOut(rowCnt);
               Parquet::ColumnVector<int> codeDatasOut(rowCnt);
               Parquet::ColumnVector<int> v1DatasOut(rowCnt);
               Parquet::ColumnVector<int> v2DatasOut(rowCnt);
               Parquet::ColumnVector<double> v3DatasOut(rowCnt);
               Parquet::ColumnVector<parquet::ByteArray> v4DatasOut(rowCnt);
               Parquet::ColumnVector<double> v5DatasOut(rowCnt);
               Parquet::ColumnVector<double> v6DatasOut(rowCnt);
               Parquet::ColumnVector<double> v7DatasOut(rowCnt);
               Parquet::ColumnVector<double> v8DatasOut(rowCnt);
               Parquet::ColumnVector<double> v9DatasOut(rowCnt);
               Parquet::ColumnVector<double> v10DatasOut(rowCnt);
               Parquet::ColumnVector<double> v11DatasOut(rowCnt);
               Parquet::ColumnVector<double> v12DatasOut(rowCnt);
               Parquet::ColumnVector<double> v13DatasOut(rowCnt);
               Parquet::ColumnVector<double> v14DatasOut(rowCnt);
               Parquet::ColumnVector<double> v15DatasOut(rowCnt);
               Parquet::ColumnVector<double> v16DatasOut(rowCnt);
               Parquet::ColumnVector<double> v17DatasOut(rowCnt);

               Parquet parquet1(filePath);
               parquet1.readAllColumns(
                           idDatasOut,
                           kPIIDDatasOut,
                           codeDatasOut,
                           v1DatasOut,
                           v2DatasOut,
                           v3DatasOut,
                           v4DatasOut,
                           v5DatasOut,
                           v6DatasOut,
                           v7DatasOut,
                           v8DatasOut,
                           v9DatasOut,
                           v10DatasOut,
                           v11DatasOut,
                           v12DatasOut,
                           v13DatasOut,
                           v14DatasOut,
                           v15DatasOut,
                           v16DatasOut,
                           v17DatasOut);

               //>>>-------------------------------------------------------------------------------------------------------------------------------------
               //3.验证测试

               //判断行数和列数
               QVERIFY(parquet1.rows() == rowCnt);
               QVERIFY(parquet1.columns() == colCnt);

               //判读具体的值
               for( int i = 0; i < rowCnt; ++i )
               {
                   QVERIFY(idDatasIn.values()[i] == idDatasOut.values()[i]);
                   QVERIFY(kPIIDDatasIn.values()[i] == kPIIDDatasOut.values()[i]);
                   QVERIFY(codeDatasIn.values()[i] == codeDatasOut.values()[i]);
                   QVERIFY(v1DatasIn.values()[i] == v1DatasOut.values()[i]);
                   QVERIFY(v2DatasIn.values()[i] == v2DatasOut.values()[i]);
                   QVERIFY( abs(v3DatasIn.values()[i] - v3DatasOut.values()[i]) < 0.00001);
                   std::string outStr((char*)v4DatasOut.values()[i].ptr, v4DatasOut.values()[i].len);
                   QVERIFY(std::string("It's a test") == outStr)  ;

                   QVERIFY(abs(v5DatasIn.values()[i] - v5DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v6DatasIn.values()[i] - v6DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v7DatasIn.values()[i] - v7DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v8DatasIn.values()[i] - v8DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v9DatasIn.values()[i] - v9DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v10DatasIn.values()[i] - v10DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v11DatasIn.values()[i] - v11DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v12DatasIn.values()[i] - v12DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v13DatasIn.values()[i] - v13DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v14DatasIn.values()[i] - v14DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v15DatasIn.values()[i] - v15DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v16DatasIn.values()[i] - v16DatasOut.values()[i])<0.001);
                   QVERIFY(abs(v17DatasIn.values()[i] - v17DatasOut.values()[i])<0.001);
               }

                v4DatasOut.dispose();
            }

            /**
             * @brief testReadComplexDataPerformance
             *             测试读的效率
             *
             * 测试函数
             *              readAllColumns
             *
             * 测试数据
             *              通过setupComplexSchema定义的数据结构, 定义和Sqlite中的测试数据相同
             *
             * 测试结果
             * rime PC i7  16G  1070 ubuntu
             *              Debug: 1.95 s
             *              Release:1.34 s
             *
             */
            void testReadComplexDataPerformance()
            {
                string filePath  =  (m_parquetDataPath+"testComplex.parquet").toStdString();


                QBENCHMARK
                {
                   int rowCnt =1; /*300000;*///平时, 为了方便测试, 这里的数据量改为1

                    Parquet::ColumnVector<int> idDatasOut(rowCnt);
                    Parquet::ColumnVector<int> kPIIDDatasOut(rowCnt);
                    Parquet::ColumnVector<int> codeDatasOut(rowCnt);
                    Parquet::ColumnVector<int> v1DatasOut(rowCnt);
                    Parquet::ColumnVector<int> v2DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v3DatasOut(rowCnt);
                    Parquet::ColumnVector<parquet::ByteArray> v4DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v5DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v6DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v7DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v8DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v9DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v10DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v11DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v12DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v13DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v14DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v15DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v16DatasOut(rowCnt);
                    Parquet::ColumnVector<double> v17DatasOut(rowCnt);

                    Parquet parquet(filePath);
                    parquet.readAllColumns(
                                idDatasOut,
                                kPIIDDatasOut,
                                codeDatasOut,
                                v1DatasOut,
                                v2DatasOut,
                                v3DatasOut,
                                v4DatasOut,
                                v5DatasOut,
                                v6DatasOut,
                                v7DatasOut,
                                v8DatasOut,
                                v9DatasOut,
                                v10DatasOut,
                                v11DatasOut,
                                v12DatasOut,
                                v13DatasOut,
                                v14DatasOut,
                                v15DatasOut,
                                v16DatasOut,
                                v17DatasOut);

                    v4DatasOut.dispose();
                }
            }

            /**
             * @brief testSnappyCompression
             *             写Parquet的时候, 测试不同的压缩算法对于存储容量大小和写效率的影响
             *
             * 测试数据
             *              通过setupComplexSchema定义的数据结构, 定义和Sqlite中的测试数据相同
             *
             * 测试函数
             *              writeToFilePath
             *
             * 测试结果
             * rime PC i7  16G  1070 ubuntu
             *              Debug:3.28 s
             *              Release: 3.14 s
             *              存储大小:36.6M
             */
            void testSnappyCompression()
            {
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //1. 创建需要写入的数据

                string filePath  =  (m_parquetDataPath+"testSnappyComplex.parquet").toStdString();

                writeComplexData(filePath,  parquet::Compression::type::SNAPPY);
            }

            /**
             * @brief testBrotliCompression
             *             写Parquet的时候, 测试不同的压缩算法对于存储容量大小和写效率的影响
             *
             *  测试数据
             *              通过setupComplexSchema定义的数据结构, 定义和Sqlite中的测试数据相同
             *
             * 测试函数
             *              writeToFilePath
             *
             * 测试结果
             * rime PC i7  16G  1070 ubuntu
             *              Debug: 12.03s
             *              Release: 11.88 s
             *              存储大小: 20.0M
             */
            void testBrotliCompression()
            {
                string filePath  =  (m_parquetDataPath+"testBrotliComplex.parquet").toStdString();
                writeComplexData(filePath, parquet::Compression::type::BROTLI );
            }

            /**
             * @brief testGZipCompression
             *             写Parquet的时候, 测试不同的压缩算法对于存储容量大小和写效率的影响
             *
             * 测试数据
             *              通过setupComplexSchema定义的数据结构, 定义和Sqlite中的测试数据相同
             *
             * 测试函数
             *              writeToFilePath
             *
             * 测试结果
             * rime PC i7  16G  1070 ubuntu
             *              Debug: 8.97s
             *              Release: 8.92 s
             *              存储大小: 24.8M
             */
            void testGZipCompression()
            {
                string filePath  =  (m_parquetDataPath+"testGZipComplex.parquet").toStdString();
               writeComplexData(filePath, parquet::Compression::type::GZIP );
            }

            void cleanupTestCase()
            {

            }

        private:
                  //测试数据路径
                  QString m_parquetDataPath{dataPath+"Parquet/"};

                  //创建需要导出的简单的schema结构,  全部为double, 主要用于验证封装过的parquet和为封装过的写效率的区别
                  void setupSimplySchema( parquet::schema::NodeVector& fields );
                  //创建复杂的schema结构, 参照sqlite测试数据的结构, 主要用于类型验证以及和sqlite的效率比对
                  void setupComplexSchema( parquet::schema::NodeVector& fields);

                  //写一个复杂类型的Parquet文件, 数据结构由setupComplexSchema定义, 该函数主要用于压缩测试
                  void writeComplexData(std::string& filePath, parquet::Compression::type codec);
        };//End of TestParquet

        DECLARE_TEST(TestParquet)

        void TestParquet::setupSimplySchema(parquet::schema::NodeVector& fields )
        {
            //这个函数主要用于性能测试的, 为了测试方便, Repetition全部使用REQUIRED,  这样就可以不设置ref_level和def_level了

            fields.push_back(PrimitiveNode::Make(
                                 "id", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "KPIID", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "CODE", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V1", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V2", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V3", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V4", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V5", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V6", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V7", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V8", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V9", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V10", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V11", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V12", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V13", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V14", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V15", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V16", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V17", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
        }
        void TestParquet::setupComplexSchema( parquet::schema::NodeVector& fields)
        {
            fields.push_back(PrimitiveNode::Make(
                                 "id", Repetition::REQUIRED, Type::INT32, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "KPIID", Repetition::REQUIRED, Type::INT32, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "CODE", Repetition::REQUIRED, Type::INT32, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V1", Repetition::REQUIRED, Type::INT32, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V2", Repetition::REQUIRED, Type::INT32, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V3", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V4", Repetition::REQUIRED, Type::BYTE_ARRAY, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V5", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V6", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V7", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V8", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V9", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V10", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V11", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V12", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V13", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V14", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V15", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V16", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
            fields.push_back(PrimitiveNode::Make(
                                 "V17", Repetition::REQUIRED, Type::DOUBLE, LogicalType::NONE));
        }
        void TestParquet::writeComplexData(std::string& filePath, parquet::Compression::type codec)
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1. 创建需要写入的数据

           //按照写入记录的行数创建rowGroup
          int rowCnt =1; /*300000;*///平时, 为了方便测试, 这里的数据量改为1

           Parquet::ColumnVector<int> idDatasIn(rowCnt);
           Parquet::ColumnVector<int> kPIIDDatasIn(rowCnt);
           Parquet::ColumnVector<int> codeDatasIn(rowCnt);
           Parquet::ColumnVector<int> v1DatasIn(rowCnt);
           Parquet::ColumnVector<int> v2DatasIn(rowCnt);
           Parquet::ColumnVector<double> v3DatasIn(rowCnt);
           Parquet::ColumnVector<parquet::ByteArray> v4DatasIn(rowCnt);
           Parquet::ColumnVector<double> v5DatasIn(rowCnt);
           Parquet::ColumnVector<double> v6DatasIn(rowCnt);
           Parquet::ColumnVector<double> v7DatasIn(rowCnt);
           Parquet::ColumnVector<double> v8DatasIn(rowCnt);
           Parquet::ColumnVector<double> v9DatasIn(rowCnt);
           Parquet::ColumnVector<double> v10DatasIn(rowCnt);
           Parquet::ColumnVector<double> v11DatasIn(rowCnt);
           Parquet::ColumnVector<double> v12DatasIn(rowCnt);
           Parquet::ColumnVector<double> v13DatasIn(rowCnt);
           Parquet::ColumnVector<double> v14DatasIn(rowCnt);
           Parquet::ColumnVector<double> v15DatasIn(rowCnt);
           Parquet::ColumnVector<double> v16DatasIn(rowCnt);
           Parquet::ColumnVector<double> v17DatasIn(rowCnt);

           for(int i = 0; i<rowCnt;++i)
           {
               idDatasIn.values()[i] = i;
               kPIIDDatasIn.values()[i] = i + 1;
               codeDatasIn.values()[i] = i+2;
               v1DatasIn.values()[i] = i + 3;
               v2DatasIn.values()[i] = i + 4;
               v3DatasIn.values()[i] = i * 3.14159;

               std::string str("It's a test");
               v4DatasIn.values()[i] = parquet::ByteArray(str.size(), (const uint8_t*)str.data());
               v5DatasIn.values()[i] = i * 1.1;
               v6DatasIn.values()[i] = i * 1.11;
               v7DatasIn.values()[i] = i * 1.12;
               v8DatasIn.values()[i] = i * 1.13;
               v9DatasIn.values()[i] = i * 1.14;
               v10DatasIn.values()[i] = i * 1.15;
               v11DatasIn.values()[i] = i * 1.16;
               v12DatasIn.values()[i] = i * 1.17;
               v13DatasIn.values()[i] = i * 1.18;
               v14DatasIn.values()[i] = i * 1.19;
               v15DatasIn.values()[i] = i * 1.20;
               v16DatasIn.values()[i] = i * 1.21;
               v17DatasIn.values()[i] = i * 1.22;
           }

           //>>>-------------------------------------------------------------------------------------------------------------------------------------
           //2. 写入测试

           Parquet parquet;
           QBENCHMARK
           {
               parquet::schema::NodeVector fields;
               setupComplexSchema(fields);

               parquet.setupSchema(fields);
               parquet.writeToFilePath(
                           filePath,
                           codec,
                           rowCnt,
                           idDatasIn,
                           kPIIDDatasIn,
                           codeDatasIn,
                           v1DatasIn,
                           v2DatasIn,
                           v3DatasIn,
                           v4DatasIn,
                           v5DatasIn,
                           v6DatasIn,
                           v7DatasIn,
                           v8DatasIn,
                           v9DatasIn,
                           v10DatasIn,
                           v11DatasIn,
                           v12DatasIn,
                           v13DatasIn,
                           v14DatasIn,
                           v15DatasIn,
                           v16DatasIn,
                           v17DatasIn
                           );
           }
        }

    }//End of namespace SSDK
}//End of namespace TestParquet


#endif // TESTPARQUET_HPP
