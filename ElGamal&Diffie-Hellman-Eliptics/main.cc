#include "eldifhel.h"

int main (void) {
    long p, a, b, gx, gy, db , da, m;

    std::cout << "p= "; std::cin >> p;
    std::cout << "\na= "; std::cin >> a;
    std::cout << "\nb= "; std::cin >> b;
    std::cout << "\ncoordenada x de G= "; std::cin >> gx;
    std::cout << "\ncoordenada y de G= "; std::cin >> gy;
    std::cout << "\ndB= "; std::cin >> db;
    std::cout << "\ndB= "; std::cin >> da;
    std::cout << "\nm= "; std::cin >> m;

    ElDiffieHel test(p, a, b, gx, gy, db, da, m);

    if (!test.lehmanPeralta(p)) {
        std::cout << "\n" << p << "p no es primo segun el test de lehmanPeralta\n";
        return -1;
    }
    if (!test.validPoint()) {
        std::cout << "\n(" << gx << ", "<< gy << ")  no es un punto de la curva\n";
    }
    if(!test.checkAandB()) {
        std::cout << " a y b deben satisfacer que: 4a³ + 27b² ≠ 0 (mod p)\n";
    }

    test.gamalCodeMessage();
    test.showResult();
    return 0;
}