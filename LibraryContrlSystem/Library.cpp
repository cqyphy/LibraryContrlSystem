#include "Library.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
void Library::add_user(string type, string userID, string Name) {
    User* user = nullptr;
    if (type == "学生") user = new Student(userID, Name);
    else  user = new Teacher(userID, Name);
    userlist.push_back(user);
}

void Library::add_book(string type, string isbn, string book_name, string auther, string publishing_h, string publishing_t, int inventory)
{
    Book* book = nullptr;
    if (type == "electronic")
    {
        double size;
        string format;
        cout << "please input size,format" << endl;
        cin >> size >> format;
        book = new EBook(isbn, book_name, auther, publishing_h, publishing_t, inventory, size, format);
    }
    else
    {
        book = new Book(isbn, book_name, auther, publishing_h, publishing_t, inventory);
    }
    booklist.push_back(book);
}

void Library::remove_book(const string& ISBN)
{
    for (int i = 0; i < booklist.size(); i++)
    {
        if (ISBN == booklist[i]->getISBN())
        {
            delete booklist[i];
            booklist.erase(booklist.begin() + i);
            cout << "Book removed successfully." << endl;
            return;
        }

    }
    cout << "Can't find the book." << endl;
}

Book* Library::searchbooksByisbn(const string& ISBN)
{


    for (int i = 0; i < booklist.size(); i++)
    {
        if (ISBN == booklist[i]->getISBN())
        {
            //booklist[i]->show();
            return booklist[i];

        }
    }
    cout << "Can't find the book." << endl;
    return nullptr;

}

Book* Library::searchbooksByname(const string& name)
{
    for (int i = 0; i < booklist.size(); i++)
    {
        if (name == booklist[i]->getbookName())
        {
            return booklist[i];
        }
    }
    cout << "Can't find the book." << endl;
    return nullptr;
}

void Library::showall()
{
    cout << "There are " << booklist.size() << " books in this library:" << endl;
    for (int i = 0; i < booklist.size(); i++)
    {
        booklist[i]->show();
    }
    cout << "------------------------------------------------" << endl
        << "Users list:" << endl;
    for (int i = 0; i < userlist.size(); i++)
    {
        userlist[i]->showuserinformation();
    }

}

User* Library::searchuserbyID(const string& ID)
{
    for (int i = 0; i < userlist.size(); i++)
    {
        if (userlist[i]->getID() == ID)
        {
            return userlist[i];
        }
    }
    cout << "User not found" << endl;
    return nullptr;
}

//----------------------------------------------------文件写入----------------------------------------------------
//--------------------------------------写入书本-----------------------------------------------
void Library::savebooks()
{
    ofstream out;
    out.open("books.txt", ios::out);
    if (!out.is_open())
    {
        cout << "Can't open the file" << endl;
    }
    else
    {
        for (int i = 0; i < booklist.size(); i++)
        {
            out << booklist[i]->getISBN() << "|"
                << booklist[i]->getbookName() << "|"
                << booklist[i]->getAuther() << "|"
                << booklist[i]->getPublishingHouse() << "|"
                << booklist[i]->getPublishingTime() << "|"
                << booklist[i]->getinventorystr() << "|";
            EBook* eb = dynamic_cast<EBook*>(booklist[i]);
            if (eb)
            {
                out << "electronic|" << eb->getFileSize() << "|" << eb->getFormat() << "|";
            }
            else
            {
                out << "normal|0|";
            }
            out << endl;
        }
    }


    out.close();
}
//----------------------------------------写入用户----------------------------------------------
void Library::saveusers()
{
    ofstream out;
    out.open("User.txt", ios::out);
    if (!out.is_open())
    {
        cout << "Can't open the file" << endl;
    }
    else
    {
        for (int i = 0; i < userlist.size(); i++)
        {
            out << userlist[i]->getID() << "|"
                << userlist[i]->getname() << "|"
                << userlist[i]->gettype() << "|"
                << userlist[i]->getborrowedbookisbn() << "|" << endl;
        }
    }
    out.close();
}

//-----------------------------------------------------------------文件读取-----------------------------------------------------------------
//-------------------------------------读取书本-------------------------------------------------
void Library::readbooklist()
{
    ifstream in;
    in.open("books.txt");
    if (!in.is_open())
    {
        cout << "Can't open the file" << endl;
        return;
    }
    string str;
    for (int i = 0; std::getline(in, str); i++)
    {

        stringstream ss(str);
        string isbn, name, auther, Publishing_house, Publishing_time, inventorystr, type;
        std::getline(ss, isbn, '|');
        std::getline(ss, name, '|');
        std::getline(ss, auther, '|');
        std::getline(ss, Publishing_house, '|');
        std::getline(ss, Publishing_time, '|');
        std::getline(ss, inventorystr, '|');
        std::getline(ss, type, '|');
        int inventory = stoi(inventorystr);
        Book* book = nullptr;
        if (type == "nomal")book = new Book(isbn, name, auther, Publishing_house, Publishing_time, inventory);        
        if (type == "electronic")
        {
            string sizestr, format;
            std::getline(ss, sizestr, '|');
            std::getline(ss, format, '|');
            double size = stod(sizestr);
            book = new EBook(isbn, name, auther, Publishing_house, Publishing_time, inventory, size, format);
        }
        booklist.push_back(book);
    }

    in.close();
}

//-------------------------------------读取用户-------------------------------------------------
void Library::readuserlist()
{
    ifstream in;
    in.open("User.txt");
    if (!in.is_open())
    {
        cout << "Can't open the file" << endl;
        return;
    }
    string str;
    for (int i = 0; std::getline(in, str); i++)
    {
        stringstream ss(str);
        string id, name, type, borrowedbookisbn;
        std::getline(ss, id, '|');
        std::getline(ss, name, '|');
        std::getline(ss, type, '|');

        User* user = nullptr;
        if (type == "student")
        {
            user = new Student(id, name);
            vector<Book*> books;
            for (int i = 0; i < 3; i++)
            {
                std::getline(ss, borrowedbookisbn, '|');
                if (borrowedbookisbn != " ")
                {
                    Book* book = searchbooksByisbn(borrowedbookisbn);
                    books.push_back(book);
                }
            }
            user->borrowedbooks_fromfile(books);
        }
        if (type == "teacher")
        {
            user = new Teacher(id, name);
            vector<Book*> books;
            for (int i = 0; i < 5; i++)
            {
                std::getline(ss, borrowedbookisbn, '|');
                if (borrowedbookisbn != " ")
                {
                    Book* book = searchbooksByisbn(borrowedbookisbn);
                    books.push_back(book);
                }
            }
            user->borrowedbooks_fromfile(books);
        }
        if (user) userlist.push_back(user);
    }

}