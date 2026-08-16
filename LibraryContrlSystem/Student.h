#pragma once
#include "User.h"
class Student :
    virtual public User
{
private:
    /* data */
public:
    Student(std::string userid, std::string name) :User(userid, name)
    {
        type = "student";
        Max_Borrow_Limit = 3;

    };
    ~Student() = default;
    void borrow(Book* book);
};

