#include "mydatastore.h"

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {

}

void MyDataStore::addProduct(Product* p) {
    products.push_back(p);
}


void MyDataStore::addUser(User* u) {
    users.push_back(u);
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::vector<Product*> result;

    
    return result;
}


void MyDataStore::dump(std::ostream& ofile) {
   
    ofile << "Dumping products and users..." << std::endl;
   
}

void MyDataStore::addToCart(const std::string& username, Product* product){

}
void MyDataStore::viewCart(const std::string& username){

}
void MyDataStore::buyCart(const std::string& username){

}
