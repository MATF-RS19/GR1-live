// vim: set undofile:
// Program: 01_counting

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>


// Stavka je selektovana ako pocinje zvezdom
bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

// Dat nam je predikat kojim testiramo da li je stavka selektovana.
// Cilj je da pomerimo sve selektovane elemente u kolekciji na
// mesto na koje pokazuje iterator destination
template <typename It, typename Pred>
void move_selection(It first, It last, It destination, Pred predicate)
{
    // Problem mozemo da razdvojimo na dva dela:
    //  - Particionisemo deo kolekcije od pocetka do destination iteratora,
    //    u ovom delu zelimo da pomerimo selektovane elemente na kraj
    //  - Particionisemo deo kolekcije od destination iteratora do kraja,
    //    ovde zelimo da pomerimo selektovane elemente na pocetak
    std::stable_partition(first, destination,
                          [predicate] (const auto &item) { return !predicate(item); });
    std::stable_partition(destination, last,
                          predicate);
}


int main(int argc, char *argv[])
{
    std::vector<std::string> items {
            "aardvark",
            "compunctious",
            "**congratulations**",
            "contrafribblarity",
            "contrary",
            "dictionary",
            "**interphrastical**",
            "**patronise**",
            "**pericombobulation**",
            "phrasmotic",
            "**syllables**"
        };

    move_selection(
            std::begin(items), std::end(items), std::begin(items) + 5,
            is_selected
        );

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}
