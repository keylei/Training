#include "colormaker.hpp"

ColorMaker::ColorMaker(QObject* parent):
    QObject(parent),
    m_algorithm(GenerateAlgorithm::RANDOM_RGB),
    m_currentColor(Qt::black),
    m_colorTimer(0)
{
    qsrand(QDateTime::currentDateTime().toTime_t());
}
ColorMaker::~ColorMaker()
{

}

QColor ColorMaker::currentColor() const
{
    return this->m_currentColor;
}
void ColorMaker::setCurrentColor(const QColor &currentColor)
{
    m_currentColor = currentColor;
    //一旦颜色发生修改，触发colorChanged信号
    emit colorChanged(m_currentColor);
}

QColor ColorMaker::timeColor() const
{
    QTime time = QTime::currentTime();
    int r = time.hour();
    int g = time.minute()*2;
    int b = time.second()*4;
    return QColor::fromRgb(r,g,b);
}

ColorMaker::GenerateAlgorithm ColorMaker::algorithm() const{ return this->m_algorithm;}
void ColorMaker::setAlgorithm(GenerateAlgorithm algorithm){ this->m_algorithm = algorithm; }

void ColorMaker::start()
{
    //使用一个周期为1000ms的定时器来产生颜色，定时器触发时根据算法来构造新的颜色值
    if( 0==this->m_colorTimer )
    {
        this->m_colorTimer = startTimer(1000);
    }
}
void ColorMaker::stop()
{
    if( this->m_colorTimer > 0)
    {
        killTimer(this->m_colorTimer);
        this->m_colorTimer = 0;
    }
}

void ColorMaker::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == this->m_colorTimer)
    {
        switch (this->m_algorithm)
        {
        case  GenerateAlgorithm::RANDOM_RGB:
            this->m_currentColor.setRgb(
                        qrand()%255,
                        qrand()%255,
                        qrand()%255);
            break;
        case  GenerateAlgorithm::RANDOM_RED:
            this->m_currentColor.setRed(qrand()%255);
            break;
        case GenerateAlgorithm::RANDOM_GREEN:
            this->m_currentColor.setGreen(qrand()%255);
            break;
        case GenerateAlgorithm::RANDOM_BLUE:
            this->m_currentColor.setBlue(qrand()%255);
            break;
        case GenerateAlgorithm::LINEAR_INCREASE:
        {
            int r = this->m_currentColor.red() + 10;
            int g = this->m_currentColor.green() + 10;
            int b = this->m_currentColor.blue() + 10;
            this->m_currentColor.setRgb( r%255, g%255, b%255 );
        }
            break;
        default:
            break;
        }
        emit colorChanged(this->m_currentColor);
        emit currentTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    else
    {
        QObject::timerEvent(e);
    }
}
