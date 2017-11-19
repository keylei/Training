#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>

class Student
{
public:
    Student();

    void print() const;
    std::string getName();

private:
    std::string  m_name;
};

#endif // STUDENT_HPP
