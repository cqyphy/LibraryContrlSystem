#include "EBook.h"
#include <iostream>
void EBook::show()
{
    std::cout << "ISBN\t" << "Book_name\t" << "Auther\t" << "Publishing_house\t" << "Publishing_time\t" << "File_Size\t" << "Format\t" << "inventory\t" << std::endl
        << ISBN << "\t" << Book_name << "\t" << Auther << "\t" << Publishing_house << "\t" << Publishing_time << "\t" << FileSize << "\t" << Format << "\t" << inventory << "\t" << std::endl << std::endl;
}