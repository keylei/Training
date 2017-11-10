#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "circle.hpp"

class Ellipse: public Circle
{
public:
    Ellipse(double axis);
    Ellipse(double longAxis, double shortAxis);

    virtual void calcArea() override;

private:
    double m_longAxis{0.0};
    double m_shortAxis{0.0};
};

#endif // ELLIPSE_HPP
