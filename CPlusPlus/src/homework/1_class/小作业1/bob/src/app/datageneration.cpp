#include "datageneration.hpp"

using namespace std;
using namespace App;
using namespace Job;
using namespace SSDK;


DataGeneration::DataGeneration()
{

}

DataGeneration::~DataGeneration()
{

}

void DataGeneration::generateInspectionData(int objCnt,
                                            MeasuredObj measuredObjArr[],
                                            InspectionData * pInspectionData)
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //定义随机生成基板数据的范围
        //定义基板x,y原点坐标为10,长和宽均为100(单位:mm,下同)
        double originalX = 0, originalY = 0, sizeX = 100, sizeY = 100;

        //检测对象的尺寸最大值为10,最小值为0.5
        double maxSize = 10 , minSize = 0.5;
        //板子边缘距离(板边距离检测对象的距离)
        double boardMargin = 3;
        //计算出检测对象坐标的最大值与最小值
        double maxPos = sizeX - maxSize -boardMargin;
        double minPos = minSize + boardMargin;
        //检测对象的角度最大值与最小值
        double maxAngle = 360;
        double minAngle = 0;

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //随机生成指定数量的MeasureObj数据,并将数据添加至 measurdObjList中
        srand((unsigned)time(NULL));                    //初始化随机数

        MeasuredObjList measuredObjList;      //实例化一个列表对象,存储检测对象数据

        //根据传入参数,生成指定大小的链表
        for (int i = 0; i < objCnt; ++i)
        {
            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //生成一个rectangle对象,x,y坐标,角度,及长和宽均为随机生成
            //V2 bob 添加生成检测对象的角度
            auto rect = Rectangle(NumRandom::randomDouble(maxPos,minPos),
                                  NumRandom::randomDouble(maxPos,minPos),
                                  NumRandom::randomDouble(maxSize,minSize),
                                  NumRandom::randomDouble(maxSize,minSize),
                                  NumRandom::randomDouble(maxAngle,minAngle));
            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //给measureObj数组中的元素赋值
            //生成指定对象的40%检测对象为chip元件
            string namePrefix;                  //元件名的前缀
            string nameIndex;                   //元件名字的索引号
            string name;                        //元件名

            double chipRatio = 0.4;             //生成chip元件的比例

            //生成指定对象的40%检测对象为chip元件,60%检测对象为ic
            if(i < chipRatio * objCnt )
            {
                namePrefix = "chip";                            //元件名的前缀
                nameIndex = FormatConvertion::intToString(i+1); //当前元件的索引号
                name = namePrefix + nameIndex;
            }
            else
            {
                namePrefix = "ic";
                nameIndex = FormatConvertion::intToString(i - chipRatio * objCnt + 1);
                name = namePrefix + nameIndex;
            }
            measuredObjArr[i].body() = rect; //将当前对象的rectangle变量赋值
            measuredObjArr[i].setName(name);       //设置已检测对象的名称
            //将当前检测对象添加至链表中
            measuredObjList.pushTail(&measuredObjArr[i]);
        }
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step3
        //生成board数据(基板名称,x,y原点坐标,基板的长和宽)
        Board board;
        board.setName("iphone");
        board.setOriginalX(originalX);
        board.setOriginalY(originalY);
        board.setSizeX(sizeX);
        board.setSizeY(sizeY);
        board.measuredObjs() = measuredObjList;
        pInspectionData->board() = board;
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //step4
        //生成inspectionData数据(检测程式的版本信息,检测程式上次保存时间)
        //V2 bob    将自动生成检测程式的版本号设置为V2
        string versionName = "V2";
        pInspectionData->setVersion(versionName);

        time_t currentTime = time(NULL);
        tm * pTime = localtime(&currentTime);             //获取当前系统时间的地址
        //获取时间,格式为 ( xx年/xx月/xx日  x时:x分:x秒)
        string lastEditingTime = FormatConvertion::intToString(pTime->tm_year+1900) +
                "/" + FormatConvertion::intToString(pTime->tm_mon+1) +
                "/" + FormatConvertion::intToString(pTime->tm_mday) +
                " " + FormatConvertion::intToString(pTime->tm_hour) +
                ":" + FormatConvertion::intToString(pTime->tm_min) +
                ":" + FormatConvertion::intToString(pTime->tm_sec);
        pInspectionData->setLastEditingTime(lastEditingTime);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
    catch(const exception &ex)
    {
        THROW_EXCEPTION(string ("随机生成检测程式数据错误!") + ex.what());
    }
}
