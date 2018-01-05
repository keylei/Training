//#include "mainwindow.hpp"

//using namespace std;
//using namespace Job;
//using namespace App;
//using namespace SSDK;
//using namespace SSDK::DB;

//MainWindow::MainWindow()
//{
//    this->m_pMeasuredObj = nullptr;
//}

//MainWindow::~MainWindow()
//{
//    delete [] this->m_pMeasuredObj;
//    this->m_pMeasuredObj = nullptr;
//}

//void MainWindow::loadJob(QString path)
//{
//    try
//    {
//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step1
//        //扫描目录下的检测程式
//        //如果目录不存在,则抛出异常
//        QDir dir(path);

//        if(!dir.exists())
//        {
//            THROW_EXCEPTION("读取检测程式的文件路径不存在!");
//        }

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step2
//        //过滤目录下所有的xml文件
//        QStringList filters;                //创建过滤器列表，过滤xml为后缀的文件
//        filters << "*[^xml]";               //"*[^x|^t][^m|^x][^l|^t]";
//        dir.setNameFilters(filters);        //过滤目录下的xml文件

//        //扫描目录下的文件
//        dir.setFilter(QDir::Files);
//        //获取文件目录下排除.xml文件后的文件列表
//        QFileInfoList list = dir.entryInfoList();

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step3
//        //读取目录下的检测程式
//        SqliteDB sqlite;                                //实例化一个检测程式对象

//        if (0 == list.size())   //判断目录下是否存在检测程式,则随机生成一个检测程式数据
//        {
//            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//            // step3.1 随机生成一笔检测程式数据
//            //开辟一片存放检测对象数据的空间
//            this->m_pMeasuredObj = new MeasuredObj[OBJ_CNT] ;

//            //随机一笔检测程式数据生成数据
//            DataGenerator::generateInspectionData(OBJ_CNT,
//                                                   this->m_pMeasuredObj,
//                                                   &m_inspectionData);

//            //step3.2 将检测程式数据写入到检测程式文件中(sqlite数据库)
//            //将生成检测程式的名称改成V2
//            QString file = path + "V2";
//            //判断检测程式是否打开
//            sqlite.open(file.toStdString());

//            if (sqlite.isOpened())
//            {
//                writeInspectionDataToJob(&m_inspectionData,&sqlite);
//                sqlite.reset();
//                sqlite.close();
//            }
//            else
//            {
//                THROW_EXCEPTION("写入检测程序数据时,打开检测程式错误!");
//            }
//        }
//        else        // 如果目录下有检测程式,将目录中检测程式文件显示在终端上,供用户选择
//        {
//            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//            //step3.3
//            //在终端上显示ID号和文件名称,供用户选择
//            cout << "ID Filename" << endl;

//            for (int i = 0; i < list.size(); ++i)  //将文件及文件的序号显示在终端上
//            {
//                QFileInfo fileInfo = list.at(i);

//                cout << qPrintable(QString("%1  %2")
//                                   .arg(i + 1)
//                                   .arg(fileInfo.fileName()));
//                cout << endl;
//            }

//            int jobIndex{0};                       //选择对应检测程式文件的索引号

//            //在终端上显示提示信息,让用户输入检测程式的索引号
//            cout << endl;
//            cout << "请输入文件的ID号 (1-" << list.size()<<"):";
//            cin >> jobIndex;

//            //判断用户输入的索引号是否符合要求
//            //判断用户输入是否为整数,如果不是整数,则输出错误提示,并重新输入
//            //如果输入为整数,判断输入的整数是否匹配索引号
//            //若果输入值与文件索引号不匹配,则输出错误提示,并重新输入
//            //如果输入值与文件索引号匹配,则跳出循环
//            while (true)
//            {
//                if( (jobIndex - (int)jobIndex) == 0 )
//                {

//                    if(jobIndex > 0 && jobIndex <= list.size())
//                    {
//                        break;
//                    }
//                }
//                cout << "输入非法数字,请重新输入: ";
//                std::cin.clear();
//                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
//                jobIndex = 0;
//                cin >> jobIndex;
//            }

//            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//            //step3.4
//            //读取检测程式中文件的数据
//            QString file = list.at(jobIndex-1).filePath(); //获取用户选择的检测程式路径
//            sqlite.open(file.toStdString());               //获取检测程式的打开状态

//            if(sqlite.isOpened())
//            {
//                //将检测程式中的数据读取到内存中
//                readInspectionDataFromJob(&m_inspectionData,&sqlite);
//                sqlite.reset();
//                sqlite.close();
//            }
//            else
//            {
//                THROW_EXCEPTION("读取检测数据时,打开检测程式错误!")
//            }
//        }
//    }
//    catch(const exception& ex)
//    {
//        THROW_EXCEPTION(string("加载检测程式错误!") + ex.what());
//    }
//}


////>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
////将inspectionData数据写入到检测程序中
//void MainWindow::writeInspectionDataToJob(InspectionData *pInspectionData,
//                                          SqliteDB *pSqlite)
//{
//    try
//    {
//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step2
//        //创建Job表,并在表中添加"Version"和"LastEditingTime"两个字段
//        //将相应的数据写入数据库
//        string sqlCreate = "CREATE TABLE Job(Version TEXT,LastEditingTime TEXT);";
//        pSqlite->execute(sqlCreate);

//        //插入Version数据及LastEditingTime字段数据
//        string sqlInsert = "INSERT INTO Job(Version,LastEditingTime) VALUES(?,?);";
//        pSqlite->execute(sqlInsert,pInspectionData->version(),
//                         pInspectionData->lastEditingTime());
//        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step3
//        //创建Board表,并在表中添加"Name","OriginalX","OriginalY","SizeX","SizeY"字段
//        //并将相应的数据写入数据库
//        sqlCreate = "CREATE TABLE Board(Name TEXT,OriginalX REAL,OriginalY REAL,SizeX REAL,SizeY REAL);";
//        pSqlite->execute(sqlCreate);

//        //插入Board表中Name,OriginalX,OriginalY,SizeX,SizeY字段的数据
//        sqlInsert = "INSERT INTO Board(Name,OriginalX,OriginalY,SizeX,SizeY) VALUES(?,?,?,?,?);";
//        pSqlite->execute(sqlInsert,pInspectionData->board().name(),
//                         pInspectionData->board().originalX(),
//                         pInspectionData->board().originalY(),
//                         pInspectionData->board().sizeX(),
//                         pInspectionData->board().sizeY());
//        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step4
//        //4.1创建MeasuredObjList表,并在表中添加"Name","PosX","PosY"
//        //"Width","Height"及"Angle"字段,并将列表中数据写入到数据库中
//        sqlCreate = "CREATE TABLE MeasuredObjList(Name TEXT,PosX REAL,PosY REAL,Width REAL,Height REAL,Angle REAL);";
//        pSqlite->execute(sqlCreate);

//        //4.2定义临时指针,取出MeasuredObjList中所有节点的数据,默认指向链表数据的头地址
//        MeasuredObj * pTmpObj = pInspectionData->board().measuredObjs().pHeadMeasuredObj();

//        //4.3将MeasuredObj中的数据插入到MeasuredObjList的表中
//        sqlInsert = "INSERT INTO MeasuredObjList(Name,PosX,PosY,Width,Height,Angle) VALUES(?,?,?,?,?,?);";
//        //执行插入语句
//        pSqlite->prepare(sqlInsert);
//        pSqlite->begin();

//        //将检测对象列表中索引数据插入到数据库的 MeasuredObjList 表中
//        while (nullptr != pTmpObj)
//        {
//            string str = pTmpObj->name();
//            pSqlite->executeWithParms(str.data(),
//                                      pTmpObj->body().xPos(),
//                                      pTmpObj->body().yPos(),
//                                      pTmpObj->body().width(),
//                                      pTmpObj->body().height(),
//                                      pTmpObj->body().angle());
//            //获取下一个检测对象的地址
//            pTmpObj = pTmpObj->pNextMeasuredObj();
//        }
//        pSqlite->commit();                      //将数据列表中数据一次性写入数据库
//        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//    }
//    catch (const exception &ex)
//    {
//        if(pSqlite->isOpened())
//        {
//            pSqlite->reset();
//            pSqlite->close();
//        }
//        THROW_EXCEPTION(string ("写入数据到检测程式错误!") + ex.what());
//    }
//}

//void MainWindow::readInspectionDataFromJob(InspectionData * pInspectionData,
//                                           SqliteDB * pSqlite)
//{
//    try
//    {
//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step1
//        //V2 增加读取检测程式的版本数据
//        //读取检测程式的版本号
//        //如果检测程式的版本号与当前软件版本一致,则读取检测程式数据
//        //如果检测程式版本号是更低版本,则将低版本的程式转换为与当前软件匹配的版本
//        //否则抛出异常
//        string selectedString = "select Version from Job";
//        pSqlite->prepare(selectedString);
//        string version = pSqlite->executeScalar<string>(selectedString);

//        if("V2" != version )
//        {
//            if( "V1"  == version )
//            {
//                version = "V2";
//                convertJobToV2(pSqlite);
//            }
//            else
//            {
//                THROW_EXCEPTION("检测程式版本有误,请确认!!");
//            }
//        }

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step2
//        //获取检测程式的版本号及最后一次编辑时间
//        pInspectionData->setVersion(version);

//        selectedString = "select LastEditingTime from Job";
//        pSqlite->prepare(selectedString);
//        string lastEditingTime = pSqlite->executeScalar<string>(selectedString);
//        pInspectionData->setLastEditingTime(lastEditingTime);

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step3
//        //获取基板数据,(基板的名称,基板的x,y原点坐标,基板的长,基板的宽)
//        Board board;
//        selectedString = "select * from Board";
//        pSqlite->prepare(selectedString);
//        pSqlite->step();
//        auto boardName  = pSqlite->columnValue(0);     //检测基板的名称
//        auto originalX = pSqlite->columnValue(1);      //检测基板x轴原点坐标
//        auto originalY = pSqlite->columnValue(2);      //检测基板y轴原点坐标
//        auto sizeX = pSqlite->columnValue(3);          //检测基板的长
//        auto sizeY = pSqlite->columnValue(4);          //检测基板的高

//        board.setName((string)boost::get<string>(boardName));
//        board.setOriginalX((double)boost::get<double>(originalX));
//        board.setOriginalY((double)boost::get<double>(originalY));
//        board.setSizeX((double)boost::get<double>(sizeX));
//        board.setSizeY((double)boost::get<double>(sizeY));

//        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//        //step4
//        //获取已检测对象的数据,具体数据如下:
//        //被检查对象的名称,x,y轴坐标,宽和高,角度
//        //获取检测程式中检测对象的数量
//        string sqlQuery = "SELECT COUNT(*) FROM MeasuredObjList";
//        pSqlite->prepare(sqlQuery);
//        int objCnt = pSqlite->executeScalar<int>(sqlQuery);

//        //根据检测程式中检测对象的数量新建一个存放检测对象数据的数组
//        this->m_pMeasuredObj = new MeasuredObj[objCnt];

//        MeasuredObjList measuredObjList;
//        selectedString = "select * from MeasuredObjList";
//        pSqlite->prepare(selectedString);

//        for (int i = 0; i < objCnt; ++i)
//        {
//            pSqlite->step();
//            auto name  = pSqlite->columnValue(0);     //检测对象的名称
//            auto xPos = pSqlite->columnValue(1);      //检测对象x轴坐标
//            auto yPos = pSqlite->columnValue(2);      //检测对象y轴坐标
//            auto width = pSqlite->columnValue(3);     //被检测对象的宽
//            auto height = pSqlite->columnValue(4);    //被检测对象的高
//            auto angle = pSqlite->columnValue(5);     //V2 添加检测对象的角度

//            auto rect = Rectangle((double)boost::get<double>(xPos),
//                                  (double)boost::get<double>(yPos),
//                                  (double)boost::get<double>(width),
//                                  (double)boost::get<double>(height),
//                                  (double)boost::get<double>(angle));

//            //设置检测对象的名称及rectangle对象
//            this->m_pMeasuredObj[i].body() = rect;
//            this->m_pMeasuredObj[i].setName((string)boost::get<string>(name));
//            //将检测对象添加到链表的尾部
//            measuredObjList.pushTail(&this->m_pMeasuredObj[i]);
//        }
//        //将measuredObjList对象赋值给board成员变量(m_measuredObjList)
//        board.measuredObjs() = measuredObjList;
//        //将board值赋值给InspectionData成员变量(m_board)
//        pInspectionData->board() = board;
//    }
//    catch(const exception &ex)
//    {
//        if(pSqlite->isOpened())
//        {
//            pSqlite->reset();
//            pSqlite->close();
//        }
//        THROW_EXCEPTION(string("读取检测程式异常!") + ex.what());
//    }
//}

//void MainWindow::convertJobToV2(SqliteDB *pSqlite)
//{
//    //将检测程式的的版本号修改为"V2"
//    string sqlUpdate = "UPDATE Version SET Version='V2'" ;
//    pSqlite->execute(sqlUpdate);

//    //将所有的检测对象添加Angle字段,并设置默认值为0
//    string addColumn = "ALTER TABLE MeasuredObjList ADD Angle REAL DEFAULT 0";
//    pSqlite->execute(addColumn);
//}


