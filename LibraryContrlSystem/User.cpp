#include "User.h"
#include <iostream>
void User::borrowedbooks_fromfile(std::vector<Book*> v1)
{
    borrowedbooks = v1;
}

void User::showborrowedbooks()
{
    for (int i = 0; i < borrowedbooks.size(); i++)
    {
        std::cout << "book" << i + 1 << ":" << std::endl;
        borrowedbooks[i]->show();
    }

}

void User::showuserinformation()
{
    std::cout << "userID\t" << "Name\t" << "Borrowed Books\t" << std::endl
        << userID << "\t" << Name << "\t" << borrowedbooks.size() << "\t" << std::endl << std::endl;
}

void User::returnbook(Book* book)
{
    std::string temp = book->getISBN();
    for (int i = 0; i < borrowedbooks.size(); i++)
    {
        if (borrowedbooks[i]->getISBN() == temp)
        {
            borrowedbooks.erase(borrowedbooks.begin() + i);
            book->returnbook();
            break;
        }

    }

}

std::string User::getborrowedbookisbn()
{
    std::string temp;
    int cycletimes;
    if (type == "student")
    {
        cycletimes = 3;
    }
    else if (type == "teacher")
    {
        cycletimes = 5;
    }
    int j = 0;
    for (int i = 0; i < borrowedbooks.size(); i++)
    {
        temp += borrowedbooks[i]->getISBN();
        temp += "|";
        j++;
    }
    for (; j < cycletimes; j++)
    {
        temp += " ";
        temp += "|";
    }


    return temp;
}