#include "aes.h"
std::vector<std::bitset<8> > emptyrow = {0, 0, 0, 0};
Aes::Aes(std::vector<std::bitset<8> > keyg, std::vector<std::bitset<8> > textg) {
    initializeBox();
    initializeRcon();
    toMatrix(keyg, key_);
    toMatrix(textg, text_);
    roundkey_ = key_;
    for (size_t i = 0; i < rowamount; i++) {
        intermediate_.push_back(emptyrow);
    }
}

Aes::~Aes() {}

void Aes::toMatrix(std::vector<std::bitset<8> > param, 
    std::vector<std::vector<std::bitset<8> > > &matrix) {
    int counter1 = 0;
    std::vector<std::bitset<8> > row;
    std::vector<std::vector<std::bitset<8> > > transpose;

    for (size_t i = 0; i < param.size(); i++) {
        if (counter1 == 4) {
            matrix.push_back(row);
            row.clear();
            counter1 = 0;
        }
        counter1++;
        row.push_back(param[i]);
        if (i == param.size() - 1)
            matrix.push_back(row);
    }

    for (int i = 0; i < rowamount; i++)
        transpose.push_back(emptyrow);

    for(int i = 0; i < rowamount; ++i){
        for(int j=0; j < rowamount; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }
    matrix = transpose;
}

std::string Aes::toHex(std::bitset<8> bits) {
    std::stringstream res;
    res << std::hex << bits.to_ulong();
    return res.str();
}

void Aes::shiftRow() {
    std::bitset<8> aux;
    for (size_t i = 0; i < intermediate_.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            aux = intermediate_[i][0];
            intermediate_[i].erase(intermediate_[i].begin());
            intermediate_[i].push_back(aux);
        }
    }   
}

void Aes::addRoundKey(std::vector<std::vector<std::bitset<8> > > mtx) {
    for(size_t i = 0; i < intermediate_.size(); i++) {
       for(int j = 0; j < rowsize; j++) {
           intermediate_[i][j] = mtx[i][j] ^ roundkey_[i][j];
       }
    }
                        for (size_t i = 0; i < intermediate_.size();i++){
            if(i != 0)
                std::cout << std::endl;
        for (size_t j = 0; j < 4;j++) {
            std::cout << toHex(intermediate_[i][j]) <<" ";
        }
    }
}

void Aes::subBytes() {
    std::vector<int> rowandcolumn;
    for(size_t i = 0; i < intermediate_.size(); i++) {
       for(int j = 0; j < rowsize; j++) {
           rowandcolumn = divideAndInterp(intermediate_[i][j]);
           intermediate_[i][j] = sbox_[rowandcolumn[0]][rowandcolumn[1]];
           rowandcolumn.clear();
       }
    }
}

void Aes::mixColumn() {
    std::vector<std::vector<std::bitset<8> > > empty;
    std::vector<std::vector<std::bitset<8> > > transpose;

    for (int i = 0; i < rowamount; i++) {
        empty.push_back(emptyrow);
        transpose.push_back(emptyrow);
    }
    for(int i = 0; i < rowamount; ++i){
        for(int j=0; j < rowamount; ++j) {
            empty[j][i] = intermediate_[i][j];
        }
    }
    for (size_t i = 0; i < intermediate_.size(); i++) {
        gMixColumn(empty[i]);
    }

    for(int i = 0; i < rowamount; ++i){
        for(int j=0; j < rowamount; ++j) {
            transpose[j][i] = empty[i][j];
        }
    }

    intermediate_ = transpose;
    

}

void Aes::keyExpansion(int inx) {
    std::vector<std::vector<std::bitset<8> > > newroundkey;
    std::vector<std::vector<std::bitset<8> > > roundkey = roundkey_;
    std::vector<std::vector<std::bitset<8> > > emptyone;
    std::vector<std::vector<std::bitset<8> > > transpose1;
    std::vector<std::vector<std::bitset<8> > > toclear;

    std::vector<std::bitset<8> > lastcolumn;
    std::vector<std::bitset<8> > lastclmsbox;
    std::bitset<8> auxiliar;

    std::vector<int> rowandcolumn;
    std::bitset<8> sboxed;

    for (int i = 0; i < rowsize; i++)
       transpose1.push_back(emptyrow);

    for(int i = 0; i < rowsize; ++i)
        for(int j=0; j < 4; ++j) {
            transpose1[j][i] = roundkey[i][j];
        }
        roundkey = transpose1;

    //primer paso
    lastcolumn = roundkey[3];

    //segundo paso
    auxiliar = lastcolumn[0];
    lastcolumn.erase(lastcolumn.begin());
    lastcolumn.push_back(auxiliar);

    //tercer paso
    for (int i = 0; i < 4; i++) {
        rowandcolumn = divideAndInterp(lastcolumn[i]);
        sboxed = sbox_[rowandcolumn[0]][rowandcolumn[1]];
        lastclmsbox.push_back(sboxed);
        sboxed = 0;
    }
     //cuarto paso
    std::vector<std::bitset<8> > rfromxors;
    for (int i = 0; i < 4; i++)
        rfromxors.push_back(transpose1[0][i] ^ lastclmsbox[i] ^ rcon_[inx][i]); 

    //quinto paso
    newroundkey.push_back(rfromxors);
    rfromxors.clear();

    //sexto paso
    for (size_t i = 1; i < transpose1.size(); i++) {
        for (int j = 0; j < 4;j++) {
           rfromxors.push_back(transpose1[i][j] ^ newroundkey[i - 1][j]);
        }
        newroundkey.push_back(rfromxors);
        rfromxors.clear();
    }
    //final
    for (int i = 0; i < 4;i++)
        emptyone.push_back(emptyrow);

    for(int i=0; i<4; ++i)
            for(int j=0; j<4; ++j) {
            emptyone[j][i] = newroundkey[i][j];
        }
    roundkey_ = emptyone;

    //liberar memoria
    emptyone = toclear;
    transpose1 = toclear;
   //mostrar
    std::vector<std::vector<std::bitset<8> > > transpose2;
    for (int i = 0; i < 4; i++)
        transpose2.push_back(emptyrow);

        for(int i = 0; i < rowsize; ++i)
            for(int j=0; j < 4; ++j) {
                transpose2[j][i] = roundkey_[i][j];
        }
    std::string result;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "roundkey "<<inx + 1;
    for (size_t i = 0; i < transpose2.size();i++){
        for (size_t j = 0; j < 4; j++) {
            if (toHex(transpose2[i][j]).size() == 1)
                result+= "0";
            result+= toHex(transpose2[i][j]);
        }
    }
    std::cout << "(" << result<<") = ";
    transpose2 = toclear;
}

void Aes::encrypt() {
    
    int indx = 0;
    addRoundKey(text_);
    showFirstRound();
    while(indx < 9) {
        subBytes();
        shiftRow();
        mixColumn();
        keyExpansion(indx);
        addRoundKey(intermediate_);
        showResult();
        indx++;
    }
    subBytes();
    shiftRow();
    keyExpansion(9);
    addRoundKey(intermediate_);
    showResult();
    std::cout << std::endl;
    std::cout << "El bloque de texto cifrado es: ";
    showResult();
}

void Aes::initializeBox() {
    std::vector<std::string> sitems =
    {
        "0x63", "0x7C", "0x77", "0x7B", "0xF2", "0x6B", "0x6F", "0xC5", "0x30", "0x01", "0x67", "0x2B", "0xFE", "0xD7", "0xAB", "0x76",
        "0xCA", "0x82", "0xC9", "0x7D", "0xFA", "0x59", "0x47", "0xF0", "0xAD", "0xD4", "0xA2", "0xAF", "0x9C", "0xA4", "0x72", "0xC0",
        "0xB7", "0xFD", "0x93", "0x26", "0x36", "0x3F", "0xF7", "0xCC", "0x34", "0xA5", "0xE5", "0xF1", "0x71", "0xD8", "0x31", "0x15",
        "0x04", "0xC7", "0x23", "0xC3", "0x18", "0x96", "0x05", "0x9A", "0x07", "0x12", "0x80", "0xE2", "0xEB", "0x27", "0xB2", "0x75",
        "0x09", "0x83", "0x2C", "0x1A", "0x1B", "0x6E", "0x5A", "0xA0", "0x52", "0x3B", "0xD6", "0xB3", "0x29", "0xE3", "0x2F", "0x84",
        "0x53", "0xD1", "0x00", "0xED", "0x20", "0xFC", "0xB1", "0x5B", "0x6A", "0xCB", "0xBE", "0x39", "0x4A", "0x4C", "0x58", "0xCF",
        "0xD0", "0xEF", "0xAA", "0xFB", "0x43", "0x4D", "0x33", "0x85", "0x45", "0xF9", "0x02", "0x7F", "0x50", "0x3C", "0x9F", "0xA8",
        "0x51", "0xA3", "0x40", "0x8F", "0x92", "0x9D", "0x38", "0xF5", "0xBC", "0xB6", "0xDA", "0x21", "0x10", "0xFF", "0xF3", "0xD2",
        "0xCD", "0x0C", "0x13", "0xEC", "0x5F", "0x97", "0x44", "0x17", "0xC4", "0xA7", "0x7E", "0x3D", "0x64", "0x5D", "0x19", "0x73",
        "0x60", "0x81", "0x4F", "0xDC", "0x22", "0x2A", "0x90", "0x88", "0x46", "0xEE", "0xB8", "0x14", "0xDE", "0x5E", "0x0B", "0xDB",
        "0xE0", "0x32", "0x3A", "0x0A", "0x49", "0x06", "0x24", "0x5C", "0xC2", "0xD3", "0xAC", "0x62", "0x91", "0x95", "0xE4", "0x79",
        "0xE7", "0xC8", "0x37", "0x6D", "0x8D", "0xD5", "0x4E", "0xA9", "0x6C", "0x56", "0xF4", "0xEA", "0x65", "0x7A", "0xAE", "0x08",
        "0xBA", "0x78", "0x25", "0x2E", "0x1C", "0xA6", "0xB4", "0xC6", "0xE8", "0xDD", "0x74", "0x1F", "0x4B", "0xBD", "0x8B", "0x8A",
        "0x70", "0x3E", "0xB5", "0x66", "0x48", "0x03", "0xF6", "0x0E", "0x61", "0x35", "0x57", "0xB9", "0x86", "0xC1", "0x1D", "0x9E",
        "0xE1", "0xF8", "0x98", "0x11", "0x69", "0xD9", "0x8E", "0x94", "0x9B", "0x1E", "0x87", "0xE9", "0xCE", "0x55", "0x28", "0xDF",
        "0x8C", "0xA1", "0x89", "0x0D", "0xBF", "0xE6", "0x42", "0x68", "0x41", "0x99", "0x2D", "0x0F", "0xB0", "0x54", "0xBB", "0x16"
    };

    std::vector<std::bitset<8> > srow;
    int cnt = 0;

    for (size_t i = 0; i < sitems.size();i++) {
        srow.push_back(interpretateHex(sitems[i]));
        cnt++;
        if (cnt == 16) {
           cnt = 0;
           sbox_.push_back(srow);
           srow.clear();
        }
    }
}

unsigned int Aes::interpretateHex(std::string s) {
    unsigned int x = std::stoul(s, nullptr, 16);
    return x;
}

std::vector<int> Aes::divideAndInterp(std::bitset<8> item) {
    int row;
    int column;
    std::vector<int> result;
    std::bitset<4> r;
    std::bitset<4> cl;
    int j = 0;

    for (size_t i = 0; i < item.size(); i++) {
        if (i < 4)
            cl[i] = item[i];
        else {
            r[j] = item[i];
            j++;
        }
    }
    
    row = (int)(r.to_ulong());
    column = (int)(cl.to_ulong());

    result.push_back(row);
    result.push_back(column);

    return result;
}

void Aes::gMixColumn(std::vector<std::bitset<8> > &r) {
    std::vector<std::bitset<8> > a = r;
    std::vector<std::bitset<8> > b = {0,0,0,0};
    int c;
    std::bitset<8> h;
    std::bitset<8> hibit = 128;
    std::bitset<8> galoisf = 27;

    for (c = 0; c < 4; c++) {
        h = r[c] & hibit;
        b[c] = r[c] << 1;
        if(h == hibit)
            b[c] ^= galoisf;
    }
    r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
    r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
    r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
    r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}

void Aes::initializeRcon() {
    std::vector<std::bitset<8> > notzeros;
    int j = 1;

    notzeros.push_back(j);
    for (int i = 0; i < 7; i++) {
        notzeros.push_back(j * 2);
        j = j * 2;
    }

    notzeros.push_back(27);
    notzeros.push_back(54);

    
    for (int i = 0; i < 10 ;i++)
        rcon_.push_back(emptyrow);

    for (size_t i = 0; i < rcon_.size();i++) {
        rcon_[i][0] = notzeros[i];
    }
}

void Aes::showResult() {
    std::vector<std::vector<std::bitset<8> > > toclear;
    std::vector<std::vector<std::bitset<8> > > transpose2;

    for (int i = 0; i < 4; i++)
        transpose2.push_back(emptyrow);

        for(int i = 0; i < rowsize; ++i)
            for(int j=0; j < 4; ++j) {
                transpose2[j][i] = intermediate_[i][j];
        }
    std::string result;
    for (size_t i = 0; i < transpose2.size();i++){
        for (size_t j = 0; j < 4; j++) {
            if (toHex(transpose2[i][j]).size() == 1)
                result+= "0";
            result+= toHex(transpose2[i][j]);
        }
    }
    std::cout << result<<std::endl;
    transpose2 = toclear;
}

void Aes::showFirstRound() {
    std::vector<std::vector<std::bitset<8> > > transpose2;
    std::vector<std::vector<std::bitset<8> > > toclear;
    for (int i = 0; i < 4; i++)
        transpose2.push_back(emptyrow);

        for(int i = 0; i < rowsize; ++i)
            for(int j=0; j < 4; ++j) {
                transpose2[j][i] = roundkey_[i][j];
        }
    std::string result;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "roundkey 0: ";
    for (size_t i = 0; i < transpose2.size();i++){
        for (size_t j = 0; j < 4; j++) {
            if (toHex(transpose2[i][j]).size() == 1)
                result+= "0";
            result+= toHex(transpose2[i][j]);
        }
    }
    std::cout << "(" << result<<") = ";
    transpose2 = toclear;
    showResult();
}

void Aes::cuestionario() {
    addRoundKey(text_);
    subBytes();
    shiftRow();
    mixColumn();
    keyExpansion(0);
    std::cout << "seria este: "<<std::endl;
    addRoundKey(intermediate_);
}