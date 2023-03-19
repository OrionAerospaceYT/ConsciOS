#pragma once 
#include "sk_math.h"
#include "Array.h"
#include "actuator_struct.h"

#define SMOOTH 1
#define LINEAR 0

template<size_t Size>
struct Lerp{
    Array<float,2*Size> lerp_values;
    Array<float,Size> current_values;
    int type = 0;
    float smooth_start = 0;
    float current_smooth = 0;
    float smooth_max = 0;
    float increment = 0;

    template <typename ...Args>
    explicit  Lerp(const Args&... args, float interp_points) : lerp_values{args...} {
      increment = (smooth_max - smooth_start)/interp_points;
    }
    Lerp(float start, float end, float interp_points){
      smooth_start = start;
      smooth_max = end;
      increment = (smooth_max - smooth_start)/interp_points;
    }

    template <typename ActuatorGroup>
    bool writeAll(const ActuatorGroup &a){
        for(int i; i < a.len(); ++i){
            float current_smooth = current_values[i];
            float smooth_start = lerp_values[i];
            float smooth_max = lerp_values[i+1];
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
            current_values[i] += increment;
            a.data[i].write(output);
            GRAPH("lerp",output,TOP);
            return false;
            }
    }

    template <typename actuator>
    bool write(const actuator &a){
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
      a.write(output);
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