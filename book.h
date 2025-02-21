#ifndef BOOK_H
#define BOOK_H

#include "product.h"

#include <string>
#include <set>


class Book : public Product{
public:
    Book(const std::string& name, const std::string& ISBN, const std::string& Author, double price, int qty);

    std::set<std::string> keywords() const override;

    std::string displayString() const override;

    void dump(std::ostream& os) const override;

    std::string getISBN() const;
    std::string getAUTHOR() const; 

private:
    const std::string isbn_;
    const std::string author_;
};
#endif