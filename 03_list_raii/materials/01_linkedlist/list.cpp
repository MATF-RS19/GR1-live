
#include "list.h"

list::list()
{
}

void list::push_front(int value)
{
    auto new_element =
        std::make_unique<element>(value,
                std::move(m_start));
    m_start = std::move(new_element);

    m_size++;
}

void list::push_back(int value)
{
    auto new_element = std::make_unique<element>(value);

    if (!m_start) {
        m_start = std::move(new_element);
    } else {
        auto e = m_start.get();

        while (e->next) {
            e = e->next.get();
        }

        e->next = std::move(new_element);
    }

    m_size++;
}

int list::operator[] (size_t index) const
{
    return at(index)->value;
}

int& list::operator[] (size_t index)
{
    return at(index)->value;
}

size_t list::size() const
{
    return m_size;
}


// Implementacija iznad ima dva problema:
//   Nije moguce kopirati listu zbog upotrebe unique_ptr,
//   i uništavanje liste može da probjie stek zbog
//   rekurzivnih poziva prilikom unistavanja elemenata

void list::pop_front()
{
    auto old_start = std::move(m_start);
    m_start = std::move(old_start->next);
    m_size--;
}

// Kad god se napravi destruktor, obavezno je napraviti
// i konstruktor kopije i operator dodele (rule of 3),
// a pozeljno je napraviti i /move/ konstruktor i /move/
// operator dodele (rule of 5)
list::~list()
{
    while (m_start) {
        pop_front();
    }
}

// konstruktor kopije:
list::list(const list& other)
{
    // Uzasna efikasnost:
    for (size_t i = 0; i < other.m_size; ++i) {
        push_back(other[i]);
    }
}

// move konstruktor
list::list(list&& other)
    : m_start(std::move(other.m_start))
    , m_size(other.m_size)
{
    other.m_size = 0;
}

// operator dodele koji pravi kopiju podataka
list& list::operator= (const list& other)
{
    // copy-and-swap idiom - da bi operator dodele bio
    // bezbedan prilikom pojave izuzetaka, obavezno je
    // implementirati ga na ovaj nacin:
    // 1. Pravi se privremena kopija objekta (poziva se
    //    konstruktor kopije)
    // 2. Zamene se sve clanske promenljive u *this i
    //    privremenoj kopiji
    auto temp = other;
    std::swap(temp.m_start, m_start);
    std::swap(temp.m_size, m_size);
    return *this;
}

// operator dodele koji krade podatke iz izvorne kolekcije
list& list::operator= (list&& other)
{
    // Ova implementacija je potencijalno problemticna.
    // Lista other ce imati sadrzaj koji je prethodno
    // bio u *this listi.
    // Zvanicno, objekti iz kojih su podaci ukradeni
    // mogu da se ostave u neodredjenom stanju,
    // ali bi verovatno bilo bolje ostaviti other listu
    // praznu
    std::swap(other.m_start, m_start);
    std::swap(other.m_size, m_size);
    return *this;
}

list::element::element(int value, std::unique_ptr<list::element>&& next)
    : value(value)
    , next(std::move(next))
{
}

list::element* list::at(size_t index) const
{
    if (!m_start) {
        return nullptr;
    }

    auto e = m_start.get();

    for (size_t i = 0; i < index; ++i) {
        e = e->next.get();

        if (!e) {
            return nullptr;
        }
    }

    return e;
}


