#include "mydatastore.h"
#include <cctype>
#include <map>
#include <set>
#include <vector>

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
    for (std::map<std::string, User*>::iterator it = usernameToUser.begin(); it != usernameToUser.end(); ++it) {
        delete it->second;
    }
    for (std::map<std::string, std::set<Product*>>::iterator it = keywordToProduct.begin(); it != keywordToProduct.end(); ++it) {
        for (std::set<Product*>::iterator prodIt = it->second.begin(); prodIt != it->second.end(); ++prodIt) {
            delete *prodIt;
        }
    }
}

void MyDataStore::addProduct(Product* p) {
    std::set<std::string> keywords = p->keywords();
    for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it) {
        keywordToProduct[*it].insert(p);
    }
}


void MyDataStore::addUser(User* u) {
    usernameToUser[u->getName()] = u;
}



std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    // std::vector<Product*> result;

    std::set<Product*> resultSet;
    if (terms.empty()) return {};
    
    if (type == 0) { // AND search
        resultSet = keywordToProduct[terms[0]];
        for (size_t i = 1; i < terms.size(); i++) {
            std::set<Product*> temp;
            std::set_intersection(resultSet.begin(), resultSet.end(),
                                  keywordToProduct[terms[i]].begin(), keywordToProduct[terms[i]].end(),
                                  std::inserter(temp, temp.begin()));
            resultSet = temp;
        }
    } else { // OR search
        for (size_t i = 0; i < terms.size(); i++) {
            resultSet.insert(keywordToProduct[terms[i]].begin(), keywordToProduct[terms[i]].end());
        }
    }
    return std::vector<Product*>(resultSet.begin(), resultSet.end());

    
    // return result;
}


void MyDataStore::dump(std::ostream& ofile) {
   
    ofile << "Dumping products and users..." << std::endl;

    ofile << "<products>\n";
    for (std::map<std::string, std::set<Product*>>::iterator it = keywordToProduct.begin(); it != keywordToProduct.end(); ++it) {
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
    if (usernameToUser.find(username) != usernameToUser.end()) {
        usernameToCart[username].push_back(product);
    } else {
        std::cout << "Invalid username";
    }
    
}
void MyDataStore::viewCart(const std::string& username){
    if (usernameToCart.find(username) == usernameToCart.end()) {
        std::cout << "Invalid username";
        return;
    }
    int index = 1;
    for (std::vector<Product*>::iterator it = usernameToCart[username].begin(); it != usernameToCart[username].end(); ++it) {
        std::cout << "Item " << index++ << ":\n";
        std::cout << (*it)->displayString() << "\n";
    }

}
void MyDataStore::buyCart(const std::string& username){
    if (usernameToUser.find(username) == usernameToUser.end()) {
        std::cout << "UInvalid username";
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
