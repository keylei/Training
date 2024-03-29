#ifndef INONASSIGNABLE_H
#define INONASSIGNABLE_H

/**
         *  @brief
         *      forbid assignment
         *      non-assignable class need inhert it
         *
         *  @author rime
         *  @version 1.00 2017-03-02 rime
         *                note:create it
        */
class INonAssignable
{
protected:
    INonAssignable(){}
    virtual ~INonAssignable(){}

private:
    const INonAssignable & operator = (const INonAssignable&);
};


#endif//INONASSIGNABLE_H
