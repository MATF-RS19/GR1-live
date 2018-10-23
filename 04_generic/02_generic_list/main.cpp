#include "list.hpp"
#include <iostream>

#include <list>

int main()
{
    list<int> xs; 

    xs.push_back(3);
    xs.push_back(4);
    xs.push_back(5);

    xs.push_front(2);
    xs.push_front(1);

    for (unsigned i = 0; i < xs.size(); ++i) {
        std::cout << xs[i] << std::endl; 
    }

    std::cout << "Prebacujemo iz xs u ys" << std::endl;
    list<int> ys = std::move(xs);
    std::cout << "XS" << std::endl;
    for (unsigned i = 0; i < xs.size(); ++i) {
        std::cout << xs[i] << std::endl; 
    }
    std::cout << "YS" << std::endl;
    for (unsigned i = 0; i < ys.size(); ++i) {
        std::cout << ys[i] << std::endl; 
    }

    ys.pop_front();
    std::cout << "YS" << std::endl;
    for (unsigned i = 0; i < ys.size(); ++i) {
        std::cout << ys[i] << std::endl; 
    }

    xs = ys;
    std::cout << "XS" << std::endl;
    for (unsigned i = 0; i < xs.size(); ++i) {
        std::cout << xs[i] << std::endl; 
    }
    std::cout << "YS" << std::endl;
    for (unsigned i = 0; i < ys.size(); ++i) {
        std::cout << ys[i] << std::endl; 
    }

    // unit testing
    // catch2

    return 0;
}

