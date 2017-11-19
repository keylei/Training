#include <QDebug>

#include "unittester.hpp"

int main()
{
    int failures = UnitTester::run();


    qDebug() << "--------------------------------------------------------------------------------------";
    qDebug() << "SSDK Test";

    if (failures == 0)
    {
      qDebug() << "ALL TESTS PASSED";
    }
    else
    {
      qDebug() << failures << " TESTS FAILED!";
    }

    qDebug() << "--------------------------------------------------------------------------------------";

    return 0;
}
