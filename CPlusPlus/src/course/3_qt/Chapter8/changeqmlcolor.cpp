#include "changeqmlcolor.hpp"

ChangeQmlColor::ChangeQmlColor(QObject* target, QObject *parent):
    QObject(parent),
    m_timer(this),
    m_target(target)
{
    //绑定了onTimeout槽
    qsrand(QDateTime::currentDateTime().toTime_t());
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    m_timer.start(1000);
}

ChangeQmlColor::~ChangeQmlColor()
{

}

void ChangeQmlColor::onTimeout()
{
    QColor color = QColor::fromRgb(qrand()%256, qrand()%256,qrand()%256);
    this->m_target->setProperty("color", color);
}
