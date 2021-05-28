#include "common.h"

#define aes 27
#define snow 169

class BinaryMul {
    private:
    std::bitset<8> byte1_;
    std::bitset<8> byte2_;
    std::bitset<8> result_;
    std::bitset<8> bytealgorithm_;
    std::bitset<8> lighter_;
    std::bitset<8> heavier_;
    std::vector<int> multindex_;
    int maxin_;

    public:
    BinaryMul(int byte1, int byte2, std::string algorithm);
    ~BinaryMul();
   
    void lighterByte();
    void getMultipliers();
    void multiplyThem();
    void showResults();
};