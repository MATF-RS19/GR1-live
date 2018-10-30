#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> xs(10);
    std::iota(std::begin(xs), std::end(xs), 1);

    // rotiramo na levu stranu niz za k pozicija
    int k = 3;
    // Ne vrsi se provera da li se ispada iz opsega u okviru
    // funkcije rotate -> treba biti pazljiv.
    std::rotate(std::begin(xs), std::begin(xs) + k, std::end(xs));

    // Ispisujemo elemente...
    std::copy(
        std::begin(xs),
        std::end(xs),
        std::ostream_iterator<int>(std::cout, "\n")
    );

    return 0;
}
