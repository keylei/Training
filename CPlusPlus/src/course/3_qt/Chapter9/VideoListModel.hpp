#ifndef VIDEOLISTMODEL_HPP
#define VIDEOLISTMODEL_HPP

#include <QObject>
#include <QAbstractListModel>

#include "VideoElement.hpp"

/**
 *  @brief comment
 *
 *  @author author
 *  @version 1.00 2017-12-18 author
 *                note:create it
*/
class VideoListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString source READ source WRITE setSource)

public:

    //>>>-----------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    VideoListModel(QObject *parent = 0);
    virtual ~VideoListModel();

    //<<<-----------------------------------------------------------------------------------------------------------------

    //>>>-----------------------------------------------------------------------------------------------------------------
    //invokable functions

    Q_INVOKABLE void reload();
    Q_INVOKABLE void remove(int index);

    //<<<-----------------------------------------------------------------------------------------------------------------

    //>>>--------------------------------------------------------------------------------------------------------------------
    //member functions

    //rowCount/data/roleNames是虚函数，需要被重写

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    QString source() const;
    void setSource(const QString& filePath);

    //<<<--------------------------------------------------------------------------------------------------------------------

    //>>>-----------------------------------------------------------------------------------------------------------------
    //signals

Q_SIGNALS:

//    void normalObjNameChanged(EnumTypeName enumObjName);

    //<<<-----------------------------------------------------------------------------------------------------------------

private:

    //>>>-----------------------------------------------------------------------------------------------------------------
    //member variants

    VideoElement* m_pVideoElement { nullptr };
    //<<<-----------------------------------------------------------------------------------------------------------------
};


#endif // VIDEOLISTMODEL_HPP
