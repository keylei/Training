#include "StyleSetting.hpp"

using namespace SSDK;

StyleSetting::StyleSetting(QObject *parent)
{
    this->m_themeList = QEnumStringList<StyleSetting>(std::string("ThemeType"));
    int cnt = m_themeList.count();
    for (int i = 0; i < cnt ; ++i)
    {
        this->m_backgroundColorList.push_back(QColor());
        this->m_foregroundColorList.push_back(QColor());
        this->m_primaryColorList.push_back(QColor());
        this->m_accentColorList.push_back(QColor());
    }

    //自定义初始值
    this->m_backgroundColorList[(int)ThemeType::USER_DEFINED] = QColor("#FFF59D");
    this->m_foregroundColorList[(int)ThemeType::USER_DEFINED] = QColor("#FFEB3B");
    this->m_primaryColorList[(int)ThemeType::USER_DEFINED] = QColor("#EF9A9A");
    this->m_accentColorList[(int)ThemeType::USER_DEFINED] = QColor("#009688");
}
StyleSetting::~StyleSetting()
{

}

void StyleSetting::setThemeColor(int themeIndex, ColorType colorType, QColor color)
{
    if( themeIndex > -1 && themeIndex < this->m_themeList.count())
    {
        switch (colorType)
        {
        case ColorType::ACCENT:
            this->m_accentColorList[themeIndex] = color;
            break;

        case ColorType::BACKGROUND:
            this->m_backgroundColorList[themeIndex] = color;
            break;

        case ColorType::FORGROUND:
            this->m_foregroundColorList[themeIndex] = color;
            break;

        case ColorType::PRIMARY:
            this->m_primaryColorList[themeIndex]= color;
            break;

        default:
            break;
        }
    }
}

QColor StyleSetting::getThemeColor(int themeIndex , ColorType colorType)
{
    if( themeIndex > -1 && themeIndex < this->m_themeList.count())
    {
        switch (colorType)
        {
        case ColorType::ACCENT:
            return this->m_accentColorList.at(themeIndex);

        case ColorType::BACKGROUND:
            return this->m_backgroundColorList.at(themeIndex);

        case ColorType::FORGROUND:
            return this->m_foregroundColorList.at(themeIndex);

        case ColorType::PRIMARY:
            return this->m_primaryColorList.at(themeIndex);

        default:
            break;
        }
    }
}

//QStringList StyleSetting::getThemeTypeList()
//{
//    return QEnumStringList<StyleSetting>(std::string("ThemeType"));
//}

QStringList StyleSetting::themeList()
{
    if(0 == this->m_themeList.count())
    {
        this->m_themeList = QEnumStringList<StyleSetting>(std::string("ThemeType"));
    }

    return this->m_themeList;
}

//QColor StyleSetting::primaryColor() const
//{
//    return m_primaryColor;
//}
//QColor StyleSetting::accentColor() const
//{
//    return m_accentColor;
//}
//QColor StyleSetting::foregroundColor() const
//{
//    return m_foregroundColor;
//}
//QColor StyleSetting::backgroundColor() const
//{
//    return m_backgroundColor;
//}


int StyleSetting::themeIndex() const
{
    return this->m_themeIndex;
}

void StyleSetting::setThemeIndex(const int themeIndex)
{
    this->m_themeIndex = themeIndex;
}

void StyleSetting::readFromFile(QString filePath)
{

}
void StyleSetting::writeToFile(QString filePath)
{

}


