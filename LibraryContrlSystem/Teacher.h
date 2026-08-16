#pragma once
#include "User.h"
class Teacher :
    virtual public User
{
private:
    /* data */
public:
    Teacher(std::string userid, std::string name) :User(userid, name)
    {
        type = "teacher";
        Max_Borrow_Limit = 5;

    };
    ~Teacher() = default;
    void borrow(Book* book);
};

