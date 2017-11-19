#include <string>
#include <iostream>

#include <vector>

#include "DB/sqlitedb.hpp"

std::string sqliteDataPath = "../../../data/";

using namespace  std;
using namespace SSDK::DB;

class JOB1
{
public:
    class Pad
     {
           public:
                int X;
                int Y;
     };

      std::string Version{"V1"};
      vector<Pad> PadVec;

      void readFromDB(string path)
      {
          SqliteDB sqlite(path);
          try
          {
              auto isOpened = sqlite.isOpened();
              if(isOpened)
              {
                  //>>>----------------------------------------------------------------------------------------------------------
                  //1.读取版本号
                  string selectedString = "select Version from Job";
                  sqlite.prepare(selectedString);
                  Version = sqlite.executeScalar<string>(selectedString);

                  if(Version!="V1")
                  {
                      throw string("读取程序的版本不对，读取中止");
                  }

                  //>>>----------------------------------------------------------------------------------------------------------
                  //2.读取Target表
                  selectedString = "select * from Pad";
                  bool ret = sqlite.prepare(selectedString);
                  ret = sqlite.begin();

                  while(true)
                  {
                      sqlite.step();
                      if (sqlite.latestErrorCode() == SQLITE_DONE)
                      {
                          break;
                      }

                      //创建具体的对象
                      Pad target;
                      auto x = sqlite.columnValue(0);
                      auto y = sqlite.columnValue(1);
                      target.X =  boost::get<int>(x);
                      target.Y =  boost::get<int>(y);
                      PadVec.push_back(target);
                  }

                  sqlite.reset();
                  sqlite.close();
              }
          }
          catch(string& ex)
          {
              cout<<ex.data()<<endl;
              if(sqlite.isOpened())
              {
                  sqlite.reset();
                  sqlite.close(); //发生异常了需要特别注意需要关闭数据库
              }
          }
      }
};

class JOB2
{
public:
     std::string Version{"V2"};

     class Pad
     {
           public:
                double CenterY; //比版本1发生了重命名
                double CenterX;//比版本2发生了重命名
                double Angle;//比版本1增加了这个字段
     };

     class Library//比版本1多个一个表
     {
        public:
         double Width;
         double Height;
     };

     vector<Pad> PadVec;
     vector<Library> LibraryVec;

     void convertFromV1( SqliteDB& sqlite )
     {
         //>>>----------------------------------------------------------------------------------------------------------
         //1. 读取Pad
         auto selectedString = "select * from Pad";
         bool ret = sqlite.prepare(selectedString);
         ret = sqlite.begin();
         while(true)
         {
             sqlite.step();
             if (sqlite.latestErrorCode() == SQLITE_DONE)
             {
                 break;
             }

             //创建具体的对象
             Pad pad;
             auto x = sqlite.columnValue(0);
             auto y = sqlite.columnValue(1);
             pad.CenterX =  (double)boost::get<int>(x);//这里原来的数据类型是int的，新改了之后是double的，需要转换下
             pad.CenterY =  (double)boost::get<int>(y);
             pad.Angle = 0; // 默认的角度是0度
             PadVec.push_back(pad);
         }

         //>>>----------------------------------------------------------------------------------------------------------
         //2. 读取Library
         //V1是没有Library数据结构的， 所以默认创建2个
         int padCnt = PadVec.size();
         for (int i = 0; i < padCnt; ++i)
         {
                Library lib{0,0};
                LibraryVec.push_back(lib);
         }

         sqlite.reset();
         sqlite.close();

         //>>>----------------------------------------------------------------------------------------------------------
         //3.重新写Job表
         auto v2Path = sqliteDataPath+"v2";
         SqliteDB v2Sqlite;
         v2Sqlite.open(v2Path);
         string sqlcreate = "CREATE TABLE if not exists Job( Version TEXT );";
         v2Sqlite.execute(sqlcreate);

         string sqlInsert = "INSERT INTO Job(Version) VALUES('V2');";
         v2Sqlite.execute(sqlInsert);

         //>>>----------------------------------------------------------------------------------------------------------
         //4.重新写数据库(Pad表)

        //删除原来的Pad表
        string deleteSql = "DROP TABLE Pad";
        v2Sqlite.execute(deleteSql);

         //创建新的Pad表
        sqlcreate = "CREATE TABLE if not exists Pad(CenterX REAL, CenterY REAL, Angle REAL);";
        v2Sqlite.execute(sqlcreate);

        //插入现有的记录
         sqlInsert = "INSERT INTO Pad(CenterX,CenterY,Angle) VALUES(?,?,?);";
        for (int i = 0; i < padCnt; ++i)
        {
            v2Sqlite.execute(sqlInsert, PadVec[i].CenterX, PadVec[i].CenterY, PadVec[i].Angle);
        }

        //>>>----------------------------------------------------------------------------------------------------------
        //5.重新写数据库(Library表)
         //创建新的Pad表
        sqlcreate = "CREATE TABLE if not exists Library(Width REAL, Height REAL);";
        v2Sqlite.execute(sqlcreate);

        //插入现有的记录
        sqlInsert = "INSERT INTO Library(Width,Height) VALUES(?,?);";
        for (int i = 0; i < padCnt; ++i)
        {
            v2Sqlite.execute(sqlInsert, LibraryVec[i].Width, LibraryVec[i].Height);
        }

        v2Sqlite.close();
     }

     void readFromDB(string path)
     {
         SqliteDB sqlite(path);
         try
         {
             auto isOpened = sqlite.isOpened();
             if(isOpened)
             {
                 //>>>----------------------------------------------------------------------------------------------------------
                 //1.读取版本号
                 string selectedString = "select Version from Job";
                 sqlite.prepare(selectedString);
                 Version = sqlite.executeScalar<string>(selectedString);

                 bool isConvertToV1 = false;
                 if(Version!="V2")
                 {
                     if(Version=="V1")
                     {
                         isConvertToV1 = true;
                         cout << "读取程序的版本为V1，进行自动的版本转换, 数据库更新为v2" <<endl;
                         convertFromV1(sqlite);

                         return;
                     }
                 }
                  else
                 {
                        //正常读取V2的代码， 此次省略
                 }

                 sqlite.reset();
                 sqlite.close();
             }
         }
         catch(string& ex)
         {
             cout<<ex.data()<<endl;
             if(sqlite.isOpened())
             {
                 sqlite.reset();
                 sqlite.close(); //发生异常了需要特别注意需要关闭数据库
             }
         }
     }
};

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    // 1 v1 版本正常读取数据库
    //1.1 打开数据库
    JOB1 job1;
    job1.readFromDB(sqliteDataPath+"v1");

    //>>>----------------------------------------------------------------------------------------------------------
    //2 v2 版本读取v1，发生版本不兼容， 需要自动进行版本转换
    JOB2 job2;
    job2.readFromDB(sqliteDataPath+"v1");
}
