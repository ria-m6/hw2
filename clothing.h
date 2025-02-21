#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"

#include <string>
#include <set>
#include <sstream>

// clothing
// Men's Fitted Shirt
// 39.99
// 25
// Medium
// J. Crew

class Clothing: public Product{ //Product* newClothing = new Clothing(size_, brand_);
public:
    Clothing(const std::string& name, double price, int qty, const std::string& SIZE, const std::string& BRAND);
    //need to add keywords and display string and dump
    std::set<std::string> keywords() const override;

    std::string displayString() const override;

    void dump(std::ostream& os) const override;
    
    
    std::string getSIZE() const;
    std::string getBRAND() const;

private:
    const std::string size_;
    const std::string brand_;
};
#endif