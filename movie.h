#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"

#include <string>
#include <set>

// movie
// Hidden Figures DVD
// 17.99
// 1
// Drama
// PG


class Movie: public Product{ //Product* newMovie = new Movie(genre_, rating_);
public:

    //Constructor + Destructor
    Movie(const std::string& name, double price, int qty, const std::string& GENRE, const std::string& RATING);
    ~Movie();
    //keywords, displayString, dump
    std::set<std::string> keywords() const override;

    std::string displayString() const override;

    void dump(std::ostream& os) const override;
    
    std::string getGENRE() const;
    std::string getRATING() const;

private:
    //strings unique to movie child
    const std::string genre_;
    const std::string rating_;
};
#endif