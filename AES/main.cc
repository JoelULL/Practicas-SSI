#include "aes.h"

unsigned int interpretateHex(std::string s) {
    unsigned int x = std::stoul(s, nullptr, 16);
    return x;
}
void analyzeBytes(std::string str, std::vector<std::bitset<8> > &vc) {
    int counter = 0;
    std::string aux;
    for (size_t i = 0; i < str.size(); i++) {
        if (counter == 2) {
            vc.push_back(interpretateHex(aux));
            aux = "";
            counter = 0;
        }
        aux+=str[i];
        counter++;
        if (i == str.size() - 1) {
            vc.push_back(interpretateHex(aux));
        }
    }
}
int error_msg() {
    std::cout<< "Error no hay 16 bytes";
    return -1;
}
int main (void) {

    std::string key;
    std::string text;
    std::vector<std::bitset<8> > keyg;
    std::vector<std::bitset<8> > textg;

    std::cout << "Clave(16 bytes en hexadecimal): ";
    std::cin >> key;

    std::cout << "Bloque de texto original (16 bytes en hexadecimal): ";
    std::cin >> text;

    if (key.size() < 32 || text.size() < 32)
        error_msg();

    analyzeBytes(key,keyg);
    analyzeBytes(text,textg);
    
    Aes test(keyg, textg);
    //test.encrypt();
    test.cuestionario();
    return 0;
}