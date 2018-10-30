// Program: count_adj_equals

#include <iostream>
#include <string>
#include <numeric>

template <typename T>
bool equal_to(const T& left, const T& right)
{
    return left == right;
}

int plus(int left, int right)
{
    return left + right;
}

template <typename T,
          typename Inner = typename T::value_type> // Ignorisati za sada
int count_adj_equals(const T& xs)
{
    return std::inner_product(std::begin(xs), std::end(xs) - 1,
                              std::begin(xs) + 1,
                              0,
                              plus,
                              equal_to<Inner>);
}

int main(int argc, char *argv[])
{
    std::string colour = "Hooloovoo";

    std::cerr << colour << ": " << count_adj_equals(colour) << std::endl;

    return 0;
}


