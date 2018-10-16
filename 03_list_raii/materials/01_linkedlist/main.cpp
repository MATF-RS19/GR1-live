
#include "list.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Pravimo listu..." << std::endl;

    list xs;

    xs.push_back(3);
    xs.push_back(4);
    xs.push_back(5);

    xs.push_front(2);
    xs.push_front(1);

    std::cout << "XS:" << std::endl;

    for (unsigned int i = 0; i < xs.size(); ++i) {
        std::cout << xs[i] << std::endl;
    }

    std::cout << "Prebacujemo podatke iz xs u ys..." << std::endl;

    list ys = std::move(xs);

    // U opstem slucaju, koriscenje promenljive iz koje su ukradeni
    // podaci (moved-from) nije dozvoljeno - jedino se zahteva da je
    // moguce pozvati destruktor nad tim objektom. Nasa implementacija
    // liste dozvoljava koriscenje i moved-from listi jer ostavljamo
    // listu u konzistentnom stanju.

    std::cout << "XS:" << std::endl;

    for (unsigned int i = 0; i < xs.size(); ++i) {
        std::cout << xs[i] << std::endl;
    }

    std::cout << "YS:" << std::endl;

    for (unsigned int i = 0; i < ys.size(); ++i) {
        std::cout << ys[i] << std::endl;
    }

    ys.pop_front();

    for (unsigned int i = 0; i < ys.size(); ++i) {
        std::cout << ys[i] << std::endl;
    }

    std::cout << "Kopiramo podatke iz ys u xs..." << std::endl;

    xs = ys;

    ys.pop_front();

    std::cout << "XS:" << std::endl;

    for (unsigned int i = 0; i < xs.size(); ++i) {
        std::cout << xs[i] << std::endl;
    }

    std::cout << "YS:" << std::endl;

    for (unsigned int i = 0; i < ys.size(); ++i) {
        std::cout << ys[i] << std::endl;
    }

    return 0;
}
