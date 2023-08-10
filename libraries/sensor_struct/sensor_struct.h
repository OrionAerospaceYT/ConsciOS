#pragma once
#include "array.h"
#include "utility.h"

template <typename T, typename R, size_t Size>
struct SensorGroup : Array<T, Size> {
    Array<T, Size> a;
    Array<R, Size> r;
    template <typename... Args>
    explicit  SensorGroup(const Args &...args){
        a = {args...};
    }
    void init() {
        for (auto i = 0; i < Size; ++i) {
            a.data[i].init();
        }
    }

    Array<R, Size> read() {
        for (auto i = 0; i < Size; ++i) {
            r.data[i] = a.data[i].read();
        }
        return r;
    }
};
