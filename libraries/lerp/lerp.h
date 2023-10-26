#pragma once 
#include "sk_math.h"
#include "array.h"
#include "actuator_struct.h"

#define SMOOTH 1
#define LINEAR 0

template<size_t Size>
struct Lerp{
    float lerp_values[2*Size] = {};
    float current_values[Size] = {};
    float increment_values[Size] = {};
    int type = 0;
    int counter = 0;
    float smooth_start = 0;
    float current_smooth = 0;
    float smooth_max = 0;
    float increment = 0;
    float interp_points = 100; //We default to 100 interpolation points

    template <typename ...Args>
    explicit  Lerp(const Args&... args) : lerp_values{args...} {
        for(int i = 0; i < Size; ++i){
            current_values[i] = 0.0f;
        }
    }
    Lerp(float start, float end, float interp_points){
      smooth_start = start;
      smooth_max = end;
      increment = (smooth_max - smooth_start)/interp_points;
    }
    void setResolution(float interp_points){
        interp_points = interp_points;
    }

    template <typename ActuatorGroup>
    bool writeAll(ActuatorGroup* a){
        for(int i = 0; i < a->len(); ++i){
            float current_smooth = current_values[i];
            float smooth_start = lerp_values[2*i];
            float smooth_max = lerp_values[2*i + 1];
            float interp_point = sk_math::MAP(current_smooth,smooth_start,smooth_max,0.0f,1.0f);
            increment = (smooth_max - smooth_start)/interp_points;
            float output = 0.0f;
            if(type == 0){
                output = smooth_start + sk_math::LERP(smooth_start,smooth_max,interp_point);
            }
            if(type == 1){
                output = smooth_start + sk_math::SMOOTHLERP(smooth_start,smooth_max,interp_point);
            }
            if(!sk_math::ISCLOSE(output,smooth_max,0.1f)){
                current_values[i] +=increment;
                a->write(i,output);
            }
        }
        return false;
    }

    template <typename actuator>
    bool write(actuator* a){
      float interp_point = sk_math::MAP(current_smooth,smooth_start,smooth_max,0.0f,1.0f);
      float output = 0.0f;
      if(type == 0){
          output = sk_math::LERP(smooth_start,smooth_max,interp_point);
      }
      if(type == 1){
          output = sk_math::SMOOTHLERP(smooth_start,smooth_max,interp_point);
      }
      if(sk_math::ISCLOSE(output,smooth_max,0.001f)){
          return true;
      }
      current_smooth += increment;
      a->write(output);
      GRAPH("lerp",output,TOP);
      return false;
    }
    
};
/*
    // This function must be called to enable lerpWrite
    // Parameters include the starting position, end position, and the number of interpolation steps to take
    void initLerp(float start, float end, float interp_points){
    }

    // actuator_number is the actuator to move and type is the type of interpolation to use
*/
