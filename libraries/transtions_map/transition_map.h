#pragma once
#include "array.h"
#include "common.h"
typedef void (*taskFunc)();
#define LOOP_ONCE -1
//-----Internals------

template <size_t Size>
struct TransitionMap {
    Array<taskFunc, Size> task_funcs;
    int current_state = 0;
    int add_count = 0;
    TransitionMap(Array<taskFunc, Size> &task) { this->task_funcs = task; }
    TransitionMap() = default;
    ~TransitionMap() = default;

    void setDefaultState(int default_state) { current_state = default_state; }

    void add(int entry_state, int condition, int exit_state) {
        // check if entry state is current state, check if condition is true, if
        // condition true enter exit state
        if (entry_state == current_state && condition == 1) {
            current_state = exit_state;
        }
        if (current_state == entry_state || current_state == exit_state) {
            const auto &task = task_funcs[current_state];
            task();
        }
        if (entry_state == current_state && condition == -1) {
            current_state = exit_state;
        }
    }
};