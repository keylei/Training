#include "VideoElement.hpp"

VideoElement::VideoElement()
{
    //初始化m_roleNames，这里定义了具体的数据结构
    int role = Qt::UserRole;
    m_roleNames.insert(role++, "name");
    m_roleNames.insert(role++, "date");
    m_roleNames.insert(role++, "director_tag");
    m_roleNames.insert(role++, "director");
    m_roleNames.insert(role++, "actor_tag");
    m_roleNames.insert(role++, "actor");
    m_roleNames.insert(role++, "rating_tag");
    m_roleNames.insert(role++, "rating");
    m_roleNames.insert(role++, "desc_tag");
    m_roleNames.insert(role++, "desc");
    m_roleNames.insert(role++, "img");
    m_roleNames.insert(role++, "playpage");
    m_roleNames.insert(role++, "playtimes");
}
VideoElement::~VideoElement()
{
      clear();
}

void VideoElement::load()
{
    //这里为了快速实现举列，舍弃了异常保护部分
    QXmlStreamReader reader;
    QFile file(this->m_xmlFilePath);
    reader.setDevice(&file);
    QStringRef elementName;
    VideoDetailInfo * video;

    if(!file.exists())
    {
        return;
    }
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }

    while(!reader.atEnd())
    {
        reader.readNext();
        if(reader.isStartElement())
        {
            elementName = reader.name();
            if( elementName == "video")
            {
                video = new VideoDetailInfo();
                QXmlStreamAttributes attrs = reader.attributes();
                video->append(attrs.value("name").toString());
                video->append(attrs.value("date").toString());
            }
            else if( elementName == "attr")
            {
                video->append(reader.attributes().value("tag").toString());
                video->append(reader.readElementText());
            }
            else if( elementName == "poster")
            {
                video->append(reader.attributes().value("img").toString());
            }
            else if( elementName == "page" )
            {
                video->append(reader.attributes().value("link").toString());
            }
            else if( elementName == "playtimes" )
            {
                video->append(reader.readElementText());
            }
        }
        else if(reader.isEndElement())
        {
            elementName = reader.name();
            if( elementName == "video")
            {
                m_videos.append(video);
                video = 0;
            }
        }
    }
    file.close();
}
void VideoElement::reset()
{
    clear();
}
void VideoElement::clear()
{
    int count = m_videos.size();
    if(count > 0)
    {
        for(int i = 0; i < count; i++)
        {
            delete m_videos.at(i);
        }
        m_videos.clear();
    }
}
