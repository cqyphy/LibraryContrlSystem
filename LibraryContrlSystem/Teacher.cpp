#include "Teacher.h"
#include <iostream>
void Teacher::borrow(Book* book)
{
    if (borrowedbooks.size() == Max_Borrow_Limit)
    {
        std::cout << "You had borrowed 5 books,please return books first." << std::endl;
    }
    if (borrowedbooks.size() < Max_Borrow_Limit)
    {

        if (book->borrowbook())
        {
            borrowedbooks.push_back(book);
        }
    }

}