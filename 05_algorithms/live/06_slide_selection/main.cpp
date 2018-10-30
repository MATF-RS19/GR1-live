#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>
#include <iostream>

template <typename It>
std::pair<It, It> slide_selection(It selection_begin, It selection_end, It destination)
{
    // Da li pomeramo na levu stranu
    if (destination < selection_begin) {
        return {
            destination,
            std::rotate(destination, selection_begin, selection_end)
        };
    }
    
    // Da li pomeramo na desnu stranu
    if (selection_end < destination) {
        return {
            std::rotate(selection_begin, selection_end, destination),
            destination
        };
    }

    return { selection_begin, selection_end };
}

int main()
{
    std::vector<std::string> items {
        "aardvark",                                                                                 
        "compunctious",                                                                             
        "**congratulations**",  // +2                                                               
        "**contrafribblarity**",                                                                    
        "**contrary**",                                                                             
        "dictionary",           // +5                                                               
        "interphrastical",                                                                          
        "patronise",            // +7                                                               
        "pericombobulation",                                                                        
        "phrasmotic",                                                                               
        "syllables"        
    };

    // Pomeramo elemente u desno na iterator (std::begin(items) + 7)
    const auto [selection_begin, selection_end] = slide_selection(
        std::begin(items) + 2,
        std::begin(items) + 5,
        std::begin(items) + 7
    );
    for (auto i : items) std::cout << i << std::endl;
    std::cout << "-------" << std::endl;

    slide_selection(selection_begin, selection_end, std::begin(items));
    for (auto i : items) std::cout << i << std::endl;
}
