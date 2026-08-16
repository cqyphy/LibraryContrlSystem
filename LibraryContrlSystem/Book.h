#pragma once
#include <string>
class Book
{
protected:
    std::string ISBN,
        Book_name,
        Auther,
        Publishing_house,
        Publishing_time,
        ID;
    int inventory;
public:
    //Book(std::string isbn, std::string book_name, std::string auther, std::string publishing_h, std::string publishing_t, int inventory) :
        //ISBN(isbn), Book_name(book_name), Auther(auther), Publishing_house(publishing_h), Publishing_time(publishing_t), inventory(inventory) {};
    Book( std::string isbn, std::string book_name, std::string auther, std::string publishing_h, std::string publishing_t, int inventory) :
        ISBN(isbn), Book_name(book_name), Auther(auther), Publishing_house(publishing_h), Publishing_time(publishing_t), inventory(inventory) {};
    virtual ~Book() = default;
    virtual void show();
    virtual bool borrowbook();
    virtual bool returnbook();
    //------------------------------------------------getters------------------------------------------------
    std::string getISBN() { return ISBN; }
    std::string getbookName() { return Book_name; }
    std::string getAuther() { return Auther; }
    std::string getPublishingHouse() { return Publishing_house; }
    std::string getPublishingTime() { return Publishing_time; }
    //virtual std::string getType(){return "Book";}
    std::string getinventorystr() {
        std::string inventorystr = std::to_string(inventory);
        return inventorystr;
    }
};

