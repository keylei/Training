#include "board.hpp"

using namespace Job;

Board::Board()
{

}


Board::~Board()
{

}


void Board::writeToXml(QString path)
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.创建传入路径指定的xml文件
        QFile file(path);
        if(!file.open(QFile::ReadOnly))
        {
            THROW_EXCEPTION("XML文件创建不成功");
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.解析原来的xml文件加入到doc中
        QDomDocument doc;
        if(!doc.setContent(&file))  //若解析错误则关闭文件并抛出异常
        {
            file.close();
            THROW_EXCEPTION("解析xml文件错误");
        }
        file.close();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.创建一级子节点board并存入数据
        QDomElement root = doc.documentElement();   //创建根节点

        //创建next子节点board:
        QDomElement board = doc.createElement(QString::fromStdString(this->m_name));
        board.setAttribute("板宽",QString::number(this->m_sizeX));
        board.setAttribute("板长",QString::number(this->m_sizeY));
        board.setAttribute("x原点",QString::number(this->m_originalX));
        board.setAttribute("y原点",QString::number(this->m_originalY));

        //获取链表首个元素地址
        Job::MeasuredObj *pWritingObj = (this->m_measuredObjs).pHeadMeasuredObj();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //4.创建board的子节点object,并存入数据
        QDomElement object;        //board的子节点object

        //存入所有原件的数据
        for ( int i = 1; i <= (this->m_measuredObjs).size(); ++i)
        {
            //存入一个元件的数据：
            object = doc.createElement(QString::fromStdString((*pWritingObj).name()));
            object.setAttribute("高度",QString::number(((*pWritingObj).body()).height()) );
            object.setAttribute("宽度",QString::number(((*pWritingObj).body()).width()) );
            object.setAttribute("x坐标",QString::number(((*pWritingObj).body()).xPos()) );
            object.setAttribute("y坐标",QString::number(((*pWritingObj).body()).yPos()) );
            if("V2" == this->m_version)
                object.setAttribute("角度",QString::number(((*pWritingObj).body()).angle()) );
            board.appendChild(object);  //添加boject到board节点

            //将待写入的元素指针改为指向链表的下一个元素
            pWritingObj = (*pWritingObj).pNextMeasuredObj();
        }

        root.appendChild(board);        //添加board到根节点

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //5.输出到文件
        if(!file.open(QFile::WriteOnly|QFile::Truncate))    //若打开文件失败
            THROW_EXCEPTION("打开xml文件失败");
        QTextStream out_stream(&file);
        doc.save(out_stream,4);         //以缩进4格方式输出
        file.close();                   //关闭文件
    } //end of try
    catch(const SSDK::CustomException& ex)
    {
        //加上这一层的异常信息，异常上抛
        THROW_EXCEPTION(ex.what());
    }
}

