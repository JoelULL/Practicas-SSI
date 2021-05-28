#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#define rowamount 4
#define rowsize 4

class Aes {
    private:
        std::vector<std::vector<std::bitset<8> > > key_;
        std::vector<std::vector<std::bitset<8> > > roundkey_;
        std::vector<std::vector<std::bitset<8> > > text_;
        std::vector<std::vector<std::bitset<8> > > intermediate_;
        std::vector<std::vector<std::bitset<8> > > sbox_;
        std::vector<std::vector<std::bitset<8> > > rcon_;
    public:
        Aes(std::vector<std::bitset<8> > keyg, std::vector<std::bitset<8> > textg);
        ~Aes();
        void addRoundKey(std::vector<std::vector<std::bitset<8> > > mtx);
        void subBytes();
        void shiftRow();
        void mixColumn();
        void keyExpansion(int inx);
        void encrypt();
        void cuestionario();
    private:
        void toMatrix(std::vector<std::bitset<8> > param, 
          std::vector<std::vector<std::bitset<8> > > &matrix);
        std::string toHex(std::bitset<8> bits);
        void initializeBox();
        unsigned int interpretateHex(std::string s);
        std::vector<int> divideAndInterp(std::bitset<8> item);
        void gMixColumn(std::vector<std::bitset<8> > &r);
        void initializeRcon();
        void showResult();
        void showFirstRound();
};