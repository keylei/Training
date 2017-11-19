#include "fileinfo.hpp"

using namespace SSDK::Archive;
using namespace std;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

FileInfo::FileInfo(const std::string& srcPath) :
    m_qFileinfo(srcPath.data())
{
}
FileInfo::FileInfo(const QString& srcPath) :
    m_qFileinfo(srcPath)
{
}

FileInfo::FileInfo(const FileInfo &fileInfo)
{
    m_childrenFileInfo = fileInfo.m_childrenFileInfo;
    m_qFileinfo = fileInfo.m_qFileinfo;
}
FileInfo::FileInfo(FileInfo &&fileInfo)
{
    m_childrenFileInfo = std::move(fileInfo.m_childrenFileInfo);
    m_qFileinfo = std::move(fileInfo.m_qFileinfo);
}

FileInfo::~FileInfo()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//operator override functions

FileInfo &FileInfo::operator =(const FileInfo &fileInfo)
{
    if(this != &fileInfo)
    {
        m_childrenFileInfo = fileInfo.m_childrenFileInfo;
        m_qFileinfo = fileInfo.m_qFileinfo;
    }
    return *this;
}

FileInfo &FileInfo::operator =(FileInfo &&fileInfo)
{
    m_childrenFileInfo = std::move(fileInfo.m_childrenFileInfo);
    m_qFileinfo = std::move(fileInfo.m_qFileinfo);
    return *this;
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//get file information functions

FileInfo::FileInfoType FileInfo::fileInfoType() const
{
    try
    {
        if(!exists())
        {
            return ILLEGAL;
        }
        //判断是否是文件，如果是输出File
        else if( m_qFileinfo.isSymLink())
        {
            return SYMLINK;
        }
        //判断是否是目录，如果是输出Directory
        else if(m_qFileinfo.isDir())
        {
            return DIRECTORY;
        }
        else if(m_qFileinfo.isFile() )
        {
            return FILE;
        }
        else
        {
            THROW_EXCEPTION_WITH_OBJ(std::string("Unknown type !"));
        }
    }
    CATCH_THROW_EXCEPTION_WITH_OBJ(std::string("Failed to get file information! Frome ")+this->path().toStdString());
}
FileInfo::FileInfoType FileInfo::fileInfoType(const string &srcPath)
{
        if(!exists(srcPath))
        {
            return ILLEGAL;
        }
        QFileInfo fileInfo(QString::fromStdString(srcPath));
        //判断是否是文件，如果是输出File
        if( fileInfo.isSymLink())
        {
            return SYMLINK;
        }
        //判断是否是目录，如果是输出Directory
        else if(fileInfo.isDir())
        {
            return DIRECTORY;
        }
        else if(fileInfo.isFile() )
        {
            return FILE;
        }
        else
        {
            return ILLEGAL;
        }
}
FileInfo::FileInfoType FileInfo::fileInfoType(const QString &srcPath)
{
        if(!exists(srcPath))
        {
            return ILLEGAL;
        }
        QFileInfo fileInfo(srcPath);
        //判断是否是文件，如果是输出File
        if( fileInfo.isSymLink())
        {
            return SYMLINK;
        }
        //判断是否是目录，如果是输出Directory
        else if(fileInfo.isDir())
        {
            return DIRECTORY;
        }
        else if(fileInfo.isFile() )
        {
            return FILE;
        }
        else
        {
              return ILLEGAL;
        }
}

bool FileInfo::exists(const string &srcPath)
{
    QFileInfo fileInfo(QString::fromStdString(srcPath));
    return fileInfo.exists();
}
bool FileInfo::exists(const QString &srcPath)
{
    QFileInfo fileInfo(srcPath);
    return fileInfo.exists();
}
bool FileInfo::exists() const
{
    return m_qFileinfo.exists();
}

bool FileInfo::isUsed(const string &srcPath)
{
    FileInfo fileInfo(srcPath);
    if(FILE == fileInfo.fileInfoType() || SYMLINK == fileInfo.fileInfoType())
    {
        QFile qfile(QString::fromStdString(srcPath));

        if(!qfile.open(QIODevice::ReadOnly))
        {
            return true;
        }
        else
        {
            qfile.close();
            return false;
        }
    }
    return false;
}
bool FileInfo::isUsed(const QString &srcPath)
{
    FileInfo fileInfo(srcPath);
    if(FILE == fileInfo.fileInfoType() || SYMLINK == fileInfo.fileInfoType())
    {
        QFile qfile(srcPath);

        if(!qfile.open(QIODevice::ReadOnly))
        {
            return true;
        }
        else
        {
            qfile.close();
            return false;
        }
    }
    return false;
}
bool FileInfo::isUsed() const
{
    if(FILE == fileInfoType() || SYMLINK == fileInfoType())
    {
        QFile qfile(this->path());

        if(!qfile.open(QIODevice::ReadOnly))
        {
            return true;
        }
        else
        {
            qfile.close();
            return false;
        }
    }
    return false;
}

const QString FileInfo::path() const
{
    if(ILLEGAL != fileInfoType())
    {
        return this->m_qFileinfo.filePath();
    }
    else
    {
        QString srcPath = QDir::toNativeSeparators(m_qFileinfo.filePath());
        if (srcPath.endsWith(QDir::separator()))
        {
            QString newPath = srcPath.left(srcPath.lastIndexOf('/'));
            if(FileInfo::exists(newPath))
            {
                return newPath;
            }
            return "";
        }
        return "";
    }
}

const QString FileInfo::getParentPath() const
{
    if(FILE == fileInfoType() || SYMLINK == fileInfoType())
    {
        return m_qFileinfo.path();
    }
    else if(DIRECTORY == fileInfoType() )
    {
        //判断路径知否是'\'，转换为'/',支持windows
        QString srcPath = QDir::toNativeSeparators(this->path());
        QDir dir(srcPath);
        QDir upDir(srcPath);
        //获得上级目录
        upDir.cdUp();
        if(dir.isAbsolute())
        {
            //返回绝对路径不带'/'
            return upDir.path();
        }
        if(dir.isRelative())
        {
            //返回不带'/'的上级目录
            return getRelativePath(upDir.path().toStdString());
        }
    }

    else
    {
        //判断路径知否是'\'，转换为'/',支持windows
        QString srcPath = QDir::toNativeSeparators(m_qFileinfo.filePath());
        if (srcPath.endsWith(QDir::separator()))
        {
            QString newPath = srcPath.left(srcPath.lastIndexOf('/'));
            QString dstPath = newPath.left(newPath.lastIndexOf('/'));
            return dstPath;
        }
        else
        {
            QString dstPath = srcPath.left(srcPath.lastIndexOf('/'));
            return dstPath;
        }
        return "";
    }
}
const QString FileInfo::getNameWithExtension() const
{
    if(FILE == fileInfoType() || SYMLINK == fileInfoType())
    {
        return m_qFileinfo.fileName();
    }
    else
    {
        return "";
    }
}
const QString FileInfo::getNameWithoutExtension() const
{
    if(FILE == fileInfoType() || SYMLINK == fileInfoType())
    {
        return m_qFileinfo.baseName();
    }
    else
    {
        return "";
    }
}

const QString FileInfo::getAbsolutePath(const std::string &srcPath)
{
    QString srcPathQstr = QString::fromStdString(srcPath);
    QDir directory(srcPathQstr);
    return directory.absolutePath();
}
const QString FileInfo::getAbsolutePath(const QString &srcPath)
{
    QDir directory(srcPath);
    return directory.absolutePath();
}

const QString FileInfo::getRelativePath(const std::string &srcPath)
{
    QString srcPathQstr = QString::fromStdString(srcPath);
    QDir directory(srcPathQstr);
    if(directory.isRelative())
    {
        return QString::fromStdString(srcPath);
    }
    QDir newDirectory(QDir::currentPath());
    return newDirectory.relativeFilePath(srcPathQstr);
}
const QString FileInfo::getRelativePath(const QString &srcPath)
{
    QDir directory(srcPath);
    if(directory.isRelative())
    {
        return srcPath;
    }
    QDir newDirectory(QDir::currentPath());
    return newDirectory.relativeFilePath(srcPath);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//traverse children fileinfo functions

const std::vector<FileInfo>& FileInfo::getChildren()
{
    if(DIRECTORY == fileInfoType())
    {
        setFileList(this->path());
    }
    else
    {
        this->m_childrenFileInfo.clear();
    }

    return this->m_childrenFileInfo;
}
const std::vector<FileInfo> FileInfo::getChildrenRecursively()
{
    this->m_childrenFileInfo.clear();
    if(DIRECTORY == fileInfoType())
    {
        QString srcPath = this->path();
        setFileList(this->path());
        for (int unsigned i = 0; i<m_childrenFileInfo.size(); ++i)
        {
            if(DIRECTORY == m_childrenFileInfo.at(i).fileInfoType())
            {
                m_childrenFileInfo.at(i).m_childrenFileInfo =m_childrenFileInfo.at(i).getChildrenRecursively();
            }
        }
        QFileInfoList fileInfoList = getFileListRescursively(srcPath);
        std::vector<FileInfo> allChildrenFilInfo;
        for(int j = 0; j<fileInfoList.size();++j)
        {
            auto filePath = fileInfoList.at(j).filePath();
            allChildrenFilInfo.push_back(FileInfo(filePath));
        }
        return allChildrenFilInfo;
    }
    else
    {
        this->m_childrenFileInfo.clear();
    }
    return this->m_childrenFileInfo;
}

QFileInfoList FileInfo::getFileListRescursively(QString &srcPath)
{
    QDir dir(srcPath);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Hidden);
    QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folderList.size(); i++)
    {
        QString filePath = folderList.at(i).filePath();
        QFileInfoList childFileList = getFileListRescursively(filePath);
        if(childFileList.empty())
        {
            QFileInfo fileInfo(filePath);
            fileList.append(fileInfo);
        }
        fileList.append(childFileList);
    }
    return fileList;
}

void FileInfo::setFileList(const QString &srcPath)
{
    m_childrenFileInfo.clear();

    QDir dir(srcPath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::Dirs | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list  = dir.entryInfoList();
    for (int i = 0; i<list.size(); ++i)
    {
        QFileInfo qFileInfo = list.at(i);
        m_childrenFileInfo.emplace_back(FileInfo( qFileInfo.filePath()));
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// operation functions

bool FileInfo::remove() const
{
    if(!exists())
        return false;
    //判断是否是目录,是目录删除
    if( DIRECTORY == fileInfoType())
    {
        //toNativeSeparators是支持windows和linux路径静态函数，使windows路径也被支持
        QString srcPath = QDir::toNativeSeparators(this->path());
        //判断路径末尾是否是以'/'结尾，如果不是会加上'/'，windows同样如此
        if (!srcPath.endsWith(QDir::separator()))
            srcPath += QDir::separator();
        QDir directory(srcPath);
        return directory.removeRecursively();
    }
    else
    {
        return QFile::remove(this->path());
    }
}

bool FileInfo::copyTo(std::string destDir, bool isCover)
{
    //判断源路径与目标路径是否相同，如果相同不需要复制
    if(this->path().toStdString() == destDir)
    {
        return true;
    }
    if(FILE == fileInfoType() || SYMLINK == fileInfoType())
    {
        //复制文件
        return copyFileTo(QString::fromStdString(destDir),isCover);
    }
    if(DIRECTORY == fileInfoType())
    {
        //复制目录
        return copyDirTo(this->path(),QString::fromStdString(destDir), isCover);
    }
    else if(ILLEGAL == fileInfoType())
    {
        return false;
    }
    return false;
}
bool FileInfo::copyFileTo(const QString &destPath, bool isCover) const
{
    //判断目标路径是否正确，如果不正确抛出异常
    if(ILLEGAL == fileInfoType())
    {
        THROW_EXCEPTION_WITH_OBJ(std::string("The dest path is illegal!"));
        return false;
    }
    QString dstPath = QDir::toNativeSeparators(destPath);
    if (!dstPath.endsWith(QDir::separator()))
        dstPath += QDir::separator();
    //判断是否被覆盖，如果true删除
    if(isCover&&QFile::exists(dstPath+m_qFileinfo.fileName()))
    {
        if(!QFile::remove(dstPath+m_qFileinfo.fileName()))
        {
            return false;
        }
    }
    //拷贝不成功返回false
    if(!QFile::copy(this->path(),dstPath+m_qFileinfo.fileName()))
    {
        return false;
    }
    return true;
}
bool FileInfo::copyDirTo(const QString &srcDirPath,const QString &destDirPath,bool isCover) const
{
    QDir directory(srcDirPath);
    QString srcPath = QDir::toNativeSeparators(srcDirPath);
    if (!srcPath.endsWith(QDir::separator()))
        srcPath += QDir::separator();
    QString dstPath = QDir::toNativeSeparators(destDirPath);
    if (!dstPath.endsWith(QDir::separator()))
        dstPath += QDir::separator();
    //将源目录名称添加到目标目录路径后
    dstPath+=directory.dirName();
    if (!dstPath.endsWith(QDir::separator()))
        dstPath += QDir::separator();
    bool error = false;
    QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    for (QStringList::size_type i=0; i != fileNames.size(); ++i)
    {
        QString fileName = fileNames.at(i);
        QString srcFilePath = srcPath + fileName;
        QString dstFilePath = dstPath + fileName;
        QFileInfo fileInfo(srcFilePath);
        if (fileInfo.isFile() || fileInfo.isSymLink())
        {
            if (isCover)
            {
                QFile::remove(dstFilePath);
            }
            QFile::copy(srcFilePath, dstFilePath);
        }
        else if (fileInfo.isDir())
        {
            QDir dstDir(dstFilePath);
            QString absolutePath = dstDir.absolutePath();
            dstDir.mkpath(absolutePath);
            dstDir.cdUp();
            if (!copyDirTo(srcFilePath, dstDir.absolutePath(), isCover))
            {
                error = true;
            }
        }
    }
    return !error;
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------




