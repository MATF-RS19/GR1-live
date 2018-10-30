// vim: set undofile:
// Program: split

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

std::vector<std::string> split(const std::string & str)
{
    std::vector<std::string> result;

    auto i = str.cbegin();

    // Idemo dok ne stignemo do kraja stringa
    while (i != str.cend()) {

        // Preskacemo razmake sa pocetka
        i = std::find_if_not(i, str.cend(), isspace);

        // Trazimo kraj reci
        auto j = std::find_if(i, str.cend(), isspace);

        // Kopiramo karaktere u izlazni vektor
        if (i != str.cend()) {
            result.push_back(std::string(i, j));
        }

        // Zavrsavamo petlju nastavljajuci od kraja prethodne reci
        i = j;
    }

    return result;
}

int main(int argc, const char *argv[])
{
    const auto message = split("Splitting atoms or strings");

    std::copy(message.cbegin(), message.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}

