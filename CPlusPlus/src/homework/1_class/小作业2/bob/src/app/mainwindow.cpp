#include "mainwindow.hpp"

using namespace std;
using namespace Job;
using namespace App;
using namespace SSDK;
//using namespace SSDK::DB;

MainWindow::MainWindow()
{
    this->m_pMeasuredObj = nullptr;
}

MainWindow::~MainWindow()
{
    delete [] this->m_pMeasuredObj;
    this->m_pMeasuredObj = nullptr;
}

