#include "gamal.h"

bool isPrime(int n)
{
    if (n <= 1)
        return false;
 
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
 
    return true;
}

int main (void) {

    int p, a, k, x ,m;

    std::cout << "p = "; std::cin >> p; std::cout << "a = "; std::cin >> a;
    std::cout << "k = "; std::cin >> k; std::cout << "x = "; std::cin >> x;
    std::cout << "m = "; std::cin >> m;
    if (!isPrime(p)) {
        std::cout << "p debe ser primo\n";
        return -1;
    }

    Gamal prgm(p, a, k, x, m);
    
    prgm.gamalEncrypt();
    prgm.gamalDecrypt();
    prgm.showresults();

    return 0;
}