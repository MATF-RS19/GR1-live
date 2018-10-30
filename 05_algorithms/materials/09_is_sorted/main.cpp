// Program: is_sorted

#include <iostream>
#include <string>
#include <numeric>

// std::is_sorted je efikasniji - raniji izlazak iz funkcije

template <typename T>
bool less_than_or_equal(const T& left, const T& right)
{
    return left <= right;
}

bool conjunction(bool left, bool right)
{
    return left && right;
}

template <typename T,
          typename Inner = typename T::value_type> // Ignorisati za sada
int is_sorted(const T& xs)
{
    return std::inner_product(std::begin(xs), std::end(xs) - 1,
                              std::begin(xs) + 1,
                              true,
                              conjunction,
                              less_than_or_equal<Inner>);
}

int main(int argc, char *argv[])
{
    std::string colour = "Hooloovoo";
    std::string word = "Almost";

    std::cerr << colour << ": " << is_sorted(colour) << std::endl;
    std::cerr << word << ": " << is_sorted(word) << std::endl;

    return 0;
}


