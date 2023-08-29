#pragma once
#include "utility.h"
//#include "skServo.h"

template <typename R>
struct Iterator {
    using value_type = R;
    using pointer = R *;
    using reference = R &;

    explicit Iterator(pointer ptr){ m_ptr = ptr; }

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    Iterator &operator++() {
        m_ptr++;
        return *this;
    }
    Iterator operator++(int) {
        Iterator tmp = *this;
        ++(*this);
        return tmp;
    }
    friend bool operator==(const Iterator &a, const Iterator &b) {
        return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const Iterator &a, const Iterator &b) {
        return a.m_ptr != b.m_ptr;
    };

    pointer m_ptr;
};

// thanks to Martin Starkov for help with the basics of this struct
// assert that size > 1
template <typename T, size_t Size>
struct Array {
    typedef Iterator<T> iterator;
    T data[Size];
    template <typename... Args>
    explicit constexpr Array(const Args &...args) : data{args...}{}
    constexpr Array() : data{} {}
    T get(int i) {
        if (i < 0 || i > Size) {
            sk_warn(i < 0 || i > Size, "Invalid Array Element")
            return data[Size];
        } else {
            return data[i];
        }
    }
    int len() {
        return Size;
    }
    operator String() {
        String ret;
        for (auto i = 0; i < Size - 1; ++i) {
            ret += String(data[i]) + ",";
        }
        ret += String(data[Size - 1]);
        return ret;
    }
    T operator[](int i) {
        if (i < 0 || i > Size) {
            sk_warn(i < 0 || i > Size, "Invalid Array Element")
            return data[Size];
        } else {
            return data[i];
        }
    }
    iterator begin() { return iterator(&data[0]); }
    iterator end() { return iterator(&data[Size]); }
};

//template <size_t Size>
//struct skArray {
//    typedef Iterator<skServo*> iterator;
//    skServo* data[Size];
//    template <typename... Args>
//    explicit  skArray(Args ...args): data{args...}{}
//    skServo get(int i) {
//        if (i < 0 || i > Size) {
//            sk_warn(i < 0 || i > Size, "Invalid Array Element")
//            return data[Size];
//        } else {
//            return data[i];
//        }
//    }
//    int len() {
//        return Size;
//    }
//    operator String() {
//        String ret;
//        for (auto i = 0; i < Size - 1; ++i) {
//            ret += String(data[i]) + ",";
//        }
//        ret += String(data[Size - 1]);
//        return ret;
//    }
//    skServo operator[](int i) {
//        if (i < 0 || i > Size) {
//            sk_warn(i < 0 || i > Size, "Invalid Array Element")
//            return data[Size];
//        } else {
//            return data[i];
//        }
//    }
//    iterator begin() { return iterator(&data[0]); }
//    iterator end() { return iterator(&data[Size]); }
//};
