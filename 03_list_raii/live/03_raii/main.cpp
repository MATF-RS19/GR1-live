#include <iostream>
#include <cstdio>
#include <cstdlib>

void example_c()
{
    FILE* file = fopen("data.txt", "r");
    int x;
    fscanf(file, "%d", &x);
    // ---
    // koristi se datoteka
    // ---
    fclose(file);
}

class file_reader {
public:
    file_reader(std::string path) {
        std::cout << "Otvaramo datoteku" << std::endl;
        m_file = fopen(path.c_str(), "r");
        
        std::cout << "Citamo datoteku..." << std::endl;
        // ...
        std::cout << "Gotovo citanje ..." << std::endl;
    }

    ~file_reader() {
        std::cout << "Zatvaramo datoteku" << std::endl;
        fclose(m_file);
    }

private:
    FILE* m_file;
};

int main()
{
    file_reader reader("input.txt");
}
