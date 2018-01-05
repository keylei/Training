TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    job/Employee.cpp \
    job/Manager.cpp \
    job/Administrator.cpp \
    job/Engineer.cpp \
    job/Department.cpp \
    job/Company.cpp \
    job/Saler.cpp \
    app/Datagenerator.cpp \
    sdk/Customexception.cpp \
    sdk/FormatConvertor.cpp \
    sdk/RandomNumber.cpp

HEADERS += \
    job/Employee.hpp \
    job/Manager.hpp \
    job/Administrator.hpp \
    job/Engineer.hpp \
    job/Department.hpp \
    job/Company.hpp \
    job/Saler.hpp \
    app/Datagenerator.hpp \
    sdk/Customexception.hpp \
    sdk/FormatConvertor.hpp \
    sdk/RandomNumber.hpp
