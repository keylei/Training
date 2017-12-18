#include "Text.hpp"


Text::Text(QObject *parent)
{

}

Text::~Text()
{

}

QString Text::text() const
{
    return QObject::tr("from C++");
}

void Text::setText(QString text)
{
    this->m_text = text;
    emit textChanged();
}
