#include "MyVector.h"
#include <stdexcept>

template<typename T>
void MyVector<T>::push_back(const T& val) {
    if (length == cap) {
        size_t newcap = (cap == 0 ? 1 : cap * 2);
        T* newdata = new T[newcap];
        for (size_t i = 0; i < length; i++)
            newdata[i] = data[i];
        delete[] data;
        data = newdata;
        cap = newcap;
    }
    data[length++] = val;
}

template<typename T>
void MyVector<T>::pop_back() {
    if (length == 0) return;
    --length;
}


template<typename T>
typename MyVector<T>::Iterator MyVector<T>::insert(Iterator pos, const T& value) {
    size_t index = pos.ptr - data;
    insert(index, value);
    return Iterator(data + index);
}

template<typename T>
void MyVector<T>::insert(size_t pos, const T& value) {
    if (pos > length) return;
    if (length == cap) {
        size_t newcap = (cap == 0 ? 1 : cap * 2);
        T* newdata = new T[newcap];
        for (size_t i = 0; i < length; i++)
            newdata[i] = data[i];
        delete[] data;
        data = newdata;
        cap = newcap;
    }
    for (size_t i = length; i > pos; i--)
        data[i] = data[i - 1];
    data[pos] = value;
    length++;
}

template<typename T>
typename MyVector<T>::Iterator MyVector<T>::erase(Iterator pos) {
    size_t index = pos.ptr - data;
    for (size_t i = index; i < length - 1; i++)
        data[i] = data[i + 1];
    --length;
    return Iterator(data + index);
}

template<typename T>
bool MyVector<T>::operator==(const MyVector& other) const {
    if (length != other.length) return false;
    for (size_t i = 0; i < length; i++)
        if (data[i] != other.data[i]) return false;
    return true;
}

template<typename T>
bool MyVector<T>::operator!=(const MyVector& other) const {
    return !(*this == other);
}

template<typename T>
bool MyVector<T>::operator<(const MyVector& other) const {
    size_t minlen = length < other.length ? length : other.length;
    for (size_t i = 0; i < minlen; i++) {
        if (data[i] < other.data[i]) return true;
        if (data[i] > other.data[i]) return false;
    }
    return length < other.length;
}

template<typename T>
bool MyVector<T>::operator>(const MyVector& other) const {
    return other < *this;
}

template<typename T>
bool MyVector<T>::operator<=(const MyVector& other) const {
    return !(*this > other);
}

template<typename T>
bool MyVector<T>::operator>=(const MyVector& other) const {
    return !(*this < other);
}

