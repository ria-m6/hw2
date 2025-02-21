#include "mydatastore.h"
#include "util.h"
#include <cctype>
#include <map>
#include <set>
#include <vector>

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    for (std::map<std::string, User*>::iterator it = usernameToUser.begin(); it != usernameToUser.end(); ++it) {
        // std::cout << "Deleting user: " << it->first << std::endl;
        delete it->second;
    }

    std::set<Product*> deletedProducts; // track deleted products
    for (std::map<std::string, std::set<Product*> >::iterator it = keywordToProduct.begin(); it != keywordToProduct.end(); ++it) {
        for (std::set<Product*>::iterator prodIt = it->second.begin(); prodIt != it->second.end(); ++prodIt) {
            if (deletedProducts.find(*prodIt) == deletedProducts.end()) { // check if already deleted
                // std::cout << "Deleting product: " << (*prodIt)->getName() << std::endl;
                delete *prodIt;  
                deletedProducts.insert(*prodIt);  // mark as deleted
            }
        }
    }

    usernameToUser.clear();
    keywordToProduct.clear();
}


void MyDataStore::addProduct(Product* p) {
    std::set<std::string> keywords = p->keywords();
    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        //std::cout << "Adding keyword: " << *it << " for product: " << p->getName() << std::endl; 
        keywordToProduct[*it].insert(p);
    }
}


void MyDataStore::addUser(User* u) {
    //std::cout << u->getName() << std::endl;
    usernameToUser[u->getName()] = u;
}



std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> resultSet;
    std::vector<Product*> result; 

    if (terms.empty()) { return result; }

    if (type == 0) { // AND search
        resultSet = keywordToProduct[terms[0]];
        for (size_t i = 1; i < terms.size(); i++) {
            resultSet = setIntersection(resultSet, keywordToProduct[terms[i]]);
        }
    } else { // OR search
        for (size_t i = 0; i < terms.size(); i++) {
            resultSet = setUnion(resultSet, keywordToProduct[terms[i]]);
        }
    }

    // Convert the set to a vector and assign to result
    result.assign(resultSet.begin(), resultSet.end());

    return result;
}


void MyDataStore::dump(std::ostream& ofile) {
   
    ofile << "Dumping products and users..." << std::endl;

    ofile << "<products>\n";
    for (std::map<std::string, std::set<Product*> >::iterator it = keywordToProduct.begin(); it != keywordToProduct.end(); ++it) {
        for (std::set<Product*>::iterator prodIt = it->second.begin(); prodIt != it->second.end(); ++prodIt) {
            (*prodIt)->dump(ofile);
        }
    }
    ofile << "</products>\n<users>\n";
    for (std::map<std::string, User*>::iterator it = usernameToUser.begin(); it != usernameToUser.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>\n";
}



void MyDataStore::addToCart(const std::string& username, Product* product){
    //std::cout << "Username reached here: " << username << std::endl;
    if (usernameToUser.find(username) != usernameToUser.end()) {
        usernameToCart[username].push_back(product);
    } else {
        std::cout << "Invalid request\n";
    }
    
}
void MyDataStore::viewCart(const std::string& username){
    // std::cout<<username<<std::endl;
    if (usernameToCart.find(username) == usernameToCart.end()) {
        // std::cout<<"This ran and is causing the error"<<std::endl;
        std::cout << "Invalid username\n";
        return;
    }
    int index = 1;
    for (std::vector<Product*>::iterator it = usernameToCart[username].begin(); it != usernameToCart[username].end(); ++it) {
        std::cout<< "\n";
        std::cout << "Item " << index++ << "\n";
        std::cout << (*it)->displayString() << "\n";
    }

}
void MyDataStore::buyCart(const std::string& username){
    if (usernameToUser.find(username) == usernameToUser.end()) {
        // std::cout << "Invalid request\n";
        std::cout << "Invalid username\n" << std::endl;
        return;
    }
    User* user = usernameToUser[username];
    std::vector<Product*>& cart = usernameToCart[username];
    std::vector<Product*> remaining;
    
    for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
        if ((*it)->getQty() > 0 && user->getBalance() >= (*it)->getPrice()) {
            (*it)->subtractQty(1);
            user->deductAmount((*it)->getPrice());
        } else {
            remaining.push_back(*it);
        }
    }
    cart = remaining;
}
