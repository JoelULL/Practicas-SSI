#include "rc4.h"
/**
 * Si el makefile da problemas compilar como:
 * g++ -g rc4.h rc4.cc main.cc -o rc4
**/

int main () {
   std::vector<int> seed;
   seed.push_back(97);
   seed.push_back(45);
   seed.push_back(117);
   seed.push_back(98);
   seed.push_back(34);

   std::vector<int> message;
   message.push_back(1);
   message.push_back(34);
  

   Rc4 test(seed, message);
   test.KSA();
   /*
   test.CipherMessage();
   test.Showresults();
   */

    return 0;

}