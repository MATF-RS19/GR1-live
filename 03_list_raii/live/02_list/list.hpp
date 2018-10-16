#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

class list {
public:
    list();
    void push_front(int value);
    void push_back(int value);
    int operator[](size_t index) const;
    int& operator[](size_t index);
    size_t size() const;
    void pop_front();

    // destruktor
    ~list();

    // operator dodele koji kopira
    list& operator=(const list& other);
    // operator dodele koji preuzima elemente
    list& operator=(list&& other);

    // konstruktor kopije
    list(const list& other);
    // move konstruktor
    list(list&& other);

private:
    class element {
    public:
        element(int value = 0, std::unique_ptr<element>&& next = nullptr);

        int value;
        std::unique_ptr<element> next;
    };

    std::unique_ptr<element> m_start;
    size_t m_size = 0;

    element* at(size_t index) const;
};

#endif /* ifndef LIST_HPP */
