#include <iostream>
#include <vector>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

namespace matf {

template <typename T>
inline T max(T a, T b) {
    return a > b ? a : b;
}

} // namespace matf

int main()
{
    // Testiramo maksimum
    std::cout << matf::max(2, 3) << std::endl;    
    std::cout << matf::max(2.3, 2.4) << std::endl;    
    std::cout << std::max(2, 3) << std::endl;
    return 0;
}
