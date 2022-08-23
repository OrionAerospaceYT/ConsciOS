#pragma once
#include "common.h"



template <typename R>
struct Iterator 
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = R;
        using pointer           = R*;
        using reference         = R&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }  
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };  

        pointer m_ptr;
    };


//thanks to Martin Starkov for help with the basics of this struct
//assert that size > 1
template <typename T, size_t Size>
struct Array {
    typedef Iterator<T> iterator;
    T data[Size];
    template <typename ...Args>
    constexpr Array(const Args&... args) : data{args...} {}
    constexpr Array() : data{} {}
    T get(int i){
	return data[i];
    }

    operator String(){
	    String ret;
	    for(auto i = 0; i < Size - 1; ++i){
		ret += String(data[i]) + ",";
	    }
	    ret += String(data[Size - 1]);
	    return ret;
    }
    T operator [](int i){
	return data[i];
    }
    iterator begin(){return iterator(&data[0]);} 
    iterator end(){return iterator(&data[Size]);} 

};
