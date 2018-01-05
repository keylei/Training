#include "measuredobj.hpp"

using namespace SSDK;


Job::MeasuredObj::MeasuredObj(std::string name, ShapeType shapeType)
{
    try
    {
        this->m_name = name;            //检测对象的名称

        double maxPos = 100;            //检测对象x,y轴中心点坐标的最大值
        double minPos = 0;              //检测对象x,y轴中心点坐标的最小值
        double widthMax = 10;           //检测对象宽度的最大值
        double widthMin = 0.5;          //检测对象宽度的最小值
        double heightMax = 10;          //检测对象高度的最大值
        double heightMin = 0.5;         //检测对象高度的最小值
        double angleMax = 360;          //检测对象角度的最大值
        double angleMin = 0;            //检测对象角度的最小值
        double maxRadius = 10;          //检测对象半径的最大值
        double minRadius = 0.5;         //检测对象半径的最小值

        if(shapeType == ShapeType::CIRCLE)         //如果形状类型为0,则生成为圆形框
        {
            this->m_pShape = new Circle(
                                 NumRandom::randomDouble(maxPos,minPos),
                                 NumRandom::randomDouble(maxPos,minPos),
                                 NumRandom::randomDouble(maxRadius,minRadius));
        }
        else if (shapeType == ShapeType::RECTANGLE) //如果形状类型为1,则生成为矩形框
        {
            this->m_pShape = new Rectangle(
                                 NumRandom::randomDouble(maxPos,minPos),
                                 NumRandom::randomDouble(maxPos,minPos),
                                 NumRandom::randomDouble(widthMax,widthMin),
                                 NumRandom::randomDouble(heightMax,heightMin),
                                 NumRandom::randomDouble(angleMax,angleMin));
        }
        else
        {
           THROW_EXCEPTION("输入形状类型错误!");
        }
    }
    catch(...)
    {
        if(nullptr != this->m_pShape)
        {
            delete this->m_pShape;
            this->m_pShape = nullptr;
        }
        THROW_EXCEPTION("创建检测对象错误");
    }
}

Job::MeasuredObj::~MeasuredObj()
{
    try
    {
        if(nullptr != this->m_pShape)
        {
            delete this->m_pShape;
            this->m_pShape = nullptr;
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("删除检测对象形状类型错误");
    }
}
