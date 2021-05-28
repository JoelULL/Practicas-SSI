#include "rsa.h"

bool checkMessage(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (!isupper(str[i]) && str[i] != ' ')
            return false;
    }
    return true;
}

int main (void) {

    long p, q, d;
    std::string message;

    std::cout << "\nmessage = "; 
    std::getline(std::cin, message);

    std::cout << "p = "; 
    std::cin >> p;
    std::cout << "\nq = "; 
    std::cin >> q;
    std::cout << "\nd = "; 
    std::cin >> d;


    if (!checkMessage(message)) {
        std::cout << "Error se piden caracteres del abecedario de A-Z sin Ñ"<<std::endl;
        return -1;
    }
  
    Rsa prgm(message, p, q, d);
    prgm.encrypt();
    prgm.showResult();
    
    return 0;
}