#ifndef INSPECTIONDATA_HPP
#define INSPECTIONDATA_HPP

#include <iostream>
#include <iomanip>
#include <string>

#include <QDomDocument>
#include <QTextStream>
#include <QString>
#include <QFile>

#include "../DB/sqlitedb.hpp"
#include "../Job/board.hpp"

namespace Job
{
    /**
     *  @brief InspectionData
     *      InspectionData类是读取程式文件,并导出为xml文件的类
     *
     *      类的成员变量包含:
     *          1.数据类型为Board的成员(存放Board尺寸信息和数据信息的类)
     *          2.程式文件的版本
     *          3.程式文件最近一次的编辑时间
     *      类的成员函数功能包含:
     *          1.访存函数
     *          2.将默认数据写入程式文件
     *          3.读取传入的程式文件
     *          4.将程式文件的数据导出为xml文件
     *          5.打印程式文件的版本号、最近一次编辑时间
     *      使用操作:
     *          1.将程式文件路径传入readFromDB()函数,读取程式文件数据到内存
     *          2.将程式文件路径传入writeToDB()函数,将内存中的数据写入到数据库
     *          3.将程式文件路径传入writeToXml()函数,将内存中的数据导出为xml文件
     *          4.print()函数,直接打印当前程式的版本和最近一次编辑时间
     *
     *  @author peter
     *  @version 1.00 2017-11-24 peter
     *                note:create it
     */
    class InspectionData
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor function
        /**
         * @brief InspectionData
         *      默认构造函数
         * @param N/A
         * @return N/A
         */
        InspectionData();
        /**
         * @brief ~InspectionData
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual~InspectionData();

        //>>>--------------------------------------------------------------------------------
        // get & set function
        Job::Board& board(){return this->m_board;}

        std::string version(){return this->m_version;}
        void setVersion(std::string version){this->m_version = version;}

        //rime -1 last去哪里了
        std::string editingTime(){return this->m_lastEditingTime;}
        void setEditingTime(std::string time){this->m_lastEditingTime = time; }


        //>>>--------------------------------------------------------------------------------
        // write & read & print function
        /**
         * @brief writeToXml
         *     将内存中检测程式的Job,Board,MeasureObjs等信息写入xml文件中
         *          1.Job的版本号,最后编辑时间
         *          2.Board名字,起始点位置,长宽尺寸
         *          3.MeasureObjs中各原件的位置信息和长宽信息
         * @param path
         */
        void writeToXml(const QString &path);
        /**
         * @brief print
         *      打印程式文件的版本和最后编辑时间的信息
         * @param N/A
         * @return N/A
         */
        void print();
        /**
         * @brief readFromDB
         *      读取程式文件
         * @param path
         *      待读取的程式文件路径
         * @return N/A
         */
        void readFromDB(const QString &path);
        /**
         * @brief writeToDB
         *      将数据写入程式文件并导出
         * @param path
         *      导出程式文件的路径
         * @return N/A
         */
        void writeToDB(const QString &path);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // read & convert function
        /**
         * @brief readCurrentVersionDB
         *      读取当前的程式文件,将数据存入内存
         * @param sqlite
         *      打开的数据库文件
         * @return N/A
         */
        void readCurrentVersionDB(SSDK::DB::SqliteDB& sqlite);
        /**
         * @brief convertFromV1
         *      读取版本为V1的程式文件,将数据存入内存
         * @param sqlite
         *      打开的数据库文件
         * @return N/A
         */
        void convertFromV1(SSDK::DB::SqliteDB& sqlite);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



    private:
        Job::Board m_board;
        std::string m_version {"V2"};
        std::string m_lastEditingTime {"2000-01-01 00:00:00"};

    };
}//End of namespace Job


#endif // INSPECTIONDATA_HPP
