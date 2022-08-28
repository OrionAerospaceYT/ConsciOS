#pragma once


//-----Internals------
#include "./Libraries/common.h"
#include "./Libraries/array.h"
#include "task.h"
typedef void (*taskFunc)();
#define LOOP_ONCE -1
//-----Internals------


//Transition map 
//STATE CONDITION STATE
//STATE CONDITION STATE 
// ..
//Default STATE 

//function that takes in state condition state 
//internal two column array that takes in the states 
//internal array that contains the condition and is linked to the states array 

template <size_t Size>
struct TransitionMap{
    Array<taskFunc,Size> task_funcs;
    int current_state = -1; 
    int add_count = 0;
    bool default_flag = true;
    TransitionMap(const Array<taskFunc,Size> &task_funcs) : task_funcs(task_funcs) {}
    TransitionMap() = default;
    ~TransitionMap() = default;

    void setDefaultState(int default_state){
        current_state = default_state;
    }

    void add(int entry_state, bool condition, int exit_state){
        //check if entry state is current state, check if condition is true, if condition true enter exit state
        if(entry_state == current_state && condition == 1){
           current_state = exit_state;
        }

        auto task = task_funcs[current_state];
        task();

        if(entry_state == current_state && condition == -1){
            current_state += 1;
        }
    }
};


//You can change the Tasks in here, but make sure to follow the naming convention
//These are the set of tasks our robot will complete (Note: this does not specify the order)
enum Task{Setup,ActuatorTest,Calibration,Loop};
const int TASK_COUNT = 4;
Array<taskFunc,TASK_COUNT> TaskFlow(task::Setup,task::ActuatorTest,task::Calibration,task::Loop);
TransitionMap<TASK_COUNT> transition_map(TaskFlow);
void defau(){
    transition_map.setDefaultState(Setup);
}
void taskSchedule(){
    transition_map.add(Setup,LOOP_ONCE, Loop);
}
