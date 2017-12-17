#ifndef CHANGEQMLCOLOR_HPP
#define CHANGEQMLCOLOR_HPP

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QColor>
#include <QVariant>

class ChangeQmlColor: public QObject
{
    Q_OBJECT
public:
    ChangeQmlColor(QObject* target, QObject *parent = 0);
    ~ChangeQmlColor();

protected slots:
    void onTimeout();

private:
    QTimer m_timer;
    QObject *m_target;
};

#endif // CHANGEQMLCOLOR_HPP
