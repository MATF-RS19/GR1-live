#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>

void string_to_lower(std::string& str)
{
    std::transform(str.begin(), str.end(), str.begin(), tolower);
}

class compare_ignorecase {
public:
    bool operator() (std::string left, std::string right) const
    {
        string_to_lower(left);
        string_to_lower(right);
        return left < right;
    }
};

int main()
{
    std::ifstream in("words", std::ifstream::in);

    std::string word;
    std::string definition;

    std::map<std::string, std::string, compare_ignorecase> words;

    while (in >> word) {
        std::getline(in, definition);
        words[word] = definition;
    }

    //for (const auto& p: words)
        //std::cout << p.first << " -> " << p.second << std::endl;
    
    std::string query;
    while (std::cin >> query) {
        auto lower = words.lower_bound(query); 
        query[query.size() - 1]++;
        // (*query.rbegin())++;
        auto upper = words.lower_bound(query);
        for (; lower != upper; lower++) {
            std::cout << lower->first << "->" << lower->second << std::endl;
        }
    }

    return 0;
}
