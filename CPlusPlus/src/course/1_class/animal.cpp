#include "animal.hpp"

using namespace std;

Animal::Animal()
{
    cout<<"Base default constructor"<<endl;
}

Animal::Animal(int age)
{
    cout<<"Base parameterized constructor"<<endl;
}

void Animal::sleep()
{

}

void Animal::run()
{
    cout<<"Animal running..."<<endl;
}
