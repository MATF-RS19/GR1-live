#include "list.hpp"

list::list()
{
}

// kopiramo other u this
list::list(const list& other)
{
    // this je duzine n, other je duzine m
    
    for (size_t i = 0; i < other.m_size; ++i)
        push_back(other[i]);
    // Slozenost: ?
    // O(n*m)
}

list::list(list&& other)
    : m_start(std::move(other.m_start))
    , m_size(other.m_size)
{
    other.m_size = 0;
}

list::~list()
{
    while (m_start) {
        pop_front();
    }
}

int list::operator[](size_t index) const
{
    return at(index)->value;
}

int& list::operator[](size_t index) 
{
    return at(index)->value;
}

list& list::operator=(const list& other)
{
    // copy-swap idiom
    auto tmp = other;
    std::swap(tmp.m_start, this->m_start);
    std::swap(tmp.m_size, this->m_size);
    return *this;
}

list& list::operator=(list&& other)
{
    // copy-swap idiom
    std::swap(other.m_start, m_start);
    std::swap(other.m_size, m_size);
    return *this;
}

list::element::element(int value, std::unique_ptr<element>&& next)
    : value(value)
    , next(std::move(next))
{
}

size_t list::size() const
{
	return m_size;
}

void list::pop_front()
{
    auto old_start = std::move(m_start);
    m_start = std::move(old_start->next);
    m_size--;
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

    ++m_size;
}

void list::push_front(int value)
{
    auto new_element =
        std::make_unique<element>(value, std::move(m_start));
    m_start = std::move(new_element);
    m_size++;
}

list::element* list::at(size_t index) const
{
    if (!m_start) {
        return nullptr;
    }

    auto e = m_start.get();
    for (size_t i = 0; i < index; ++i) {
        e = e->next.get();
        if (! e) return nullptr;
    }

    return e;
}
