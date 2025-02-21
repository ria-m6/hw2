#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std::string& name, double price, int qty, const std::string& GENRE, const std::string& RATING) 
    : Product("movie", name, price, qty), genre_(GENRE), rating_(RATING){}

std::set<std::string> Movie::keywords() const{
    std::set<std::string> keywords = parseStringToWords(name_);
    keywords.insert(genre_);
    return keywords;
}

std::string Movie::displayString() const{

    std::ostringstream oss;
    oss << name_ << "\n"
    << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
    << price_ << " " << qty_ << " left.";
    return oss.str();
}

void Movie::dump(std::ostream& os) const{
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

std::string Movie::getGENRE() const{
    return genre_; 
}
std::string Movie::getRATING() const{
    return rating_; 
}