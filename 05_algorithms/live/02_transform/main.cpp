#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>

bool is_selected(const std::string& item)
{
    return item[0] == '*';
}

int main()
{
    std::vector<std::string> items {
        "aardvark",                                                                                 
        "compunctious",                                                                             
        "**congratulations**",                                                                      
        "contrafribblarity",                                                                        
        "contrary",                                                                                 
        "dictionary",                                                                               
        "**interphrastical**",                                                                      
        "**patronise**",                                                                            
        "**pericombobulation**",                                                                    
        "phrasmotic",                                                                               
        "**syllables**"  
    };

    std::vector<bool> selection_markers(items.size());

    std::transform(
            items.cbegin(),
            items.cend(),
            selection_markers.begin(),
            is_selected
    );

    for (auto i : selection_markers) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    return 0;
}
