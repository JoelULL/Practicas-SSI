#include "aes.h"
#define bsz 16
class Cbc {
    private:
        std::vector<std::vector<std::bitset<8> > > plaintexts_;
        std::vector<std::bitset<8> >  key_;
        std::vector<std::bitset<8> > initialization_;
        std::vector<std::vector<std::bitset<8> > > results_;
        int lastinx_;
        bool optional_;
        int dif_;

    public:
    Cbc(std::vector<std::vector<std::bitset<8> > > allTheData);
    ~Cbc();

    void cipherCbc();
    std::vector<std::bitset<8> > xorOfbitsets(std::vector<std::bitset<8> > bs1, 
        std::vector<std::bitset<8> > bs2);
    void showResults();
    private:
    void insertZeros();
};