#include "clothing.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& SIZE, const std::string& BRAND) 
    : Product("clothing", name, price, qty), size_(SIZE), brand_(BRAND){}

//need to add keywords and display string and dump
std::set<std::string> Clothing::keywords() const{
        std::set<std::string> keywords = parseStringToWords(name_);
        std::set<std::string> brandwords = parseStringToWords(brand_);
        keywords.insert(brandwords.begin(), brandwords.end());
        return keywords;
}

std::string Clothing::displayString() const{

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << name_ << "\n"
    "Size: " << size_ << " Brand: " << brand_ << "\n"
    << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Clothing::dump(std::ostream& os) const{
    os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}


std::string Clothing::getSIZE() const{
    return size_; 
}
std::string Clothing::getBRAND() const{
    return brand_; 
}