#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>


#define mid 32
#define K 1023

class CaGps {
    private:
    std::bitset<10> G1_;
    std::bitset<10> G2_;
    std::vector<int> prn1_;
    std::vector<std::bitset<10> > G1sh_;
    std::vector<std::bitset<10> > G2sh_;
    std::vector<int> G1rtr_;
    std::vector<int> G2rtr_;
    int tap1_;
    int tap2_;
    int its_;
    public:
    CaGps(int ID, int seclenght);
    ~CaGps();
    void initTable(int id);
    void lsfrsWork();
    void showResults();
};