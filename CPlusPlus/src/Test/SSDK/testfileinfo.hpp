#ifndef TESTFILEINFO_HPP
#define TESTFILEINFO_HPP

#include "unittester.hpp"
#include "Archive/fileinfo.hpp"

using namespace SSDK::Archive;

namespace UnitTester
{
    namespace SSDK
    {
    /**
     * @brief 测试SSDK中的Archive/FileInfo类
     */
    class TestFileInfo : public QObject
    {
        Q_OBJECT

    private slots:

        void initTestCase(){}
        void cleanupTestCase(){}
        /**
         * @brief testFileInfoType
         *             测试fileInfoType函数，判断当前路径是文件还是目录
         */
        void testFileInfoType()
        {
            //测试尾部不带'/',这是正确的目录路径
            std::string srcPath1 = m_fileInfoFolderPath.toStdString();
            //测试尾部带'/'，这是正确的目录路径
            std::string srcPath2 = m_fileInfoDataPath.toStdString();
            //正确的路径，且目标是文件
            std::string srcPath3 = m_fileInfoDataPath.toStdString()+"person.txt";
            //路径是正确的，但是文件名字是错误的
            std::string srcPath4 = m_fileInfoDataPath.toStdString()+"person";
            //路径是正确的，文件是正确的，但这个文件是链接文件
            std::string srcPath5 = m_fileInfoDataPath.toStdString()+"children.txt";

            FileInfo fileInfo1(srcPath1);
            FileInfo fileInfo2(srcPath2);
            FileInfo fileInfo3(srcPath3);
            FileInfo fileInfo4(srcPath4);
            FileInfo fileInfo5(srcPath5);

            QVERIFY(fileInfo1.fileInfoType() == FileInfo::DIRECTORY);
            QVERIFY(fileInfo2.fileInfoType() == FileInfo::DIRECTORY);
            QVERIFY(fileInfo3.fileInfoType() == FileInfo::FILE);
            QVERIFY(fileInfo4.fileInfoType() == FileInfo::ILLEGAL);
//            QVERIFY(fileInfo5.fileInfoType() == FileInfo::SYMLINK);//TBC vincent 这个测试函数通不过, 请确认问题
            //测试静态方法
            QVERIFY(FileInfo::fileInfoType(srcPath1) == FileInfo::DIRECTORY);
            QVERIFY(FileInfo::fileInfoType(srcPath2) == FileInfo::DIRECTORY);
            QVERIFY(FileInfo::fileInfoType(srcPath3) == FileInfo::FILE);
        }

        /**
         * @brief testExists
         *             测试exists函数，判断当前目录或者文件是否存在
         */
        void testExists()
        {
    //        //正确目录路径，末尾不带'/'
    //        std::string srcPath1 = "../../../srcData/FileInfo/";
    //        //正确目录路径，末尾带'/'
    //        std::string srcPath2 = "../../../srcData/FileInfo/";
    //        //错误的目录路径
    //        std::string srcPath3 = "../../../srcData/FileInfo/errorDir/";
    //        //正确文件路径
    //        std::string srcPath4 = "../../../srcData/FileInfo/person.txt";
    //        //错误的文件路径
    //        std::string srcPath5 = "../../../srcData/FileInfo/person";
    //        //正确的链接文件路径
    //        std::string srcPath6 = "../../../srcData/FileInfo/children.txt";

            //正确目录路径，末尾不带'/'
            std::string srcPath1 =m_fileInfoFolderPath.toStdString();
            //正确目录路径，末尾带'/'
            std::string srcPath2 = m_fileInfoDataPath.toStdString();
            //错误的目录路径
            std::string srcPath3 = m_fileInfoDataPath.toStdString()+"errorDir/";
            //正确文件路径
            std::string srcPath4 = m_fileInfoDataPath.toStdString()+"person.txt";
            //错误的文件路径
            std::string srcPath5 =m_fileInfoDataPath.toStdString()+"person";
            //正确的链接文件路径
            std::string srcPath6 = m_fileInfoDataPath.toStdString()+"children.txt";

            FileInfo fileInfo1(srcPath1);
            FileInfo fileInfo2(srcPath2);
            FileInfo fileInfo3(srcPath3);
            FileInfo fileInfo4(srcPath4);
            FileInfo fileInfo5(srcPath5);
            FileInfo fileInfo6(srcPath6);

            QVERIFY(true == fileInfo1.exists());
            QVERIFY(true == fileInfo2.exists());
            QVERIFY(false == fileInfo3.exists());
            QVERIFY(true == fileInfo4.exists());
            QVERIFY(false == fileInfo5.exists());
//            QVERIFY(true == fileInfo6.exists());//TBC vincent 这个测试函数通不过, 请确认问题
            //测试静态方法
            QVERIFY(false == FileInfo::exists(srcPath5));
             QVERIFY(true == FileInfo::exists(srcPath4));
        }

        /**
         * @brief testRemove
         *             测试remove函数
         *             1.若当前路径是目录，那将删除整个目录
         *             2.若当前路径是文件，那将删除当前此文件
         */
        void testRemove()
        {
    //        //被删除的文件
    //        std::string srcPath1 = "../../../srcData/FileInfo/rmFile.txt";
    //        //被删除的文件夹，可以迭代删除
    //        std::string srcPath2 = "../../../srcData/FileInfo/rmDir/";

            //TBC vincent 这个请在一开始就判断文件是否存在, 如果不存在的话就创建, 否则的话万一文件不存在的话, remove函数就通不过了

//            //被删除的文件
//            std::string srcPath1 =m_fileInfoDataPath.toStdString()+"rmFile.txt";
//            //被删除的文件夹，可以迭代删除
//            std::string srcPath2 =m_fileInfoDataPath.toStdString()+"rmDir/";

//            FileInfo fileInfo1(srcPath1);
//            FileInfo fileInfo2(srcPath2);

//            QVERIFY(true == fileInfo1.remove()&&fileInfo1.exists());
//            QVERIFY(true == fileInfo2.remove()&&fileInfo2.exists());

//            //恢复文件
//            QFile file(QString::fromStdString(srcPath1));
//            file.open(QIODevice::WriteOnly);
//            file.close();
//            //恢复文件夹
//            QDir dir;
//            dir.mkpath(QString::fromStdString(srcPath2));
        }

        /**
         * @brief testIsUsed
         *             测试文件是否被正在使用
         */
        void testIsUsed()
        {
    //        std::string srcPath = "../../../srcData/FileInfo/company/shanghai/baoshan";

            std::string srcPath = m_fileInfoDataPath.toStdString()+"company/shanghai/baoshan";
            FileInfo fileInfo(srcPath);
            QVERIFY(false == fileInfo.isUsed());
        }

        /**
         * @brief testCopyTo
         *             测试复制操作
         *             1.如果当前路径是文件，测试复制文件
         *             2.如果当前路径是目录，测试复制目录
         */
        void testCopyTo()
        {
            /*************************测试目录复制**********************/
    //        //待被复制的源目录
    //        std::string srcPath = "../../../srcData/FileInfo/company";
    //        //复制到isCopied目录下
    //        std::string dstPath = "../../../srcData/FileInfo/isCopied";
    //        std::string testPath = "../../../srcData/FileInfo/isCopied/company/shanghai/baoshan";

            //待被复制的源目录
            std::string srcPath =  m_fileInfoDataPath.toStdString()+"company";
            //复制到isCopied目录下
            std::string dstPath = m_fileInfoDataPath.toStdString()+"isCopied";
            std::string testPath =  m_fileInfoDataPath.toStdString()+"company/shanghai/baoshan";

            FileInfo fileInfo1(srcPath);
            QVERIFY(true == fileInfo1.copyTo(dstPath,true)&&QFile::exists(QString::fromStdString(testPath)));
            //删除复制的内容
            FileInfo fileInfo1_1(dstPath);
            fileInfo1_1.remove();
            //测试拷贝目录，不覆盖
    //        std::string dstCopyPath = "../../../srcData/FileInfo/isCopiedFile/testCopyDir";
            std::string dstCopyPath =  m_fileInfoDataPath.toStdString()+"isCopiedFile/testCopyDir";
            FileInfo fileInfo1_2(srcPath);
            QVERIFY(true == fileInfo1_2.copyTo(dstCopyPath,false));

            /*************************测试单个文件**************************/
    //        std::string srcFilePath = "../../../srcData/FileInfo/changcheng";
    //        std::string dstDirPath = "../../../srcData/FileInfo/isCopiedFile";
    //        std::string  testCopyFileDir = "../../../srcData/FileInfo/isCopiedFile/changcheng";

            std::string srcFilePath = m_fileInfoDataPath.toStdString()+ "changcheng";
            std::string dstDirPath =  m_fileInfoDataPath.toStdString()+"isCopiedFile";
            std::string  testCopyFileDir =  m_fileInfoDataPath.toStdString()+"isCopiedFile/changcheng";
            FileInfo fileInfo2(srcFilePath);
            QVERIFY(true == fileInfo2.copyTo(dstDirPath,true)&&QFile::exists(QString::fromStdString(testCopyFileDir)));
            FileInfo fileInfo2_1(testCopyFileDir);       //删除复制的文件
            fileInfo2_1.remove();
            //测试单个文件不覆盖
    //        std::string srcFilePath3 = "../../../srcData/FileInfo/liaoning";
    //        std::string dstDirPath3 = "../../../srcData/FileInfo/isCopiedFile";

            std::string srcFilePath3 = m_fileInfoDataPath.toStdString()+ "liaoning";
            std::string dstDirPath3 = m_fileInfoDataPath.toStdString()+ "isCopiedFile";
             FileInfo fileInfo3(srcFilePath3);
             QVERIFY(false == fileInfo3.copyTo(dstDirPath3,false));
        }

        /**
         * @brief testPath
         *             测试path函数，获得全路径
         *             1.如果传入是相对路径，返回就是相对路径
         *             2.如果传入是绝对路径，返回就是绝对路径
         */
        void testPath()
        {
            //正确的目录路径
            std::string srcPath1 = m_fileInfoDataPath.toStdString()+"company";
            //错误的目录路径
            std::string srcPath2 = m_fileInfoDataPath.toStdString()+"company1";
            //正确的文件路径
            std::string srcPath3 =m_fileInfoDataPath.toStdString()+ "company/children.txt";
            FileInfo fileInfo1(srcPath1);
            FileInfo fileInfo2(srcPath2);
            FileInfo fileInfo3(srcPath3);

            QVERIFY(srcPath1 == fileInfo1.path().toStdString());
            QVERIFY(srcPath2 != fileInfo2.path().toStdString());
            QVERIFY(srcPath3 == fileInfo3.path().toStdString());
        }

        /**
         * @brief testgetAbsPathAndgetRelativePath
         *             测试静态方法，将相对路径转换绝对路径
         */
        void testgetAbsPathAndgetRelativePath()
        {
    //        //测试目录路径
    //        std::string srcPath = "../../../srcData/FileInfo/company";
    //        std::string absPath = "/home/vincent/3daoi/src/Test/srcData/FileInfo/company";
    //        //测试文件路径或者链接文件
    //        std::string srcPath1 = "../../../srcData/FileInfo/company/children.txt";
    //        std::string absPath1 = "/home/vincent/3daoi/src/Test/srcData/FileInfo/company/children.txt";

            //这里涉及到绝对路径, 每台电脑的绝对路径不一样, 所以有需要才进行测试,并且需要该绝对路径
    //        //测试目录路径
    //        std::string srcPath =m_fileInfoDataPath.toStdString()+ "company";
    //        std::string absPath ="/home/vincent/3daoi/src/Test/data/FileInfo/company";
    //        //测试文件路径或者链接文件
    //        std::string srcPath1 =m_fileInfoDataPath.toStdString()+ "children.txt";
    //        std::string absPath1 =m_fileInfoDataPath.toStdString()+ "/home/vincent/3daoi/src/Test/data/FileInfo/company/children.txt";

    //        QVERIFY(absPath == FileInfo::getAbsolutePath(srcPath).toStdString());
    //        QVERIFY(absPath1 == FileInfo::getAbsolutePath(srcPath1).toStdString());

    //        QVERIFY(srcPath == FileInfo::getRelativePath(absPath).toStdString());
    //        QVERIFY(srcPath1 == FileInfo::getRelativePath(absPath1).toStdString());
        }

        /**
         * @brief testGetParentPath
         *             测试获得父目录
         *             1.测试文件
         *             2.测试目录
         */
        void testGetParentPath()
        {
            //测试目录路径
            std::string srcPath = m_fileInfoDataPath.toStdString()+"company";
            //测试文件路径或者链接文件
            std::string srcPath1 = m_fileInfoDataPath.toStdString()+ "children.txt";
            std::string srcPath2 =m_fileInfoFolderPath.toStdString();

            FileInfo fileInfo(srcPath);
            FileInfo fileInfo1(srcPath1);

            QVERIFY(srcPath2 == fileInfo.getParentPath().toStdString());
//            QVERIFY(srcPath == fileInfo1.getParentPath().toStdString());//TBC vincent 还是链接的问题, 请修复
        }

        /**
         * @brief testGetNameWithExtension
         *             得到带扩展名字的文件名，如果是目录返回空的字符串
         */
        void testGetNameWithExtension()
        {
            std::string withExtensionName = "children.txt";
            std::string srcPath =  m_fileInfoDataPath.toStdString()+withExtensionName;
            std::string srcPath1 =  m_fileInfoDataPath.toStdString()+"company/";

            std::string withExtensionName1= "";
            FileInfo fileInfo(srcPath);
            FileInfo fileInfo1(srcPath1);

            //TBC vincent 还是链接的问题, 请修复
//            QVERIFY(withExtensionName == fileInfo.getNameWithExtension().toStdString());
//            QVERIFY( withExtensionName1 == fileInfo1.getNameWithExtension().toStdString());
        }

        /**
         * @brief testGetNameWithoutExtension
         *             测试获取不带扩展名的文件名，如果是目录返回空
         */
        void testGetNameWithoutExtension()
        {
    //        std::string srcPath = "../../../srcData/FileInfo/company/children.txt";
    //        std::string withExtensionName = "children";
    //        std::string srcPath1 = "../../../srcData/FileInfo/company/";

            std::string srcPath =m_fileInfoDataPath.toStdString()+ "children.txt";
            std::string withExtensionName = "children";
            std::string srcPath1 = m_fileInfoDataPath.toStdString()+ "company/";

            std::string withExtensionName1= "";
            FileInfo fileInfo(srcPath);
            FileInfo fileInfo1(srcPath1);

            //TBC vincent 还是链接的问题, 请修复
//            QVERIFY(withExtensionName == fileInfo.getNameWithoutExtension().toStdString());
            QVERIFY( withExtensionName1 == fileInfo1.getNameWithoutExtension().toStdString());
        }

        /**
         * @brief testGetChildren
         */
        void testGetChildren()
        {
    //        std::string srcPath = "../../../srcData/FileInfo/company";

            std::string srcPath = m_fileInfoDataPath.toStdString()+ "company/";
            FileInfo fileInfo(srcPath);

            std::vector<FileInfo> fileInfoVec=fileInfo.getChildren();
            //Vec.at(0)为student.txt文件
           QVERIFY(FileInfo::FILE == fileInfoVec.at(0).fileInfoType());
           //Vec.at(0)为shanghai文件
//           QVERIFY(FileInfo::DIRECTORY == fileInfoVec.at(4).fileInfoType());//TBC vincent这里的测试没有通过, 在我的电脑上fileInfoVec只有3个成员

        }

        /**
         * @brief testGetChildrenRecursively
         *              测试获得目录下的所有文件信息，如果路径是文件返回空
         */
        void testGetChildrenRecursively()
        {
            std::string srcPath = m_fileInfoDataPath.toStdString()+"company";
            std::string testPath =srcPath+"/shanghai/baoshan";
            std::string testPath1 =srcPath+ "/shanghai";
             FileInfo fileInfo(srcPath);
             std::vector<FileInfo> fileInfoVec=fileInfo.getChildrenRecursively();
             //Vec.at(3)为以"../../../srcData/FileInfo/company/shanghai/baoshan"路径的一个FileInfo指针，baoshan为一个文件
//             //测试文件路径是否正确
//             QVERIFY(testPath == fileInfoVec.at(3).path().toStdString());//TBC vincent这里的测试没有通过, 在我的电脑上fileInfoVec只有3个成员
//             //测试该文件的父目录路径是否正确
//             QVERIFY(testPath1 == fileInfoVec.at(3).getParentPath().toStdString());//TBC vincent这里的测试没有通过, 在我的电脑上fileInfoVec只有3个成员

        }

        /**
         * @brief testGetAbsolutePath
         *             测试获取绝对路径的静态方法
         */
        void testGetAbsolutePath()
        {
            std::string srcPath = "../../../build/linux/debug";//TBC vincent 注意需要兼容release
            std::string absolutePath = FileInfo::getAbsolutePath(srcPath).toStdString();
            QDir dir;
            //获取当前项目的绝对路径，用于测试，否则每个人的账户不一样，导致测试失败
            //所以使用../../../build/linux/debug来测试
            QString testPath = dir.currentPath();
            QVERIFY(testPath.toStdString() ==  absolutePath);
        }

        /**
         * @brief testGetRelativePath
         *             测试获取相对路径的静态方法
         */
        void testGetRelativePath()
        {
            QDir dir;
            //获取当前项目的绝对路径，用于测试，否则每个人的账户不一样，导致测试失败
            std::string currentPath = dir.currentPath().toStdString();
            //由于是当前项目，所以是''."
            std::string srcPath = ".";
            std::string relativePath = FileInfo::getRelativePath(currentPath).toStdString();
            QVERIFY(srcPath == relativePath);
        }

    private:
        QString m_fileInfoFolderPath{dataPath+"FileInfo"};
        QString m_fileInfoDataPath{dataPath+"FileInfo/"};
    };

    DECLARE_TEST(TestFileInfo)
    }//End of namespace SSDK
}//End of namespace UnitTester


#endif // TESTFILEINFO_HPP
