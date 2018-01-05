#include "Pad.hpp"

using namespace Job;

#include "../sdk/Shape.hpp"

Pad::Pad()
{

}

Pad::Pad(SSDK::IShape *pShape):MeasuredObject(pShape)
{

}

Pad::~Pad()
{

}
