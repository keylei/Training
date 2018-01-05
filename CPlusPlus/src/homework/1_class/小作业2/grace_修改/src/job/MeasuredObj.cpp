#include "MeasuredObj.hpp"


using namespace Job;
using namespace SSDK;
using namespace std;


MeasuredObj::MeasuredObj()
{

}

MeasuredObj::MeasuredObj(Shape *pBody, string objName)
{
    setPBody(pBody);
    setName(objName);
}


MeasuredObj::~MeasuredObj()
{
    if(nullptr != this->m_pBody)
    {
        delete this->m_pBody;
        this->m_pBody = nullptr;
    }
}
