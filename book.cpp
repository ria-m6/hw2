#include "book.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Book::Book(const std::string& name, const std::string& ISBN, const std::string& Author, double price, int qty) 
    : Product("book", name, price, qty), isbn_(ISBN), author_(Author){}

Book::~Book(){}

std::set<std::string> Book::keywords() const {
    std::set<std::string> keywords = parseStringToWords(name_);
    std::set<std::string> authorwords = parseStringToWords(author_);
    keywords.insert(authorwords.begin(), authorwords.end());
    keywords.insert(isbn_);
    return keywords;
}

std::string Book::displayString() const {

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << name_ << "\n"
    << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
    << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Book::dump(std::ostream& os) const {
    os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}

std::string Book::getISBN() const{
    return isbn_; 
}
std::string Book::getAUTHOR() const{
    return author_; 
}