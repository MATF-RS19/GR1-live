#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

template <typename T>
class list {
public:
    list()
    {
    }

    void push_front(T value)
    {
        auto new_element =
            std::make_unique<element>(value, std::move(m_start));
        m_start = std::move(new_element);
        m_size++;
    }

    void push_back(T value)
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

    const T& operator[](size_t index) const
    {
        return at(index)->value;
    }

    T& operator[](size_t index)
    {
        return at(index)->value;
    }

    size_t size() const
    {
        return this->m_size;
    }

    void pop_front()
    {
        auto old_start = std::move(m_start);
        m_start = std::move(old_start->next);
        m_size--;
    }

    // destruktor
    ~list()
    {
        while (m_start) {
            pop_front();
        }
    }

    // operator dodele koji kopira
    list& operator=(const list& other)
    {
        // copy-swap idiom
        auto tmp = other;
        std::swap(tmp.m_start, this->m_start);
        std::swap(tmp.m_size, this->m_size);
        return *this;
    }

    // operator dodele koji preuzima elemente
    list& operator=(list&& other)
    {
        // copy-swap idiom
        std::swap(other.m_start, m_start);
        std::swap(other.m_size, m_size);
        return *this;
    }

    // konstruktor kopije
    list(const list& other)
    {
        for (size_t i = 0; i < other.m_size; ++i)
            push_back(other[i]);
    }
    // move konstruktor
    list(list&& other) : m_start(std::move(other.m_start))
                       , m_size(other.m_size)
    {
        other.m_size = 0;
    }

private:
    class element {
    public:
        element(T value, std::unique_ptr<element>&& next = nullptr)
            : value(value), next(std::move(next))
        {}

        T value;
        std::unique_ptr<element> next;
    };

    std::unique_ptr<element> m_start;
    size_t m_size = 0;

    element* at(size_t index) const
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
};

#endif /* ifndef LIST_HPP */
