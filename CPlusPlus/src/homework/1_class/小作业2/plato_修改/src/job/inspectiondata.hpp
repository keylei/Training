//#ifndef INSPECTIONDATA_H
//#define INSPECTIONDATA_H

//#include <QFile>
//#include <QDoubleValidator>
//#include <QDomDocument>
//#include <QXmlStreamWriter>
//#include <QTextStream>

//#include "Board.hpp"
//#include "sdk/customexception.hpp"

//namespace Job
//{
//    /**
//     *  @brief 检测数据类，存放一次检测程式的所有数据，（包括程式版本号、最后一次修改时间，
//     *         基板信息和基板上所有元件信息），能够将程式的所有信息导出为xml格式文件
//     *
//     *  @author lynn
//     *  @version 1.00 2017-11-29 lynn
//     *                note:create it
//     */
//    class InspectionData
//    {
//    public:
//        //>>>-------------------------------------------------------------------------------------------------------------------------------------
//        //1.constructor & destructor

//        /*
//        *  @brief   类的构造函数，占无内容
//        *  @param   N/A
//        *  @return  N/A
//        */
//        InspectionData();

//        /*
//        *  @brief   类的析构函数，占无内容
//        *  @param   N/A
//        *  @return  N/A
//        */
//        ~InspectionData();

//        //>>>-------------------------------------------------------------------------------------------------------------------------------------
//        //1.set & get function
//        /*
//        *  @brief   获得检测数据中的基板的数据
//        *  @param   N/A
//        *  @return  检测数据中的基板的数据
//        */
//        Job::Board &board() { return this->m_board; }

//        /*
//        *  @brief   获取检测程式的版本号
//        *  @param   N/A
//        *  @return  检测程式的版本号
//        */
//        std::string version() { return this->m_version; }
//        /*
//        *  @brief   修改检测程式的版本号
//        *  @param   要设置的版本号
//        *  @return  N/A
//        */
//        void setVersion(std::string version) { this->m_version = version; }

//        /*
//        *  @brief   获取检测程式的最后一次修改时间
//        *  @param   N/A
//        *  @return  检测程式的最后一次修改时间
//        */
//        std::string lastEditingTime() { return this->m_lastEditingTime; }
//        /*
//        *  @brief   修改检测程式的最后一次修改时间
//        *  @param   要设置的检测程式最后一次修改时间
//        *  @return  N/A
//        */
//        void setLastEditingTime(std::string lastEditingTime)
//        {
//            this->m_lastEditingTime = lastEditingTime;
//        }

//        //>>>-------------------------------------------------------------------------------------------------------------------------------------
//        //2.member function

//        /*
//        *  @brief   将检测程式的所有信息（包括基板信息和基板上所有元件的信息）导出为xml文件
//        *  @param   导出xml文件的路径
//        *  @return  N/A
//        */
//        void writeToXml(QString path);

//    private:
//        //>>>-------------------------------------------------------------------------------------------------------------------------------------
//        //3.member function
//        Job::Board m_board;
//        std::string m_version{"\0"};
//        std::string m_lastEditingTime{"\0"};
//    };

//}//End of namespace Job

//#endif // INSPECTIONDATA_H
