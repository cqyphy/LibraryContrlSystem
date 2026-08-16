#pragma once
#include "Book.h"
class EBook :
    virtual public Book
{
    private:
        double FileSize;
        std::string Format;
    public:
        EBook(std::string isbn, std::string book_name, std::string auther, std::string publishing_h, std::string publishing_t, int inventory, double size, std::string format) :
            Book(isbn, book_name, auther, publishing_h, publishing_t, inventory), FileSize(size), Format(format) {};
        ~EBook() = default;
        void show();
        //-----------------getters---------------------
        double getFileSize() { return FileSize; };
        std::string getFormat() { return Format; };
};

