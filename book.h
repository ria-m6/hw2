#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>
#include <set>


class Book : public Product{
public:
    //constructor and deconstructor
    Book(const std::string& name, const std::string& ISBN, const std::string& Author, double price, int qty);
    ~Book();
    
    //getting keywords from author, book name, and ibsn
    std::set<std::string> keywords() const override;

    //displays the content
    std::string displayString() const override;

    //dumps
    void dump(std::ostream& os) const override;

    std::string getISBN() const;
    std::string getAUTHOR() const; 

private:
    //private variables unqiue to the book child
    const std::string isbn_;
    const std::string author_;
};
#endif