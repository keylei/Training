#ifndef TESTSQLITE_HPP
#define TESTSQLITE_HPP

#include "unittester.hpp"

#include "DB/sqlitedb.hpp"
#include "DB/blob.hpp"
#include "Archive/Json/json.hpp"
#include "Archive/fileinfo.hpp"

using namespace std;
using namespace SSDK::DB;
using namespace SSDK::Archive;

namespace UnitTester
{
namespace SSDK
{
class TestSqlite: public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {

    }

    /**
           * @brief testOpenAndClose
           *
           * 测试sqliteDB下面函数
           *    1.open
           *    2.close
           *
           * 测试数据
           *    student
           *
           * 测试逻辑: 打开sqlite文件,然后再关闭文件, 看是否成功
           */
    void testOpenAndClose()
    {
        //读取一个合法的路径
        auto path = m_sqliteDataPath.toStdString()+string("student");
        SqliteDB sqlite(path);
        auto isOpened = sqlite.isOpened();
        QVERIFY2(isOpened,"Open student failed!");

        auto isClosed = sqlite.close();
        QVERIFY2(isClosed,"Close student failed!");
    }

    /**
           * @brief testExecute
           *
           * 测试sqliteDB下面函数
           *     prepare
           *     execute
           *     executeArgs(execute内部调用了)
           *     executeScalar
           *
           * 测试逻辑
           *    1.新建一个表(execute)
           *            创建表涵盖所有的数据结构
           *    2.插入一行记录(executeArgs)
           *    3.查询指定数据是否正确(executeScalar)
           */
    void testExecute()
    {
        SqliteDB db;

        auto path = m_sqliteDataPath.toStdString()+string("student");
        bool isSuccessful = false;

        //打开数据库
        isSuccessful = db.open(path);
        QVERIFY2(isSuccessful,"open db error!");

        //删除表
        const string deleteSql = "DROP TABLE BasicInfo";
        db.execute(deleteSql);
        QVERIFY2(isSuccessful,"Delete table error!");

        //创建一个数据库
        const string sqlcreate = "CREATE TABLE if not exists BasicInfo(ID INTEGER NOT NULL, Name Text, Score REAL, Address BLOB);";
        QVERIFY2(db.isOpened() && db.execute(sqlcreate),"create table failed!");

        //插入一条记录
        const string sqlInsert = "INSERT INTO BasicInfo(ID,Name,Score,Address) VALUES(?,?,?,?);";
        int id = 1;
        string name = "rime";
        string city = "Jiangshu";
        double score = 9.9;
        Blob blob(city.data());
        QVERIFY2(db.execute(sqlInsert,id,name,score,blob),"insert a record failed!");

        //查询记录
        const string str = "select Score from BASICINFO where ID=1";
        auto dRes = db.executeScalar<double>(str);
        QVERIFY2(dRes ==9.9 ," query name failed !");

        const string str1 = "select Name from BASICINFO where ID=1";
        auto nRes = db.executeScalar<string>(str1);
        QVERIFY2(nRes ==name ," query name failed !");

        const string str2 = "select Address from BASICINFO where ID=1";
        auto cRes = db.executeScalar<Blob>(str2);
        QVERIFY2(cRes.toString() ==city ," query city failed !");

        db.close();
    }

    /**
           * @brief testExecuteInsertPerformance
           * 测试sqliteDB使用execute接口的插入效率
           *
           * 测试函数:
           *        prepare
           *        begin
           *        commit
           *        rollBack
           *        executeWithParms
           *
           * 测试逻辑
           *        在一个事务中插入30W条数据
           *
           * 测试环境
           *        1.rime 笔记本 ubuntu  i7 16G 1070
           *        2.30W记录  每条记录20列  没有二进制数据
           *
           * 测试结果
           *       插入
           *                Debug: 1.41s
           *                Release:1.16s
           *                50.7M
           */
    void testExecuteInsertPerformance()
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1. 创建数据库

        auto path = m_sqliteDataPath.toStdString()+string("student");
        FileInfo fileInfo(path);
        if(fileInfo.exists(path))
        {
            fileInfo.remove();
        }

        SqliteDB db;
        db.open(path);

        //创建一个数据库
        const string sqlcreate = "CREATE TABLE if not exists TestInfoTable"
                                 "(ID INTEGER NOT NULL, "
                                 "KPIID INTEGER, "
                                 "CODE INTEGER, "
                                 "V1 INTEGER, "
                                 "V2 INTEGER, "
                                 "V3 REAL, "
                                 "V4 TEXT, "
                                 "V5 REAL,"
                                 "V6 REAL,"
                                 "V7 REAL,"
                                 "V8 REAL,"
                                 "V9 REAL,"
                                 "V10 REAL,"
                                 "V11 REAL,"
                                 "V12 REAL,"
                                 "V13 REAL,"
                                 "V14 REAL,"
                                 "V15 REAL,"
                                 "V16 REAL,"
                                 "V17 REAL"
                                 ");";
        QVERIFY2(db.isOpened() && db.execute(sqlcreate),"create table failed!");


        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.插入效率测试

        //这里是利用普通接口的插入数据, 用了极少的封装,代表了sqlite插入数据的效率的上限

        //插入30W条数据
        const string sqlinsert = "INSERT INTO TestInfoTable("
                                 "ID, KPIID,CODE,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13,V14,V15,V16,V17)"
                                 "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

        //插入效率
        int rowCnt =200; /*300000;*///平时, 为了方便测试, 这里的数据量改为200
        QBENCHMARK
        {
            bool ret = db.prepare(sqlinsert);
            QVERIFY2(ret ,"prepare failed!");

            ret = db.begin();
            QVERIFY2(ret ,"begin failed!");

            for (int i = 0; i < rowCnt; i++)
            {
                ret = db.executeWithParms(
                            i,
                            i + 1,
                            i + 2,
                            i + 3,
                            i + 4,
                            i * 3.14159 ,
                            "it is test",
                            i * 1.1,
                            i * 1.11,
                            i * 1.12,
                            i * 1.13,
                            i * 1.14,
                            i * 1.15,
                            i * 1.16,
                            i * 1.17,
                            i * 1.18,
                            i * 1.19,
                            i * 1.20,
                            i * 1.21,
                            i * 1.22
                            );
                if (!ret)
                    QVERIFY2(ret ,"insert failed!");
            }

            if (ret)
            {
                ret =  db.commit(); //提交事务
                if (!ret)
                    QVERIFY2(ret ,"commit failed!");
            }
            else
            {
                ret =   db.rollBack(); //回滚
                QVERIFY2(ret ,"rollback failed!");
            }
        }

        db.close();
    }

    /**
     * @brief testExecuteQueryPerformance
     * 测试sqliteDB使用execute接口的查询效率
     *
     * 测试逻辑
     *        在一个事务中插入30W条数据
     *
     * 测试环境
     *        1.rime 笔记本 ubuntu  i7 16G 1070
     *        2.30W记录  每条记录20列  没有二进制数据
     *
     * 测试结果
     *       查询:
     *                Debug:4.57s
     *                Release:0.79s
     */
    void testExecuteQueryPerformance()
    {
        auto path = m_sqliteDataPath.toStdString()+string("student");
        SqliteDB db;
        db.open(path);


        //这里是利用普通接口的查询数据, 用了极少的封装,代表了sqlite查询效率的上限
        const string selectedString = "select * from TestInfoTable";
//        QBENCHMARK
        {
            bool ret = db.prepare(selectedString);
            QVERIFY2(ret ,"prepare failed!");

            ret = db.begin();
            QVERIFY2(ret ,"begin failed!");

            while(true)
            {
                auto colCnt = db.columnCnt();
                db.step();
                for(int i = 0;i<colCnt;++i)
                {
                    //获取数据
                    db.columnName(i);
                    db.columnValue(i);
                }

                if (db.latestErrorCode() == SQLITE_DONE)
                {
                    break;
                }
            }

            db.reset();
        }

        db.close();
    }

    /**
           * @brief testJsonExecute
           *            测试Sqlite的Json接口的插入和查询性能
           *
           * 测试函数:
           *            queryToJson
           *            insertJsonToSqlite
           *
           * 测试逻辑:
           *            1.使用json插入30W条数据
           *            2.使用json检索出30W条数据
           *
           * 测试环境
           *        1.rime 笔记本 ubuntu  i7 16G 1070 SSD512
           *        2.30W记录  每条记录20列  没有二进制数据
           *
           * 测试数据
           *        1.生成json的时间:
           *                    Debug:1.97s
           *                    Release:0.5s
           *        2.json插入的时间
           *                    Debug:4.9s
           *                    Release:4.1s
           *        3.json查询的时间
           *                    Debug:4.5s
           *                    Release:3.2s
           *
           */
    void testJsonPerformance()
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.创建数据库
        SqliteDB db;
        bool isSuccessful{false};
        db.open(m_sqliteDataPath.toStdString()+string("student"));

        //删除表
        const string deleteSql = "DROP TABLE TestInfoTable";
        isSuccessful = db.execute(deleteSql);
        QVERIFY2(isSuccessful,"Delete table error!");

        //创建一个数据库
        const string sqlcreate = "CREATE TABLE if not exists TestInfoTable"
                                 "(ID INTEGER NOT NULL, "
                                 "KPIID INTEGER, "
                                 "CODE INTEGER, "
                                 "V1 INTEGER, "
                                 "V2 INTEGER, "
                                 "V3 NUMERIC, "
                                 "V4 TEXT, "
                                 "V5 REAL,"
                                 "V6 REAL,"
                                 "V7 REAL,"
                                 "V8 REAL,"
                                 "V9 REAL,"
                                 "V10 REAL,"
                                 "V11 REAL,"
                                 "V12 REAL,"
                                 "V13 REAL,"
                                 "V14 REAL,"
                                 "V15 REAL,"
                                 "V16 REAL,"
                                 "V17 REAL"
                                 ");";

        QVERIFY2(db.isOpened() && db.execute(sqlcreate),"create table failed!");


        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2. json生成测试数据

        int rowCnt =300;//测试行数, 30W
        Json json;
        //              QBENCHMARK//测试数据表生成时间
        {
            json.startArray();
            for( int i = 0;i<rowCnt;++i )
            {
                json.startObject();
                json.writeValue("ID", i);
                json.writeValue("KPIID", i);
                json.writeValue("CODE", i);
                json.writeValue("V1", i);
                json.writeValue("V2", i);
                json.writeValue<double>("V3", i+1.25);
                json.writeValue("V4", "it is a test");
                json.writeValue<int>("V5", i);
                json.writeValue<int>("V6", i);
                json.writeValue<int>("V7", i);
                json.writeValue<int>("V8", i);
                json.writeValue<int>("V9", i);
                json.writeValue<int>("V10", i);
                json.writeValue<int>("V11", i);
                json.writeValue<int>("V12", i);
                json.writeValue<int>("V13", i);
                json.writeValue<int>("V14", i);
                json.writeValue<int>("V15", i);
                json.writeValue<int>("V16", i);
                json.writeValue<int>("V17", i);
                json.endObject();
            }
            json.endArray();
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.json插入效率测试

        const string sqlinsert = "INSERT INTO TestInfoTable("
                                 "ID, KPIID,CODE,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13,V14,V15,V16,V17)"
                                 "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
        QBENCHMARK
        {
            isSuccessful = db.insertJsonToSqlite(sqlinsert,json.toString());
            QVERIFY2(isSuccessful,"Json insert to sqlite failed!");
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //4.json查询效率测试

        string jsonStr;
//        QBENCHMARK//查询效率测试
        {
            jsonStr =  db.queryToJson("select * from TestInfoTable");
        }


        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //5.验证查询结果是否正确
        //验证查询结果
        Json json1;
        json1.parseFromString(jsonStr);
//        int cnt = json1.getArrayCount();
        for(int i = 0;i<rowCnt-1;++i)
        {
            QVERIFY2(json1.queryNumberOfDocArray<int>(i, "ID")== i,"ID is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<int>(i, "KPIID") == i,"KPIID is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<int>(i, "CODE") == i,"CODE is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<int>(i, "V1") == i,"V1 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<int>(i, "V2") == i,"V2 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V3") ==  i + 1.25,"V3 is incorrent");
            QVERIFY2(string(json1.queryStringOfDocArray(i, "V4"))== string("it is a test"),"V4 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V5") == i,"V5 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V6") == i,"V6 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V7") == i,"V7 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V8") == i,"V8 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V9") == i,"V9 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V10") == i,"V10 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V11") == i,"V11 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V12") == i,"V12 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V13") == i,"V13 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V14") == i,"V14 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V15") == i,"V15 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V16") == i,"V16 is incorrent");
            QVERIFY2(json1.queryNumberOfDocArray<double>(i, "V17") == i,"V17 is incorrent");
        }
    }

    /**
     * @brief testTuplePerformance
     *          测试Sqlite的Tuple接口的插入和查询性能
     *
     * 测试结果:
     *          Tuple性能太差, 一次插入就需要60ms, 那么插入30W条就需要5小时
     */
    void testTuplePerformance()
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.创建数据库
        SqliteDB db;
        bool isSuccessful{false};
        db.open(m_sqliteDataPath.toStdString()+string("student"));

        //删除表
        const string deleteSql = "DROP TABLE TestInfoTable";
        isSuccessful = db.execute(deleteSql);
        QVERIFY2(isSuccessful,"Delete table error!");

        //创建一个数据库
        const string sqlcreate = "CREATE TABLE if not exists TestInfoTable"
                                 "(ID INTEGER NOT NULL, "
                                 "KPIID INTEGER, "
                                 "CODE INTEGER, "
                                 "V1 INTEGER, "
                                 "V2 INTEGER, "
                                 "V3 NUMERIC, "
                                 "V4 TEXT, "
                                 "V5 REAL,"
                                 "V6 REAL,"
                                 "V7 REAL,"
                                 "V8 REAL,"
                                 "V9 REAL,"
                                 "V10 REAL,"
                                 "V11 REAL,"
                                 "V12 REAL,"
                                 "V13 REAL,"
                                 "V14 REAL,"
                                 "V15 REAL,"
                                 "V16 REAL,"
                                 "V17 REAL"
                                 ");";

        QVERIFY2(db.isOpened() && db.execute(sqlcreate),"create table failed!");


        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.tuple插入
        int rowCnt = 2;//测试行数, 30W
        const string sqlinsert = "INSERT INTO TestInfoTable("
                                 "ID, KPIID,CODE,V1,V2,V3,V4,V5,V6,V7,V8,V9,V10,V11,V12,V13,V14,V15,V16,V17)"
                                 "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

        QBENCHMARK
        {
            for(int i = 0;i < rowCnt; ++i)
            {
                db.insertTupleToSqlite(sqlinsert, std::forward_as_tuple(i, i,i,i,i,i+1.25,string("it is a test"), i,i,i,i,i,i,i,i,i,i,i,i,i));
            }
        }
    }

    void cleanupTestCase()
    {

    }

private:
    //测试数据路径
    QString m_sqliteDataPath{dataPath+"Sqlite/"};
};//End of TestSqlite

DECLARE_TEST(TestSqlite)
}//End of namespace SSDK
}//End of namespace UnitTester

#endif // TESTSQLITE_HPP
