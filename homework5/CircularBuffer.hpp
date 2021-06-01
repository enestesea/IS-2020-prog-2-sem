#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
class CircularBuffer;

template <typename T>
class Iterator {
private:
    T *current;
    T *elements;
    T capacity;
public:
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = T;
    using pointer = T*;
    using reference = T&;
    Iterator(T *current, T *elements, T capacity) : current(current), elements(elements), capacity(capacity) {};

    Iterator& operator = (const Iterator &other) {
        current = other.current;
        elements = other.elements;
        capacity = other.capacity;
        return *this;
    };

    bool operator == (const Iterator &other) const {
        return current == other.current;
    };

    bool operator != (const Iterator &other) const {
        return !(*this == other);
    };

    reference operator*() const {
        return *current;
    };

    Iterator& operator ++ () {
        current++;
        if (current == elements + capacity) {
            current = elements;
        }
        return *this;
    };

    Iterator& operator -- () {
        if (current == elements)
            current = elements + capacity - 1;
        current--;
        return *this;
    };

    difference_type operator - (Iterator const &other) const {
        if (*this < other)
            return (capacity + current - other.current);
        return current - other.current;
    };

    Iterator& operator += (int x) {
        x %= capacity;
        if (current + x < elements + capacity)
            current += x;
        else
            current += x - capacity;
        return *this;
    };

    Iterator& operator -= (int x) {
        x %= capacity;
        if (current - x < elements)
            current += capacity - x;
        else
            current -= x;
        return *this;
    };

    bool operator < (Iterator const &other) const {
        return current < other.current;
    };

    bool operator > (Iterator const &other) const {
        return current > other.current;
    };
};

template <typename T>
Iterator <T> operator - (const Iterator <T> &el, int x) {
    Iterator <T> res = el;
    res -= x;
    return res;
};

template <typename T>
Iterator <T> operator + (const Iterator <T> &el, int x) {
    Iterator <T> res = el;
    res += x;
    return res;
};

template <typename T>
class CircularBuffer {
    friend class Iterator<T>;

private:
    T *elements;
    int capacity;
    int size = 0;
    int begin_ = 0;

public:
    explicit CircularBuffer(int new_capacity) : capacity(new_capacity + 1) {
        elements = new T[capacity];
        };

    CircularBuffer& operator = (const CircularBuffer &other) {
        if (this == &other)
            return *this;
        delete[] elements;
        elements = new T[capacity];
        capacity = other.capacity;
        size = other.size;
        begin_ = other.begin_;
        for (int i = 0; i < capacity; i++) {
            elements[i] = other.elements[i];
        }
        return *this;
        };
    ~CircularBuffer(){
        delete[] elements;
        };

    T operator [] (int i) const {
        return elements[(begin_ + i) % capacity];
        };

    T& operator [] (int i){
        if (size == 0 || i >= size)
            throw out_of_range(" out of range");
        return elements[(begin_ + i) % capacity];
        };

    T first(){
        return elements[begin_];
        };

    T last(){
        return elements[(begin_ + size - 1) % capacity];
        };

    void addFirst(T x) {
        if (size == 0)
            elements[0] = x;
        else {
            begin_ = (begin_ - 1 + capacity) % capacity;
            elements[begin_] = x;
            }
        size++;
        if (size >= capacity)
            size--;
    };

    void addLast(T x) {
        if (size == 0)
            elements[0] = x;
        else
            elements[(begin_ + size) % capacity] = x;
        size++;
        if (size >= capacity)
            size--;
    };

    void delFirst() {
        if (size == 1)
            begin_ = 0;
        else
            begin_ = (begin_ + 1) % capacity;
        size--;
    };

    void delLast() {
        if (size == 1)
            begin_ = 0;
        size--;
    };

    Iterator <T> begin() const {
        return Iterator <T>(elements + begin_, elements, capacity);
    };

    Iterator <T> end() const {
        return Iterator <T>(elements + (begin_ + size) % capacity, elements, capacity);
    };

    void changeCapacity(int capcity_) {
        T *elements_ = new T[capcity_ + 1];
        for (int i = 0; i < capacity; i++) {
            elements_[i] = elements[i];
        }
        delete[] elements;
        elements = elements_;
        capacity = capcity_ + 1;
    };


};
#endif
