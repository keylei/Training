#ifndef UNIT_TESTER_HPP
#define UNIT_TESTER_HPP

#include <QObject>
#include <QtTest/QtTest>
#include <QString>
#include <QSharedPointer>

namespace UnitTester
 {

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // test class

        /**
         * @brief TestList
         *              测试列表, 这个List存放的是测试类, 测试的时候会遍历其中的类
         */
        typedef QList<QObject*> TestList;

        /**
          * 测试数据的根目录
          */
        static QString dataPath{"../../../data/"};

        /**
         * @brief 获取到待所有待测试的类的列表，使用局部静态变量，为了更好的封装
         */
        inline TestList& testList()
        {
            static TestList list;
            return list;
        }

        /**
         * @brief 判断指定的对象指针是否已经包含在列表中
         * @param 对象指针
         * @return 如果包含，返回true，否则返回false
         */
        inline bool hasContained(QObject* pObject)
        {
            TestList& list = testList();
            if (list.contains(pObject))
            {
                return true;
            }
            foreach (QObject* test, list)
            {
                if (test->objectName() == pObject->objectName())
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief 将对象指针加入待测试列表
         * @param 对象指针
         */
        inline void addTestedObject(QObject* pObject)
        {
            TestList& list = testList();
            if (!hasContained(pObject))
            {
                list.append(pObject);
            }
        }

        /**
         * @brief 测试所有的类
         * @return 全部成功为0,否则就不为0
         */
        inline int run()
        {
            int ret = 0;

            foreach (QObject* test, testList())
            {
                ret += QTest::qExec(test);
            }

            return ret;
        }

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

}//End of namespace UnitTester

template <class T>
class Test
{
public:
       QSharedPointer<T> child;

       Test(const QString& name) : child(new T)
       {
              child->setObjectName(name);
              UnitTester::addTestedObject(child.data());
       }
};

/**
* 1.生成一个TestedObject<className>的模板类，然后创建对象
* 2.将该对象加入测试
*/
#define DECLARE_TEST(className) static Test<className> t(#className);

 #endif // UNIT_TESTER_HPP


