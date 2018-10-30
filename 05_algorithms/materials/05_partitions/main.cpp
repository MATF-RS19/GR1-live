// vim: set undofile:
// Program: partitions

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>


int main(int argc, char *argv[])
{
    // Zelimo da razdvojimo elemente koji su deljivi sa 3 u jednu grupu,
    // one koji daju ostatak 1 u drugu, i one koji daju ostatak 2 u trecu
    std::vector<int> xs { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

    // Izdvajamo elemente koji su deljivi sa 3 na pocetak kolekcije.
    // Algoritam vraca iterator na prvi element koji nije deljiv.
    const auto first_end =
        std::stable_partition(std::begin(xs), std::end(xs),
                              [] (auto i) { return i % 3 == 0; }
                );

    // Particionisemo drugi deo kolekcije (preskacemo elemente koji su
    // deljivi sa tri) - druga grupa ce imati samo elemente koji
    // daju ostatak 1 pri deljenju sa 3
    const auto second_end =
        std::stable_partition(first_end, std::end(xs),
                              [] (auto i) { return i % 3 == 1; }
                );

    // Ispisujemo rezultat na cout
    std::copy(std::begin(xs), std::end(xs),
              std::ostream_iterator<int>(std::cout, " "));

    return 0;
}
