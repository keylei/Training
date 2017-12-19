#ifndef STYLESETTING_HPP
#define STYLESETTING_HPP

#include <vector>

#include <QObject>
#include <QColor>
#include <QString>
#include <QMetaEnum>

#include "metaeeum.hpp"

/**
 *  @brief 这个类可以实现程序在运行期间的主题切换已经颜色配置，具体要配置qml界面使用
 *
 *  @author author
 *  @version 1.00 2017-12-20 author
 *                note:create it
 */
class StyleSetting: public QObject
{
    Q_OBJECT

    Q_ENUMS(ThemeType)
    Q_ENUMS(ColorType)
    Q_PROPERTY(int themeIndex READ themeIndex  WRITE setThemeIndex)

    //QStringList可以直接作为属性传输到QML，不过如果没有NOTIFYable，会抱一个警告
    //这个也可以直接通过Q_INVOKABLE成员函数可以避免
    Q_PROPERTY(QStringList themeList READ themeList )

public:

    enum class ThemeType
    {
        LIGHT,
        DARK,
        USER_DEFINED
    };

    enum class ColorType
    {
        PRIMARY,
        ACCENT,
        FORGROUND,
        BACKGROUND
    };

    StyleSetting(QObject* parent = 0);
    ~StyleSetting();

    Q_INVOKABLE void setThemeColor (int themeIndex,
                                             ColorType colorType,
                                             QColor color) ;
    Q_INVOKABLE QColor getThemeColor (int themeIndex, ColorType colorType) ;

    //注意: 这个函数很关键，直接把枚举转换为可以为combobox直接作为model的QStringList
//    Q_INVOKABLE QStringList getThemeTypeList () ;

    QStringList themeList () ;

    ThemeType theme() const;
    void setTheme(const ThemeType &theme);

    int themeIndex() const;
    void setThemeIndex(const int themeIndex);

    void readFromFile(QString filePath);
    void writeToFile(QString filePath);

private:
    // 注意，这里为了方便和界面进行绑定，都使用Index进行定位
    int m_themeIndex { 1 } ;
    //和Combobox进行绑定，把QEnum转换为StringList再做处理
    QStringList m_themeList;
    QList<QColor> m_primaryColorList /*{ QColor("#FFF59D") }*/;
    QList<QColor> m_accentColorList  /*{ QColor("#FFEB3B") }*/;
    QList<QColor> m_foregroundColorList/*{  QColor("#EF9A9A")}*/;
    QList<QColor> m_backgroundColorList/*{ QColor("#009688")}*/;
};

#endif // STYLESETTING_HPP
