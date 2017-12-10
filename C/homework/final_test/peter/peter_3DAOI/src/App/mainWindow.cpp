#include "mainWindow.hpp"

using namespace App;
using namespace Job;
using namespace SDK;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & destructor
MainWindow::MainWindow()
{

}

MainWindow::~MainWindow()
{
    MeasuredObj * pTmpObj = this->m_inspectionData.board().measuredList().pHead();
    while ( nullptr !=  pTmpObj )
    {
        pTmpObj = this->m_inspectionData.board().measuredList().pHead()->pNext();
        delete this->m_inspectionData.board().measuredList().pHead();
        this->m_inspectionData.board().measuredList().setHead(pTmpObj);
    }
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//load configure & scan folder function
void MainWindow::loadSetting( const QString& appSettingPath,
                  const QString& captureSettingPath )
{
    //rime -1 最上层一定要进行try...Catch
    m_appSetting.loadAppSetting(appSettingPath);
    m_captureSetting.loadCaptureSetting(captureSettingPath);
}

void MainWindow::scanJobFolder(const QString& path)
{
    QDir dir(path);
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step1:判断文件夹是否存在，不存在则创建
    if(!dir.exists())
    {
        std::cout << path.toStdString() << " is not exists!"<< std::endl;
        bool isCreatedPath = dir.mkpath(path);
        //文件夹不存在，判断是否创建成功，不成功则抛出异常
        if( !isCreatedPath )
        {
            //创建配置文件失败,抛出异常.
            THROW_EXCEPTION("Path is not existed and create path error!");
        }
    }
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step2:扫描检测程式
    QStringList filters;    //创建过滤器列表，过滤xml、txt为后缀的文件
    filters << "*[^xml|^txt]";
    dir.setNameFilters(filters);

    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    //没有要读取的程式文件，向程式中写入默认数据
    if ( 0 == list.size() )
    {
        int chipCnt {20};
        int icCnt {30};
        generateObjsRandomly(chipCnt,icCnt);

        QString dbPath {path};
        dbPath = dbPath.append("iPhoneV2");
        m_inspectionData.writeToDB(dbPath);
    }
    else
    {
        //将扫描的文件打印在终端上
        for (int i = 0; i < list.size(); ++i)
        {
            std::cout << qPrintable( QString("%1:%2\n").arg(i+1).arg(list.at(i).fileName()) );
        }
        int index {0};
        //选择需要读取的检查程式文件
        do
        {
            std::cout << "\nPlease choice the file!(1-" << list.size() << ")\n";
            std::cin >> index;
            //判断输入是否为数字
            if(!std::cin)
            {
                std::cout << "Error! Not a digit!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                index = 0;
            }
        }
        while( index > list.size() || index <= 0);
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        // step3:读取用户选择的文件
        QString dbPath = list.at(index-1).filePath();
        m_inspectionData.readFromDB(dbPath);
        //输出到xml文件中
        QString xmlPath = dbPath.append(".xml");
        m_inspectionData.writeToXml(xmlPath);

    }
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//generate data function
void MainWindow::generateObjsRandomly( int chipCnt, int icCnt )
{
    //rime -1 主要要保证所有的元件的边界都在板子范围内
    //rime -1 为什么元件的大小的最大值就直接和board的最大值一样了
    //rime -1 元件不可能出现在原点的左下角


    int minPosX {25};
    int maxPosX {175};
    int minPosY {25};
    int maxPosY {175};
    int minAngle {0};
    int maxAngle {90};
    int minWidth {100};
    int maxWidth {150};
    int minHeight {100};
    int maxHeight {150};
    int precision {2};

    //>>>--------------------------------------------------------------------------------
    // 1.默认的版本和当前编辑时间
    m_inspectionData.setVersion("V2");
    auto currentTime = std::time(nullptr);
    auto formatTime = *std::localtime(&currentTime);

    std::ostringstream timeStream;
    timeStream << std::put_time(&formatTime, "%Y-%m-%d %H:%M:%S");
    m_inspectionData.setEditingTime(timeStream.str());

    //>>>--------------------------------------------------------------------------------
    // 2.默认的job程式名,原点位置,尺寸大小
    this->m_inspectionData.board().setName("iPhone");
    this->m_inspectionData.board().setOriginalX(0.00);
    this->m_inspectionData.board().setOriginalY(0.00);
    this->m_inspectionData.board().setSizeX(200.00);
    this->m_inspectionData.board().setSizeY(200.00);

    //rime -1 这个为什么和上面的分隔线长度不一
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //3.生成随机数据

    std::stringstream rectNameSteam;
    MeasuredObj* pMeasureObj = nullptr;
    for ( int i = 1; i <= chipCnt+icCnt; ++i )
    {
        pMeasureObj = new MeasuredObj();
        if ( i <= chipCnt )
        {
            rectNameSteam<<"chip_"<<std::setfill('0')<<std::setw(3)<<i;
        }
        else
        {
            rectNameSteam<<"ic_"<<std::setfill('0')<<std::setw(3)<<i-chipCnt;
        }
        pMeasureObj->setName(rectNameSteam.str());
        pMeasureObj->body().setPosX(RandomDigit::randomDigit(precision,minPosX,maxPosX));
        pMeasureObj->body().setPosY(RandomDigit::randomDigit(precision,minPosY,maxPosY));
        pMeasureObj->body().setAngle(RandomDigit::randomDigit(precision,minAngle,maxAngle));
        pMeasureObj->body().setWidth(RandomDigit::randomDigit(precision,minWidth,maxWidth));
        pMeasureObj->body().setHeight(RandomDigit::randomDigit(precision,minHeight,maxHeight));

        this->m_inspectionData.board().measuredList().pushBack(*pMeasureObj);
        rectNameSteam.str("");
    }
    pMeasureObj = nullptr;
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------








