#ifndef IBOX_HPP
#define IBOX_HPP

#include <iostream>

class IBox
{
public:
    IBox();

     virtual void calcVolume() = 0;
};

#endif // IBOX_HPP
