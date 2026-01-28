
#ifndef ARRAY_H
#define ARRAY_H
#include <memory>
#include <initializer_list>
#include "Exceptions.h"
#include "Sorting.h"

template<typename T>
class Array {
    private:
        std::unique_ptr<T[]> storage;
        size_t size, capacity;

        void ResizeStorage();

    public:
        using iterator = T*;
        using const_iterator = const T*;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;

        Array();

        explicit Array(const size_t capacity);

        Array(Array &arr);

        Array(Array &&arr) noexcept;

        Array(std::initializer_list<T> list);

        ~Array() = default;

        Array<T> &operator=(const Array<T> &arr);

        Array<T> &operator=(Array<T> &&arr) noexcept;

        T &operator[](int index);;

        size_t Size() const;

        size_t Capacity() const;

        void push_back(T element);


        T &pop_back();

        void Sort();

        bool IsEmpty();

        size_t Find(T element);

        void Save(const std::string& filename) const;
        void Load(const std::string& filename);

class Iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        Iterator(T* p) :ptr(p){};

        reference operator*() const {return *ptr;};
        pointer operator->() const {return ptr;};

        Iterator& operator++(){ptr++; return *this;}
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        Iterator& operator--(){ptr--; return *this;}
        Iterator& operator--(int) {Iterator tmp = *this; ptr--; return tmp;}

        Iterator operator+(int n) const {return Iterator(ptr + n);}
        Iterator operator-(int n) const {return Iterator(ptr - n);}

        difference_type operator-(const Iterator &other) const {return ptr - other.ptr;};

        bool operator==(const Iterator &other) const {return ptr == other.ptr;};
        bool operator!=(const Iterator &other) const {return ptr != other.ptr;};
        bool operator<(const Iterator &other) const {return ptr < other.ptr;};
        bool operator>(const Iterator &other) const {return ptr > other.ptr;};

};

};

#include "../src/Array.tpp"
#endif
