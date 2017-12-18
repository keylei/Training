#ifndef VIDEOLISTMODELPRIVATE_HPP
#define VIDEOLISTMODELPRIVATE_HPP

#include <QXmlStreamReader>
#include <QVector>
#include <QFile>
#include <QDebug>

using VideoDetailInfo = QVector<QString>;

class VideoElement
{
public:
    VideoElement();
    virtual ~VideoElement();

    //加载数据，解析XML文档
    void load();
    //重置所有数据，内部调用了reset
    void reset();
    //清空所有数据
    void clear();

    QString m_xmlFilePath;
    //这是一个哈希表，必须这个哈希表，才能构实现通过字符串取值
    QHash<int, QByteArray> m_roleNames;
    QVector<VideoDetailInfo*> m_videos;
};

#endif // VIDEOLISTMODELPRIVATE_HPP
