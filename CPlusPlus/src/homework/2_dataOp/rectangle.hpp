#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <string>

class Rectangle
{
public:
    Rectangle();

private:
    std::string m_name{"Rect"};
    double m_x{-1};
    double m_y{-1};
    double m_width{-1};
    double m_height{-1};
    double m_angle{-1};
};

#endif // RECTANGLE_HPP
