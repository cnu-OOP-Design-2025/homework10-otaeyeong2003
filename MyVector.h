#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>

template<typename T>
class MyVector {

    T* data;
    size_t len;
    size_t cap;

public:

    MyVector() : data(nullptr), len(0), cap(0) {}

    MyVector(std::initializer_list<T> init) {
        len = init.size();
        cap = (len == 0 ? 1 : len);
        data = new T[cap];
        int i = 0;
        for (auto v : init) {
            data[i] = v;
            i++;
        }
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& v) {
        if (len == cap) {
            size_t newcap;
            if (cap == 0) newcap = 1;
            else newcap = cap * 2;

            T* tmp = new T[newcap];
            for (size_t k = 0; k < len; k++) {
                tmp[k] = data[k];
            }
            delete[] data;
            data = tmp;
            cap = newcap;
        }
        data[len] = v;
        len++;
    }

    void pop_back() {
        if (len > 0) {
            len = len - 1;
        }
    }

    size_t size() const {
        return len;
    }

    bool empty() const {
        return len == 0;
    }

    T& operator[](int i) {
        return data[i];
    }

    T& at(size_t index) {
        if (index >= len) throw std::out_of_range("range");
        return data[index];
    }

    T& front() {
        return data[0];
    }

    T& back() {
        return data[len-1];
    }

    bool operator==(const MyVector& o) const {
        if (len != o.len) return false;
        for (size_t i = 0; i < len; i++)
            if (data[i] != o.data[i]) return false;
        return true;
    }

    bool operator!=(const MyVector& o) const {
        return !(*this == o);
    }

    bool operator<(const MyVector& o) const {
        size_t m;
        if (len < o.len) m = len;
        else m = o.len;

        for (size_t i = 0; i < m; i++) {
            if (data[i] < o.data[i]) return true;
            if (data[i] > o.data[i]) return false;
        }
        return len < o.len;
    }

    bool operator>(const MyVector& o) const {
        return o < *this;
    }

    bool operator<=(const MyVector& o) const {
        return !(*this > o);
    }

    bool operator>=(const MyVector& o) const {
        return !(*this < o);
    }

    class Iterator {
    public:
        T* ptr;

        Iterator(T* p = nullptr) : ptr(p) {}

        T& operator*() { return *ptr; }

        Iterator& operator++() {
            ptr++;
            return *this;
        }

        Iterator& operator--() {
            ptr--;
            return *this;
        }

        Iterator operator+(int n) const {
            return Iterator(ptr+n);
        }

        Iterator operator-(int n) const {
            return Iterator(ptr-n);
        }

        bool operator==(const Iterator& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }

        int operator-(const Iterator& other) const {
            return ptr - other.ptr;
        }
    };

    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + len); }

    Iterator insert(Iterator pos, const T& v) {
        size_t idx = pos.ptr - data;
        if (len == cap) {
            size_t tmpcap = (cap == 0 ? 1 : cap*2);
            T* arr = new T[tmpcap];
            for (size_t i = 0; i < len; i++)
                arr[i] = data[i];
            delete[] data;
            data = arr;
            cap = tmpcap;
        }
        for (size_t i = len; i > idx; i--) {
            data[i] = data[i-1];
        }
        data[idx] = v;
        len++;
        return Iterator(data + idx);
    }

    Iterator erase(Iterator pos) {
        size_t idx = pos.ptr - data;
        for (size_t i = idx; i < len - 1; i++) {
            data[i] = data[i+1];
        }
        len--;
        return Iterator(data + idx);
    }

    void clear() {
        len = 0;
    }
};

