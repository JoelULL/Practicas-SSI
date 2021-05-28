#include <iostream>
#include <vector>
#include <algorithm>

#define csize 256

class Rc4 {
    private:
        std::vector<int> S_;
        std::vector<int> K_;
        std::vector<int> KS_;
        std::vector<int> ciphermessage_;
        std::vector<int> decipher_;
        std::vector<int> M_;
        int messize_;
    public:
        Rc4(std::vector<int> seed, std::vector<int> message);
        ~Rc4();

        void KSA();
        void PRGA();
        void CipherMessage();
        void Decipher();
        void Showresults();
};
