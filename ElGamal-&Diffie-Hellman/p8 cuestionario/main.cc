#include "gamal.h"

int main (void) {

    Gamal vicese(1,1,1,1,1);

    std::cout << vicese.modInverse(11,29);

   
    
  

    return 0;
}