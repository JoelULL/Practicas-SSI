#include "cbc.h"

#define sz 32

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
    std::cout<< "Error deben haber 16 bytes por entrada";
    return -1;
}

int main (void) {

    std::string skey, siv, splain1, splain2;
    std::vector<std::bitset<8> > key;
    std::vector<std::bitset<8> > iv;
    std::vector<std::bitset<8> > plaintext1;
    std::vector<std::bitset<8> > plaintext2;
    std::vector<std::vector<std::bitset<8> > > allTheData;

    std::cout << "Clave: ";
    std::cin >> skey;
    analyzeBytes(skey, key);
    allTheData.push_back(key);

    std::cout << "\nIV: ";
    std::cin >> siv;
    analyzeBytes(siv, iv);
    allTheData.push_back(iv);

    std::cout << "\nBloque 1 de texto Original: ";
    std::cin >> splain1;
    analyzeBytes(splain1, plaintext1);
    allTheData.push_back(plaintext1);

    std::cout << "\nBloque 2 de texto Original: ";
    std::cin >> splain2;
    analyzeBytes(splain2, plaintext2);
    allTheData.push_back(plaintext2);

    if (skey.size() != sz || siv.size() != sz || splain1.size() != sz)
            error_msg();


    Cbc test(allTheData);
    test.cipherCbc();
    test.showResults();
    
    return 0;
}