#include "cagps.h"

CaGps::CaGps(int ID, int seclenght) {
  initTable(ID);
  G1_ = K;
  G2_ = K;
  its_ = seclenght;
}

CaGps::~CaGps(){}

void CaGps::lsfrsWork() {
  int aux1;
  int rxor2;
  int aux2;
  int rxor;

  tap1_ = tap1_ - 1;
  tap2_ = tap2_ - 1;
  G1sh_.push_back(G1_);
  G2sh_.push_back(G2_);
  
  for (int i = 0; i < its_; i++) {
    // g1
    aux1 = G1_[0];
    rxor = (G1_[0] ^ G1_[7]);
    G1rtr_.push_back(rxor);
    G1_ >>= (1);
    G1_[9] = rxor;
    G1sh_.push_back(G1_);

    // c/a code
    aux2 = (G2_[tap1_] ^ G2_[tap2_]);
    prn1_.push_back((aux1 ^ aux2));
    // g2
    rxor2 = (G2_[0] ^ G2_[1] ^ G2_[2] ^ G2_[4] ^ G2_[7] ^ G2_[8]);
    G2rtr_.push_back(rxor2);
    G2_>>= (1);
    G2_[9] = rxor2;
    G2sh_.push_back(G2_);
    
 
  }
}

void CaGps::showResults() {
  
  std::cout << "\nLFSR1      | realimentacion |";
  std::cout << "LFSR2      | realimentacion | secuencia C/A PRN1\n";

  for (int i = 0; i < its_; i++) {
    std::cout << G1sh_[i] << " |        " << G1rtr_[i] << "       |";
    std::cout << G2sh_[i] << " |   " << G2rtr_[i] << "            | " << prn1_[i] << "\n";
    std::cout << "---------------------------------------------------------------\n";
  }
}

void CaGps::initTable(int id) {
    switch(id) {
  case 1:
    tap1_ = 9;
    tap2_ = 5;
    break;
  case 2:
    tap1_ = 8;
    tap2_ = 4;
    break;
  case 3:
    tap1_ = 7;
    tap2_ = 3;
    break;
  case 4:
    tap1_ = 6;
    tap2_ = 2;
    break;
  case 5:
    tap1_ = 10;
    tap2_ = 2;
    break;
  case 6:
    tap1_ = 9;
    tap2_ = 1;
    break;
  case 7:
    tap1_ = 10;
    tap2_ = 3;
    break;
  case 8:
    tap1_ = 9;
    tap2_ = 2;
    break;
  case 9:
    tap1_ = 8;
    tap2_ = 1;
    break;
  case 10:
    tap1_ = 9;
    tap2_ = 8;
    break;
  case 11:
    tap1_ = 8;
    tap2_ = 7;
    break;
  case 12:
    tap1_ = 6;
    tap2_ = 5;
    break;
  case 13:
    tap1_ = 5;
    tap2_ = 4;
    break;
  case 14:
    tap1_ = 4;
    tap2_ = 3;
    break;
  case 15:
    tap1_ = 3;
    tap2_ = 2;
    break;
  case 16:
    tap1_ = 2;
    tap2_ = 1;
    break;  
  case 17:
    tap1_ = 10;
    tap2_ = 7;
    break;
  case 18:
    tap1_ = 9;
    tap2_ = 6;
    break;
  case 19:
    tap1_ = 8;
    tap2_ = 5;
    break;
  case 20:
    tap1_ = 7;
    tap2_ = 4;
  case 21:
    tap1_ = 6;
    tap2_ = 3;
    break;
  case 22:
    tap1_ = 5;
    tap2_ = 2;
    break;
  case 23:
    tap1_ = 10;
    tap2_ = 8;
    break;
  case 24:
    tap1_ = 7;
    tap2_ = 5;
    break;
  case 25:
    tap1_ = 6;
    tap2_ = 4;
    break;
  case 26:
    tap1_ = 5;
    tap2_ = 3;
    break;
  case 27:
    tap1_ = 4;
    tap2_ = 2;
    break;
  case 28:
    tap1_ = 3;
    tap2_ = 1;
    break;
  case 29:
    tap1_ = 10;
    tap2_ = 5;
  case 30:
    tap1_ = 9;
    tap2_ = 4;
  case 31:
    tap1_ = 8;
    tap2_ = 3;
    break;
  case 32:
    tap1_ = 7;
    tap2_ = 2;
  }
}