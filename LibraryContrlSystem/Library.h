#pragma once
#include "Book.h"
#include "EBook.h"
#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include <vector>
class Library
{
    private:
        std::vector<Book*> booklist;
        std::vector<User*> userlist;
    public:
        Library(/* args */) = default;
        ~Library() {
            for (auto p : booklist) delete p;
            for (auto p : userlist) delete p;
        }
        void add_book(std::string type, std::string isbn, std::string book_name, std::string auther, std::string publishing_h, std::string publishing_t, int inventory);
        void add_user(std::string type, std::string userID, std::string Name);
        void remove_book(const std::string& ISBN);
        Book* searchbooksByisbn(const std::string& ISBN);
        Book* searchbooksByname(const std::string& name);
        void showall();
        User* searchuserbyID(const std::string& ID);
        //文件读写功能
        void savebooks();
        void saveusers();
        void readbooklist();
        void readuserlist();
};

