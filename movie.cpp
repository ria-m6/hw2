#include "movie.h"
#include "util.h"
#include <sstream>
#include <iomanip>

Movie::Movie(const std::string& name, double price, int qty, const std::string& GENRE, const std::string& RATING) 
    : Product("movie", name, price, qty), genre_(GENRE), rating_(RATING){}
Movie::~Movie(){}

//adds keywords from name and genre to set
std::set<std::string> Movie::keywords() const{
    std::set<std::string> keywords = parseStringToWords(name_);
    std::set<std::string> genrewords = parseStringToWords(genre_);
    keywords.insert(genrewords.begin(), genrewords.end());
    return keywords;
}

//accurately displays string
std::string Movie::displayString() const{

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << name_ << "\n"
    << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
    << price_ << " " << qty_ << " left.";
    return oss.str();
}

//dumps movie info
void Movie::dump(std::ostream& os) const{
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

std::string Movie::getGENRE() const{
    return genre_; 
}
std::string Movie::getRATING() const{
    return rating_; 
}