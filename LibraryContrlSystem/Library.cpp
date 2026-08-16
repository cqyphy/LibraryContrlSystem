#include "Library.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <mysql.h>
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
    MYSQL* conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "LIBRARY_ADMINISTATER", "123456", "library_contrl_system", 3306, NULL, 0))
    {
        cout << "connect faile" << endl;
    }
    if (type == "electronic")
    {
        double size;
        string format;
        cout << "please input size,format" << endl;
        cin >> size >> format;
        book = new EBook(isbn, book_name, auther, publishing_h, publishing_t, inventory, size, format);
        string insert_sql = "insert into book_list(isbn, book_name, auther, publishing_house, publishing_time, inventory, format,size) values (" + isbn + book_name + auther + publishing_h + publishing_t + to_string(inventory) + to_string(size) + format+")";
        mysql_query(conn, insert_sql.c_str());
    }
    else
    {
        book = new Book(isbn, book_name, auther, publishing_h, publishing_t, inventory);
        string insert_sql = "insert into book_list(isbn, book_name, auther, publishing_house, publishing_time, inventory, format,size) values (" + isbn + book_name + auther + publishing_h + publishing_t + to_string(inventory) + ")";
        mysql_query(conn, insert_sql.c_str());
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
//void Library::savebooks()
//{
//    
//}
////----------------------------------------写入用户----------------------------------------------
//void Library::saveusers()
//{
//    
//}

//-----------------------------------------------------------------文件读取-----------------------------------------------------------------
//-------------------------------------读取书本-------------------------------------------------
void Library::readbooklist()
{
    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn,"localhost","LIBRARY_ADMINISTATER","123456","library_contrl_system",3306,NULL,0))
    {
        cout << "connect faile" << endl;
    }
    mysql_query(conn, "select ISBN,Book_name,Auther,Publishing_house,Publishing_time,INVENTORY from book_list");
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    while ( row = mysql_fetch_row(res))
    {
        Book* book = new Book(row[0],row[1],row[2],row[3],row[4],stoi(row[5]));
        booklist.push_back(book);
    }
    mysql_free_result(res);
    mysql_close(conn);
}

//-------------------------------------读取用户-------------------------------------------------
void Library::readuserlist()
{
    MYSQL* conn = mysql_init(nullptr);
    if (!mysql_real_connect(conn, "localhost", "LIBRARY_ADMINISTATER", "123456", "library_contrl_system", 3306, NULL, 0))
    {
        cout << "connect faile" << endl;
    }
    mysql_query(conn, "select id,name,type from user_list");
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    for (int user_num = 1;row = mysql_fetch_row(res);user_num++)
    {
        User* user;//创建用户
        if (row[2] == "学生") { user = new Student(row[0], row[1]); }
        else { user = new Teacher(row[0], row[1]); }
        //读取用户借书目录
        string view_sql = "SELECT ISBN,Book_name,Auther,Publishing_house,Publishing_time,INVENTORY FROM user_borrowed_books WHERE USER_ID = '" + string(row[0]) + "'";
        mysql_query(conn, view_sql.c_str());
        MYSQL_RES* res1 = mysql_store_result(conn);
        vector<Book*> books;
        MYSQL_ROW row1;
        while (row1 = mysql_fetch_row(res1))
        {
            Book* book = searchbooksByisbn(row1[0]);
            books.push_back(book);
        }
        mysql_free_result(res1);
        user->borrowedbooks_fromfile(books);
        userlist.push_back(user);
    }
    mysql_free_result(res);
    mysql_close(conn);
}