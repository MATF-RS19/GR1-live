#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

namespace matf {

template <typename T>
inline T max(T a, T b) {
    return a > b ? a : b;
}

template <typename ForwardIterator, typename T>
void iota(ForwardIterator begin, ForwardIterator end, T value)
{
    while (begin != end) *begin++ = value++;
}

template <typename ForwardIterator, typename T>
T accumulate(ForwardIterator first, ForwardIterator last, T init)
{
    for (; first != last; ++first) {
        init = std::move(init) + *first;
    }
    return init;
}

template <typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
    if (first == last) return last;

    ForwardIterator largest = first;
    ++first;
    for (; first != last; ++first) {
        if (*largest < *first) {
            largest = first;
        }
    }
    return largest;
}

} // namespace matf

int main()
{
    // Testiramo maksimum
    std::cout << matf::max(2, 3) << std::endl;    
    std::cout << matf::max(2.3, 2.4) << std::endl;    
    std::cout << std::max(2, 3) << std::endl;

	std::vector<int> v(10);
    matf::iota(v.begin(), v.end(), 1);
    for (const auto& i : v) {
        std::cout << i << std::endl;
    }

    std::cout << "Suma: " << std::accumulate(v.begin(), v.end(), 0) << std::endl;
    std::cout << "Suma: " << matf::accumulate(v.begin(), v.end(), 0) << std::endl;

    return 0;
}
