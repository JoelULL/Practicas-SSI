#include "cbc.h"
std::string toHex(std::bitset<8> bits) {
    std::stringstream res;
    res << std::hex << bits.to_ulong();
    return res.str();
}

Cbc::Cbc(std::vector<std::vector<std::bitset<8> > > allTheData) {
    optional_ = false;
    key_ = allTheData[0];
    initialization_ = allTheData[1];
    for (size_t i = 2; i < allTheData.size(); i++)
        plaintexts_.push_back(allTheData[i]);
    if (plaintexts_[plaintexts_.size() - 1].size() < bsz) {
        dif_ = bsz - plaintexts_[plaintexts_.size() - 1].size();
        optional_ = true;
        insertZeros();
    }
    lastinx_= plaintexts_.size() - 1;
}

Cbc::~Cbc(){}

void Cbc::cipherCbc() {
    std::vector<std::bitset<8> > xors;
    std::vector<std::bitset<8> > operate;
    std::vector<std::bitset<8> > aux;
 
    size_t i = 0;
    bool flag = false;
    bool last = false;
    do {
        if (i == 0) {
            xors = xorOfbitsets(initialization_, plaintexts_[i]);
        }
        Aes cblock(key_,xors);
        cblock.encrypt();
        results_.push_back(cblock.toCbc());
        i++;
        if (i >= plaintexts_.size()) {
            break;
        }
        xors = xorOfbitsets(cblock.toCbc(),plaintexts_[i]);
    }while(!flag);

    if (optional_) {
        aux = results_[lastinx_ - 1];
        results_.erase(results_.begin() + (lastinx_ - 1) );
        results_.push_back(aux);
    }
}

std::vector<std::bitset<8> > Cbc::xorOfbitsets(std::vector<std::bitset<8> > bs1, 
    std::vector<std::bitset<8> > bs2) {
        std::vector<std::bitset<8> > result;
        for (size_t i = 0; i < bs1.size(); i++)
            result.push_back(bs1[i] ^ bs2[i]);

        return result;   
    }

void Cbc::showResults() {
    int li = results_.size() - 1;
    if (optional_) {
        for (int i = 0; i < dif_; i++)
            results_[li].pop_back();
    }
   
    for (size_t i = 0; i < results_.size(); i++) {
        std::cout << "Bloque "<< i + 1 << " de texto cifrado: ";
        for (size_t j = 0; j < results_[i].size(); j++) {
            std::cout << toHex(results_[i][j]) << " ";
        }
        if (i == li && optional_) {
            for (int k = 0; k < dif_; k++)
                std::cout << "-- ";
        }
        std::cout << std::endl;
    }
}

void Cbc::insertZeros() {
    do {
        plaintexts_[plaintexts_.size() - 1].push_back(0);
    }while(plaintexts_[plaintexts_.size() - 1].size() < 16);
}