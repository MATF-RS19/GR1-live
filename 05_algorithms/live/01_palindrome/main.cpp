#include <iostream>
#include <algorithm>
#include <string>

bool is_palindrome(const std::string& str)
{
    //return std::equal(str.begin(), str.end(), str.rbegin());
    //return std::equal(str.cbegin(), str.cend(), str.crbegin());
    return std::equal(str.cbegin(), str.cend(), str.crbegin(), str.crend());
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " rec" << std::endl;
        return 1;
    }

    std::cout
        << argv[1]
        << (is_palindrome(argv[1]) ? " jeste" : " nije")
        << " palindrom."
        << std::endl;

    return 0;
}
