// vim: set undofile:
// Program: cont_selection_move

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>


template <typename It>
std::pair<It, It> slide_selection(It selection_begin, It selection_end, It destination)
{
    if (destination < selection_begin) {
        return {
            destination,
            std::rotate(destination, selection_begin, selection_end)
        };
    }

    if (selection_end < destination) {
        return {
            std::rotate(selection_begin, selection_end, destination),
            destination
        };
    }

    return { selection_begin, selection_end };
}


int main(int argc, char *argv[])
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

    const auto [ selection_begin, selection_end ] = // C++17
        slide_selection(std::begin(items) + 2,
                        std::begin(items) + 5,
                        std::begin(items) + 7);

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));


    std::cout << "---" << std::endl;

    slide_selection(selection_begin,
                    selection_end,
                    std::begin(items));

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}
