#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

std::string append_if_odd(const std::string& acc, int x)
{
    if (x % 2 != 0)
        return acc + std::to_string(x);
    else
        return acc;
}

int main()
{
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);

    auto r = std::accumulate(v.cbegin(), v.cend(), std::string(), append_if_odd);
    std::cout << r << std::endl;

    return 0;
}
