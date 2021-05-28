#include "rc4.h"

Rc4::Rc4(std::vector<int> seed, std::vector<int> message) {
    for (int i = 0; i < csize; i++) {
        S_.push_back(i);
        K_.push_back(seed[i % seed.size()]);
    }
    messize_ = message.size();
    for (size_t i = 0; i < message.size();i++) {
        M_.push_back(message[i]);
    }
} 

Rc4::~Rc4(){}

void Rc4::KSA() {
    int j = 0;
    for (int i = 0; i < csize; i++) {
       j = (j + S_[i] + K_[i]) % csize; 
       std::swap(S_[i],S_[j]);
    }
}

void Rc4::PRGA() {

    int i, j, k, t;
    i = j = k = 0;

    while ( k < messize_) {
        i = (i + 1) % csize;
        j = (j + S_[i]) % csize;
        std::swap(S_[i], S_[j]);
        t = (S_[i] + S_[j]) % csize;
        KS_.push_back(S_[t]);
        k++;
    }
}
void Rc4::CipherMessage() {
    KSA();
    PRGA();
    for (int i = 0; i < messize_; i++) {
        ciphermessage_.push_back(KS_[i] xor M_[i]);
    }
}

void Rc4::Decipher() {
    for (int i = 0; i < messize_; i++) {
      decipher_.push_back(KS_[i] xor ciphermessage_[i]);
    }
}

void Rc4::Showresults() {
    Decipher();
    std::cout << "La secuencia cifrante es:\n";
    for (size_t i = 0; i < KS_.size(); i++) 
      std::cout << KS_[i] << "\t";
    std::cout << "\n";

    std::cout << "El mensaje cifrado es: "<<"\n";
    for (size_t i = 0; i < ciphermessage_.size(); i++) 
      std::cout << ciphermessage_[i] << "\t";
    std::cout << "\n";      

    std::cout << "El mensaje descifrado es: "<<"\n";
    for (size_t i = 0; i < decipher_.size(); i++) 
      std::cout << decipher_[i] << "\t";
    std::cout << "\n";   
}