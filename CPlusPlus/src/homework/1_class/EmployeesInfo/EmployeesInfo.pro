TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Employee.cpp \
    Engineer.cpp \
    Administrator.cpp \
    Company.cpp \
    Department.cpp \
    Person.cpp \
    Salesman.cpp \
    manager.cpp

HEADERS += \
    Employee.hpp \
    Engineer.hpp \
    Administrator.hpp \
    Manager.hpp \
    Manager.hpp \
    Company.hpp \
    Department.hpp \
    Person.hpp \
    Inonassignable.hpp \
    Inoncopyable.hpp \
    Salesman.hpp
