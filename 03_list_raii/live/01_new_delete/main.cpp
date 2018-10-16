#include <iostream>
#include <vector>
#include <memory>

int main(void)
{
    std::unique_ptr<std::vector<int>> xs;
    xs = std::make_unique<std::vector<int>>();

    xs->push_back(10);
    xs->push_back(20);
    xs->push_back(30);

    for (const auto& v: *xs) {
        std::cout << v << std::endl;
    }

    return 0;
}
