#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <numeric>

template <typename T>
bool less_then_or_equal(const T& leftie, const T& rightie)
{
    return leftie <= rightie;
}

bool conjunction(bool leftie, bool rightie)
{
    return leftie && rightie;
}

template <typename T, typename Inner = typename T::value_type>
int is_sorted(const T& xs)
{
    return std::inner_product(
        std::begin(xs),
        std::end(xs) - 1,
        std::begin(xs) + 1,
        true,
        conjunction,
        less_then_or_equal<Inner>
    );
}

int main()
{
    std::vector<int> xs(10);
    std::iota(std::begin(xs), std::end(xs), 1);
    auto ys = xs;
    std::random_shuffle(std::begin(ys), std::end(ys));

    std::cout << is_sorted(xs) << std::endl;
    std::cout << is_sorted(ys) << std::endl;

    return 0;
}
