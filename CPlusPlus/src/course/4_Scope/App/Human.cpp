#include "Human.hpp"


using namespace Mammal;
using namespace std;

namespace
{
void func()
{
    double a = 1.1*2.2-3+4.0/5.0;
}
}

void func1()
{
    double a = 1.1*2.2-3+4.0/5.0;
}

Human::Human()
{
    auto start = std::chrono::steady_clock::now();

    int cnt = 10000000 ;
    for (int i = 0; i < cnt; ++i)
    {
        func1();
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration <double, milli> (end-start).count() <<std::endl;
}
