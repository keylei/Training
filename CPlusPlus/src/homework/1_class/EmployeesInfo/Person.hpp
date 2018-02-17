#ifndef  PERSION_HPP
#define PERSION_HPP

#include <string>

#include "Inoncopyable.hpp"

/**
 *  @brief comment
 *
 *  @author rime
 *  @version 1.00 2017-12-20 rime
 *                note:create it
*/
class Person/*: private INonCopyable*/
{
public:

    //>>>-----------------------------------------------------------------------------------------------------------------
    //enum

    enum class SexType
    {
        FEMALE,
        MALE
    };


    //<<<-----------------------------------------------------------------------------------------------------------------

    //>>>-----------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    Person();
    virtual ~Person();

    //<<<-----------------------------------------------------------------------------------------------------------------

    //>>>-----------------------------------------------------------------------------------------------------------------
    //get & set functions

    //<<<-----------------------------------------------------------------------------------------------------------------


protected:

    int m_id;
    std::string m_name;
    SexType m_sex;

private:

    //>>>-----------------------------------------------------------------------------------------------------------------
    //member variant


    //<<<-----------------------------------------------------------------------------------------------------------------
};
#endif // PERSION_HPP
