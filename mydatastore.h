#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>
#include "datastore.h"
#include "product.h"
#include "user.h"



class MyDataStore: public DataStore{
public:
    MyDataStore();
    virtual ~MyDataStore();

    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    void addToCart(const std::string& username, Product* product);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
  
    
    std::map<std::string, User*> usernameToUser;//mapping username to User
    std::map<std::string, std::set<Product*> > keywordToProduct; // Maps keywords to products
    std::map<std::string, std::vector<Product*> > usernameToCart;//mapping username to carts
    

   
    // std::vector<User*> users;
    // std::map<std::string, std::set<Product*>> keywordIndex; // Keyword index

    // void indexProduct(Product* product); // Index a product by its keywords
    // std::map<std::string, std::set<Product*>> keywordMap; // Maps keywords to products
    // std::vector<Product*> products;
};

#endif