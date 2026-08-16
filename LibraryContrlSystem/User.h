#pragma once
#include "Book.h"
#include <string>
#include <vector>
class User
{
    protected:
        std::string userID, Name, type;
        int Max_Borrow_Limit;
        std::vector<Book*> borrowedbooks;
    public:
        User(std::string userid, std::string name) :userID(userid), Name(name) {};
        virtual ~User() = default;
        virtual void borrow(Book* book) = 0;//用户类借书动作
        virtual void returnbook(Book* book);
        void showborrowedbooks();
        void showuserinformation();
        void borrowedbooks_fromfile(std::vector<Book*> v1);//用于从文件中提取已借书本
        //-------------getters-----------------
        std::string getID() { return userID; }
        std::string getname() { return Name; }
        std::string gettype() { return type; }
        std::string getborrowedbookisbn();
};

