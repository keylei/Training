//#include "sqlitedbtest.hpp"

//using namespace rapidjson;
//using namespace SSDK::DB;
//using namespace SSDK::Archive;
//using namespace std;

//SqliteDBTest::SqliteDBTest()
//{

//}

//void SqliteDBTest::testCreateTable()
//{
////    SqliteDB db;
////    db.open("test.db");

////    const string sqlcreate = "CREATE TABLE if not exists PersonTable(ID INTEGER NOT NULL, Name Text, Address BLOB);";
////    if (!db.execute(sqlcreate))
////        return;

////    const string sqlInsert = "INSERT INTO PERSONTABLE(ID,NAME,Address) VALUES(?,?,?);";
////    int id = 2;
////    string name = "Rime";
////    string city = "Jiangshu";
////    SqliteDB::Blob blob{city.data(),city.size()};
////    if(!db.execute(sqlInsert,id,name,blob))
////        return;

////    //    testJsonToSqlite(db,sqlInsert);

////    db.excecuteTuple(sqlInsert, std::forward_as_tuple(3, string("Tuple"), blob));
////    char* json;
////    string strQery = "select * from PersonTable";
////    std::shared_ptr<rapidjson::Document> doc;
////    for(int i = 0;i<10000;i++)
////    {
////        doc =  db.query(strQery);
////    }

////    const string str = "select Address from PersonTable where ID=2";
////    auto pname = db.executeScalar<string>(str);
////    cout << pname << endl;
//}

//void SqliteDBTest::testJsonHelper()
//{
//    SqliteDB db;
//    db.open("test.db");
//    const string sqlcreat = "CREATE TABLE if not exists TestInfoTable(ID INTEGER NOT NULL, KPIID INTEGER, CODE INTEGER, V1 INTEGER, V2 INTEGER, V3 REAL, V4 TEXT);";
//    if (!db.execute(sqlcreat))
//        return;

//    //>>>--------------------------------------------------------------------------------
//    //插入效率: 在release环境下，从创建7列数据到Json，json再插入到sqlite，100W时间为2s

//    boost::timer t;
////    Json jcp;

////    jcp.startArray();
////    int count = 1000000;
////    for (size_t i = 0; i < count; i++)
////    {
////        jcp.startObject();
////        jcp.write("ID", i);
////        jcp.write("KPIID", i);
////        jcp.write("CODE", i);
////        jcp.write("V1", i);
////        jcp.write("V2", i);
////        jcp.write("V3", i + 1.25);
////        jcp.write("V4", "it is a test");

////        jcp.endObject();
////    }
////    jcp.endArray();

////    const string sqlinsert = "INSERT INTO TestInfoTable(ID, KPIID, CODE, V1, V2, V3, V4) VALUES(?, ?, ?, ?, ?, ?, ?);";
////    bool r = db.excecuteJson(sqlinsert, jcp.getString());

////    cout << t.elapsed() << endl;
////    t.restart();

////    //<<<--------------------------------------------------------------------------------

////    //>>>--------------------------------------------------------------------------------
////    //读取效率,在release环境下，100W 每行7列的查询时间为1.7s

////    auto p = db.query("select * from TestInfoTable");
////    cout << "查询时间:"<<t.elapsed() << endl;
////    t.restart();

////    rapidjson::Document& doc = *p;

////    for (size_t i = 0, len = doc.Size(); i < len; i++)
////    {
////        for (size_t i = 0, size = doc[i].GetSize(); i < size; ++i)
////        {
//////            auto a = doc[i]["ID"].GetInt();
//////            auto b = doc[i]["V3"].GetDouble();
//////            auto c = doc[i]["V4"].GetString();

//////            int d = 0;
////            //            auto &c = doc[i];
////        }
////    }
////    cout << "轮寻时间:"<<t.elapsed() << endl;
////    cout << "size: " << p->Size() << endl;

//    //<<<--------------------------------------------------------------------------------

//    //	t.restart();

//    //    boost::timer t;
//    //    JsonCpp jcp;
//    //    jcp.StartArray();
//    //    for (size_t i = 0; i < 1000000; i++)
//    //    {
//    //        jcp.StartObject();
//    //        jcp.WriteJson("ID", i);
//    //        jcp.WriteJson("KPIID", i);
//    //        jcp.WriteJson("CODE", i);
//    //        jcp.WriteJson("V1", i);
//    //        jcp.WriteJson("V2", i);
//    //        jcp.WriteJson("V3", i + 1.25);
//    //        jcp.WriteJson("V3", "it is a test");

//    //        jcp.EndObject();
//    //    }
//    //    jcp.EndArray();
//    //    const string sqlinsert = "INSERT INTO TestInfoTable(ID, KPIID, CODE, V1, V2, V3, V4) VALUES(?, ?, ?, ?, ?, ?, ?);";
//    //    bool r = db.ExcecuteJson(sqlinsert, jcp.GetString());
//    //    cout << t.elapsed() << endl;
//    //    t.restart();
//    //    //100w 3.5-4秒左右

//    //    auto p = db.Query("select * from TestInfoTable");
//    //    cout << t.elapsed() << endl;
//    //    t.restart();
//    //    rapidjson::Document& doc = *p;
//    //    for (size_t i = 0, len = doc.Size(); i < len; i++)
//    //    {
//    //        for (size_t i = 0, size = doc[i].GetSize(); i < size; ++i)
//    //        {

//    //        }
//    //    }
//    //    cout << t.elapsed() << endl;
//    //    cout << "size: " << p->Size() << endl;
//}

//void SqliteDBTest::testJsonToSqlite(SqliteDB& db,const string& sqlInsert)
//{
//    StringBuffer buf;
//    Writer<rapidjson::StringBuffer> writer(buf);
//    writer.StartArray();
//    for (size_t i = 0; i < 10; i++)
//    {
//        writer.StartObject();
//        writer.String("ID");
//        writer.Int(i + 1);

//        writer.String("Name");
//        writer.String("Peter");

//        writer.String("Address");
//        writer.String("Zhuhai");
//        writer.EndObject();
//    }
//    writer.EndArray();

//    db.excecuteJson(sqlInsert, buf.GetString());
//}

////100W 条记录直接使用executeArgs在release下需要0.868s
//void SqliteDBTest::testPerformance()
//{
////    SqliteDB db;
////    db.open("test.db");
////    const string sqlcreat = "CREATE TABLE if not exists TestInfoTable(ID INTEGER NOT NULL, KPIID INTEGER, CODE INTEGER, V1 INTEGER, V2 INTEGER, V3 REAL, V4 TEXT);";
////    if (!db.execute(sqlcreat))
////        return;

////    boost::timer t;
////    const string sqlinsert = "INSERT INTO TestInfoTable(ID, KPIID, CODE, V1, V2, V3, V4) VALUES(?, ?, ?, ?, ?, ?, ?);";
////    bool ret = db.prepare(sqlinsert);
////    db.begin();
////    for (size_t i = 0; i < 1000000; i++)
////    {
////        ret = db.executeArgs(i, i, i, i, i, i + 1.25, "Performance test");
////        if (!ret)
////            break;
////    }

////    if (ret)
////        db.commit(); //提交事务
////    else
////        db.rollBack(); //回滚

////    cout << t.elapsed() << endl;
////    t.restart();
////    //100w 3.5-4秒左右

////    auto p = db.query("select * from TestInfoTable");

////    cout << t.elapsed() << endl;
////    cout << "size: " << p->Size() << endl;
////    //100W 4秒左右
//}
