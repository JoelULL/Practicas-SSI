#include "cagps.h"

int main (void) {
    int id, its;
    std::cout << "ID: ";
    std::cin >> id;

    std::cout << "\nLongitud sec salida: ";
    std::cin >> its;

    if (id <= 0 || id > 32) {
        std::cout << "Error id incorrecto";
        return 1;
    }


    CaGps test(id, its);
    test.lsfrsWork();
    test.showResults();


    return 0;
}
