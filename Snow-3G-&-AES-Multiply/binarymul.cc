#include "binarymul.h"

BinaryMul::BinaryMul(int byte1, int byte2, std::string algorithm) {
    byte1_ = byte1;
    byte2_ = byte2;
    if (algorithm == "aes")
        bytealgorithm_ = aes;
    if (algorithm == "snow")
        bytealgorithm_ = snow;
}
BinaryMul::~BinaryMul() {}

void BinaryMul::lighterByte() {
    int counter1 = 0;
    int counter2 = 0;

    for (int i = 0; i < 8; i++) {
        if (byte1_[i] == 1)
            counter1++;
        if (byte2_[i] == 1)
            counter2++;
    }
    if (counter1 < counter2){
        lighter_ = byte1_;
        heavier_ = byte2_;
    }  
    else{
        lighter_ = byte2_;
        heavier_ = byte1_;
    }
}
void BinaryMul::getMultipliers() {
    for (int i = 0; i < 8; i++) {
        if(lighter_[i] == 1) {
            maxin_ = i;
            multindex_.push_back(i);       
        }
    }
}
void BinaryMul::multiplyThem() {
    std::vector<std::bitset<8> > results;
    lighterByte();
    getMultipliers();

    if (multindex_[0] == 0) {
        multindex_.erase(multindex_.begin());
        results.push_back(heavier_);
    }
    for (int i = 0; i < maxin_ + 1; i++) {
        for (size_t j = 0; j < multindex_.size(); j++) {
            if ( i == multindex_[j]){
                results.push_back(heavier_);
                break;
            }
        }
        if (heavier_[7] == 1) {
            (heavier_ <<= 1);
            heavier_ = (heavier_ ^ bytealgorithm_);
        }
        else {
            (heavier_ <<= 1);
        }
    }
    for (size_t i = 0; i < results.size(); i++) {
        result_^= results[i];
    }
}

void BinaryMul::showResults() {
    std::cout << "\nPrimer byte: " << byte1_;
    std::cout << "\nSegundo byte: " << byte2_;
    std::cout << "\nByte Algoritmo: " << bytealgorithm_; 
    std::cout << "\nMultiplicacion: " << result_<<"\n";
}