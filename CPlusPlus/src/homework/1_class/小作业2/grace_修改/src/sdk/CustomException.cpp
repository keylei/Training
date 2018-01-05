#include "CustomException.hpp"

using namespace std;

using namespace SSDK;


CustomException::CustomException(string &message)
{
    this->m_originMsg = message;
}

CustomException::~CustomException()
{

}
