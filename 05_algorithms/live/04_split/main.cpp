#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

std::vector<std::string> split(const std::string& str)
{
    std::vector<std::string> result;
    auto i = str.cbegin();

    while (i != str.cend()) {
        // Preskacemo razmake sa pocetka
        i = std::find_if_not(i, str.cend(), isspace);

        // trazimo kraj reci
        auto j = std::find_if(i, str.cend(), isspace);

        // kopiramo karaktere u izlazni vektor
        if (i != str.cend()) {
            result.push_back(std::string(i, j));
        }

        i = j;
    }

    return result;
}

int main()
{
    std::string msg = "Splitting atoms or strings";     
    const auto elements = split(msg);
    for (auto i : elements) {
        std::cout << i << std::endl;
    }
    return 0;
}
