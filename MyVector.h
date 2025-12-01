#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>

template<typename T>
class MyVector {
    T* data;
    size_t cap;
    size_t length;

public:
    MyVector(std::initializer_list<T> init) {
        length = init.size();
        cap = (length == 0 ? 1 : length);
        data = new T[cap];
        size_t i = 0;
        for (const auto& val : init) data[i++] = val;
    }

    MyVector() : data(nullptr), cap(0), length(0) {}
    ~MyVector() { delete[] data; }

    void push_back(const T& val);
    void pop_back();
    size_t size() const;
    size_t capacity() const { return cap; }
    bool empty() const { return length == 0; }
    T& operator[](int i) { return data[i]; }

    bool operator==(const MyVector& other) const;
    bool operator!=(const MyVector& other) const;
    bool operator<(const MyVector& other) const;
    bool operator>(const MyVector& other) const;
    bool operator<=(const MyVector& other) const;
    bool operator>=(const MyVector& other) const;

    class Iterator {
    public:
        T* ptr;
        Iterator(T* p = nullptr) : ptr(p) {}
        T& operator*() { return *ptr; }
        Iterator& operator++() { ptr++; return *this; }
        Iterator& operator--() { ptr--; return *this; }
        Iterator operator+(int n) const { return Iterator(ptr + n); }
        Iterator operator-(int n) const { return Iterator(ptr - n); }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        int operator-(const Iterator& other) const { return ptr - other.ptr; }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + length); }

    Iterator insert(Iterator pos, const T& value);
    void insert(size_t pos, const T& value);
    Iterator erase(Iterator pos);

    void clear() { length = 0; }
    T& at(size_t i) {
        if (i >= length) throw std::out_of_range("Index out of range");
        return data[i];
    }

    T& front() { return data[0]; }
    T& back() { return data[length - 1]; }
};
