#include "Book.h"
#include <iostream>
void Book::show()
{
    std::cout << "ISBN\t\t\t" << "Book_name\t" << "Auther\t\t" << "Publishing_house\t" << "Publishing_time\t" << "inventory\t" << std::endl
        << ISBN << "\t" << Book_name << "\t" << Auther << "\t" << Publishing_house << "\t\t" << Publishing_time << "\t\t" << inventory << "\t" << std::endl << std::endl;
}

bool Book::borrowbook()//管理书类的库存
{
    if (inventory == 0)
    {
        std::cout << "Sorry,there is no this book." << std::endl;
        return 0;
    }
    std::cout << "Borrow succesfully." << std::endl;
    inventory--;
    return 1;
}

bool Book::returnbook()
{
    std::cout << "You have successfully return the book." << std::endl;
    inventory++;
    return 1;
}