#include "VideoListModel.hpp"

VideoListModel::VideoListModel(QObject *pParent):
    QAbstractListModel(pParent),
    m_pVideoElement(new VideoElement())
{

}

VideoListModel::~VideoListModel()
{
    delete this->m_pVideoElement;
}

int VideoListModel::rowCount(const QModelIndex &parent) const
{
    return m_pVideoElement->m_videos.size();
}
QVariant VideoListModel::data(const QModelIndex &index, int role) const
{
    VideoDetailInfo *pVideoElement = m_pVideoElement->m_videos[index.row()];
    return pVideoElement->at(role - Qt::UserRole);
}
QHash<int, QByteArray> VideoListModel::roleNames() const
{
    return this->m_pVideoElement->m_roleNames;
}

QString VideoListModel::source() const
{
    return m_pVideoElement->m_xmlFilePath;
}
void VideoListModel::setSource(const QString& filePath)
{
    m_pVideoElement->m_xmlFilePath = filePath;
    reload();
}

void VideoListModel::reload()
{
    //beginResetModel和endResetModel是基类的，然后调用自身
    //的重置方法，这两个方法会发射正确的信号来通知关联到Model
    //的view刷新界面
    beginResetModel();

    m_pVideoElement->reset();
    m_pVideoElement->load();

    endResetModel();
}

void VideoListModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    delete m_pVideoElement->m_videos.takeAt(index);
    endRemoveRows();
}
