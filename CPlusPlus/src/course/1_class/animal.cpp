#include "animal.hpp"

using namespace std;

Animal::Animal()
{
    cout<<"Base default constructor"<<endl;
}

Animal::Animal(int age)
{
    this->m_age = age;
    cout<<"Base parameterized constructor"<<endl;
}

Animal::~Animal()
{
    cout<<"Base destruct..."<<endl;
}

void Animal::sleep()
{

}

void Animal::run()
{
    cout<<"Animal running..."<<endl;
}
