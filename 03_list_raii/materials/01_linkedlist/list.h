
#ifndef MATF_LIST_H
#define MATF_LIST_H

#include <utility>
#include <memory>

class list {
public:
    list();

    void push_front(int value);

    void push_back(int value);

    int operator[] (size_t index) const;

    int& operator[] (size_t index);

    size_t size() const;


    // Implementacija do sad ima dva problema:
    //   Nije moguce kopirati listu zbog upotrebe unique_ptr,
    //   i uništavanje liste može da probjie stek zbog
    //   rekurzivnih poziva prilikom unistavanja elemenata

    void pop_front();

    // Kad god se napravi destruktor, obavezno je napraviti
    // i konstruktor kopije i operator dodele (rule of 3),
    // ili ih eksplicitno izbrisati ( = delete ),
    // a pozeljno je napraviti i /move/ konstruktor i /move/
    // operator dodele (rule of 5)
    ~list();

    // konstruktor kopije:
    list(const list& other);

    // move konstruktor
    list(list&& other);

    // operator dodele koji pravi kopiju podataka
    list& operator= (const list& other);

    // operator dodele koji krade podatke iz izvorne kolekcije
    list& operator= (list&& other);



private:
    struct element {
        element(int value = 0, std::unique_ptr<element>&& next = nullptr);

        int value;
        std::unique_ptr<element> next;
    };

    element* at(size_t index) const;

    std::unique_ptr<element> m_start;
    size_t m_size = 0;
};


#endif /* !MATF_LIST_H */
