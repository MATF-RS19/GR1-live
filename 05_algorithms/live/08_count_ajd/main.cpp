#include <vector>
#include <iostream>
#include <string>
#include <numeric>

template <typename T>
bool equal_to(const T& left, const T& right)
{
    return left == right;
}

int plus(int a, int b)
{
    return a + b;
}

// T -> std::vector<int>
// Inner -> int
template <typename T, typename Inner = typename T::value_type>
int count_adj_equals(const T& xs)
{
    return std::inner_product(
        std::begin(xs),
        std::end(xs) - 1,
        std::begin(xs) + 1,
        0,
        plus,
        equal_to<Inner>
    );
}

int main()
{
    std::string msg = "aaa__bbcd";
    std::cout << msg << ": " << count_adj_equals(msg) << std::endl;
    return 0;
}
