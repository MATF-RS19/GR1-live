#include <iostream>

int main()
{
    auto x = 10;
    decltype(10) y = 20;
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    return 0;
}
