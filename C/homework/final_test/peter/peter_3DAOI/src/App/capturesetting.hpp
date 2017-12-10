#ifndef CAPTURESETTING_HPP
#define CAPTURESETTING_HPP

#include <iostream>

#include <QSettings>
#include <QFile>
#include <QMetaEnum>

#include "../SDK/customexception.hpp"
#include "../SDK/formatconversion.hpp"

namespace App
{
    //>>>--------------------------------------------------------------------------------
    // enum
    enum class ImageBit //图像位数,包括8位和16位
    {
        BIT8,
        BIT16
    };

    /**
     *  @brief CaptureSetting
     *
     *          CaptureSetting类是检查配置文件的类,所检查的配置文件包括相机的图
     *      像面阵宽度、高度等程序运行时所必需的配置,没有或者配置错误都将导致检
     *      测数据错误,所以检测到异常的配置必须抛异常,并且中止程序继续运行.
     *
     *      //rime -1 这种注释稍微带下就可以了，不需要穷举
     *      类的成员变量包含:
     *          1.相机的图像面阵宽度    2.相机的图像面阵高度    3.图像支持的位数
     *      类的成员函数包含:
     *          1.加载配置文件    2.读取配置文件
     *      使用操作:
     *          将配置文件路径传入loadCaptureSetting()函数,读取配置文件中的配置:
     *              a.没有配置文件则直接抛出异常,停止程序运行
     *              b.有配置文件则检查参数是否正确,不正确则抛出异常,停止程序运行
     *
     *  @author peter
     *  @version 1.00 2017-11-22 peter
     *                note:create it
     */
    class CaptureSetting
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor
        /**
         * @brief CaptureSetting
         *      默认构造函数
         * @param N/A
         * @return N/A
         */
        CaptureSetting();
        /**
         * @brief ~CaptureSetting
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual~CaptureSetting();

        //>>>--------------------------------------------------------------------------------
        // load function
        /**
         *  @brief loadCaptureSetting
         *      加载配置文件
         *          1.配置文件存在:读取配置文件文件，
         *          2.配置文件不存在:直接退出程序
         *  @param path
         *      待加载的配置文件路径
         *  @return N/A//
         */
        void loadCaptureSetting( const QString& path );


    private:
        //>>>--------------------------------------------------------------------------------
        // read & write function
        /**
         *  @brief readCaptureSetting
         *      配置文件存在时读取配置文件中的信息
         *  @param path
         *      待读取的配置文件路径
         *  @return N/A
         */
        void readCaptureSetting( const QString& path );


    private:
        int m_imageWidth {3072};        // 相机的图像面阵宽度
        int m_imageHeight {4096};       // 相机的图像面阵高度
        ImageBit m_imageBit {ImageBit::BIT8};


    };
}//End of namespace App

#endif // CAPTURESETTING_HPP
