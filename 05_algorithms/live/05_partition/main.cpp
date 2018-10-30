#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

int main()
{
    std::vector<int> xs(14);
    // std::iota(xs.begin(), xs.end(), 1);
    // -> ovo vise volimo :)
    std::iota(std::begin(xs), std::end(xs), 1);

    // Izdvajamo elemente koji su deljivi sa 3 na pocetak kolekcija.
    //const auto first_end = std::partition(
    const auto first_end = std::stable_partition(
        std::begin(xs),
        std::end(xs),
        [] (auto i) {
            return i % 3 == 0;
        }
    );
    std::cout << "first_end: " << *first_end << std::endl;
    for (auto i : xs) std::cout << i << " ";
    std::cout << std::endl;

    // Particionisemo drugi deo kolekcije ->
    // druga grupa ce imati elemente koji daju ostatak 1 pri deljenju sa 3
    const auto second_end = std::stable_partition(
        first_end,
        std::end(xs),
        [] (auto i) {
            return i % 3 == 1;
        }
    );
   
    std::cout << "second_end: " << *second_end << std::endl;
    for (auto i : xs) std::cout << i << " ";
    std::cout << std::endl;

    return 0;
}
