#include "Book.h"
#include "EBook.h"
#include "User.h"
#include "Student.h"
#include "Teacher.h"
#include "Library.h"
#include <iostream>
void usermenu(Library* library)
{
    bool is_usermenu_continue = 1;
    std::string ID;
    std::cout << "Please input your ID:" << std::endl;
    std::cin >> ID;
    User* user = library->searchuserbyID(ID);
    while (is_usermenu_continue && user)
    {

        std::cout << "User " << user->getname() << ':' << std::endl
            << "1.borrow books" << std::endl
            << "2.return books" << std::endl
            << "3.show borrowed books" << std::endl
            << "4.exit" << std::endl;
        int funtion_inusermenu;
        std::cin >> funtion_inusermenu;
        switch (funtion_inusermenu)
        {
        case 1:
        {
            std::cout << "input book name:" << std::endl;
            std::string bookname;
            std::cin >> bookname;
            Book* book = library->searchbooksByname(bookname);
            if (book)  user->borrow(book);
            else std::cout << "Book not found." << std::endl;
            break;
        }
        case 2:
        {
            std::cout << "input book name:" << std::endl;
            std::string bookname;
            std::cin >> bookname;
            Book* book = library->searchbooksByname(bookname);
            if (book)  user->returnbook(book);
            else std::cout << "Book not found." << std::endl;
            break;
        }
        case 3:
            user->showborrowedbooks();
            break;
        default:
            is_usermenu_continue = 0;
            break;
        }



    }
}

//-----------------------------------------------------------------管理员菜单-----------------------------------------------------------------
void Administratormenu(Library* library)
{
    bool is_adminmenu_continue = 1;
    while (is_adminmenu_continue)
    {
        std::cout << "input numbers to choose:" << std::endl << std::endl
            << "1.add book" << std::endl
            << "2.remove book" << std::endl
            << "3.search book by ISBN" << std::endl
            << "4.search book by name" << std::endl
            << "5.show informations" << std::endl
            << "6.add user" << std::endl
            << "7.exit" << std::endl;
        int funtion_inadminmenu;
        std::cin >> funtion_inadminmenu;
        switch (funtion_inadminmenu)
        {
        case 1:
        {
            std::cout << "please input type,isbn,book_name,auther,publishing_house,publishing_time,inventory" << std::endl;
            std::string type;
            std::string isbn;
            std::string book_name;
            std::string auther;
            std::string publishing_h;
            std::string publishing_t;
            int inventory;
            std::cin >> type >> isbn >> book_name >> auther >> publishing_h >> publishing_t >> inventory;
            library->add_book(type, isbn, book_name, auther, publishing_h, publishing_t, inventory);
            break;
        }
        case 2:
        {
            std::cout << "please input ISBN" << std::endl;
            std::string isbn;
            std::cin >> isbn;
            library->remove_book(isbn);
            break;
        }
        case 3:
        {
            std::cout << "please input ISBN" << std::endl;
            std::string isbn;
            std::cin >> isbn;
            Book* book = library->searchbooksByisbn(isbn);
            if (book) book->show();
            else std::cout << "Book not found." << std::endl;
            break;
        }
        case 4:
        {
            std::cout << "please input book name" << std::endl;
            std::string name;
            std::cin >> name;
            Book* book = library->searchbooksByname(name);
            if (book) book->show();
            else std::cout << "Book not found." << std::endl;
            break;
        }

        case 5:
            library->showall();
            break;
        case 6:
        {
            std::cout << "please input user type,userID,name" << std::endl;
            std::string type, id, name;
            std::cin >> type >> id >> name;
            library->add_user(type, id, name);
            break;
        }
        default:
            is_adminmenu_continue = 0;
            break;
        }
    }

}

int main()
{
    Library GzhuLibrary;
    GzhuLibrary.readbooklist();
    GzhuLibrary.readuserlist();
    bool is_continue = 1;
    do
    {
        int choosefuntion;
        std::cout << "Welcom to Gzhu library contro pannel,please input numbers to choose funtions:" << std::endl << std::endl
            << "1.User menu" << std::endl
            << "2.Administrator menu" << std::endl
            << "3.exit" << std::endl;
        std::cin >> choosefuntion;
        switch (choosefuntion)
        {
        case  1:
            usermenu(&GzhuLibrary);
            break;
        case 2:
            Administratormenu(&GzhuLibrary);
            break;
        default:
            is_continue = 0;
            break;
        }
    } while (is_continue);
    /*GzhuLibrary.savebooks();
    GzhuLibrary.saveusers();*/

}