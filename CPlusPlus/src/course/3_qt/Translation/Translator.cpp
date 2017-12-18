#include "Translator.hpp"

using namespace std;

//>>>--------------------------------------------------------------------------------------------------------------------
//constructor & destructor

Translator::Translator(QObject *pParent):
    QTranslator(pParent)
{
    // 使用以下命令生成翻译文件
    //lupdate -recursive ./ -ts translator_zh.ts

    setLangType(Translator::LangType::CN);
}

//<<<--------------------------------------------------------------------------------------------------------------------

//>>>--------------------------------------------------------------------------------------------------------------------
//get & set functions

Translator::LangType Translator::langType() const
{
    return this->m_langType;
}

void Translator::setLangType(Translator::LangType langType)
{
    chageLangType(langType);
    emit langTypeChanged();

    //这一行仅仅是用于测试Qt::tr(),可以删除
    Text txt;
    cout << txt.text().toStdString() << endl;
}

QQmlEngine *Translator::pEngine() const
{
    return m_pEngine;
}

void Translator::setPEngine(QQmlEngine *pEngine)
{
    m_pEngine = pEngine;
}

//<<<--------------------------------------------------------------------------------------------------------------------

//>>>--------------------------------------------------------------------------------------------------------------------
//slot functions

void Translator::chageLangType(Translator::LangType langType)
{
    if( langType == this->m_langType )
    {
        return;
    }
    this->m_langType = langType;
    QTranslator::load(this->m_qmFilePaths[(int)langType]);

    if( nullptr != this->m_pEngine )
    {
        this->m_pEngine->retranslate();
    }
}

//<<<--------------------------------------------------------------------------------------------------------------------

//>>>--------------------------------------------------------------------------------------------------------------------
//static functions

Translator *Translator::instance()
{
    static Translator* instance{ nullptr };

    if(!instance)
    {
        instance = new Translator();
    }
    return instance;
}

//<<<--------------------------------------------------------------------------------------------------------------------





