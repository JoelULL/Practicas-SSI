#include "binarymul.h"

unsigned int interpretateHex(std::string s) {
    unsigned int x = std::stoul(s, nullptr, 16);
    return x;
}
int main (void) {
    std::string byte1;
    std::string byte2;
    std::string algorithm;
    int b1, b2;
    
    std::cout << "Primer byte: ";
    std::cin >> byte1;

    std::cout << "\nSegundo byte: ";
    std::cin >> byte2;

    std::cout << "\nAlgoritmo: ";
    std::cin >> algorithm;

    b1 = interpretateHex(byte1);
    b2 = interpretateHex(byte2);

    BinaryMul test(b1,b2,algorithm);
    test.multiplyThem();
    test.showResults();
}