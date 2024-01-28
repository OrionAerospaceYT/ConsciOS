#pragma once

// Simple controller definitions

// PID controller
struct PID {
    float kp = 0.0f;
    float ki = 0.0f;
    float kd = 0.0f;
    float setpoint = 0.0f;
    float integral_err = 0.0f;
    float previous_err = 0.0f;
    float min_lim = -1000.0;
    float max_lim = 1000.0f;
    bool lims_set = false;

    PID(float p_gain, float i_gain, float d_gain, float setpoint = 0.0f)
        : kp(p_gain), ki(i_gain), kd(d_gain), setpoint(setpoint) {}

    void setlims(float min, float max) {
        min_lim = min;
        max_lim = max;
        lims_set = true;
    }

    void setSetpoint(float new_setpoint) {
      setpoint = new_setpoint;
    }

    float compute(float input, float dt) {
      float error = setpoint - input;

      // assert dt must not be 0
      float derivative_err = (error - previous_err) / dt;

      integral_err += error * dt;

      float output = kp * error + ki * integral_err + kd * derivative_err;

      previous_err = error;

      if (lims_set) {
          if (output > max_lim) {
              output = max_lim;
          } else if (output < min_lim) {
              output = min_lim;
          }
          if (integral_err > max_lim) {
              integral_err = max_lim;
          } else if (integral_err < min_lim) {
              integral_err = min_lim;
          }
      }
      return output;
    }
};
