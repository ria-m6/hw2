#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "datastore.h"
#include "product.h"
#include "user.h"



class MyDataStore: public DataStore{
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;
    void addToCart(const std::string& username, Product* product);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products;
    std::vector<User*> users;
};

#endif