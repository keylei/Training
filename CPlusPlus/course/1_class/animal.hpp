#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>

class Animal
{
public:
    Animal();
    Animal(int age);


    void sleep();
    void run();

    int legs() const{ return m_legs;}
    void setLegs(int legs){m_legs = legs;}

private:
    int m_legs{4};
};

#endif // ANIMAL_HPP
