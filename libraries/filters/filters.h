#pragma once

// Simple filter definitions

<<<<<<< HEAD
// Kalman filter for single data point/1dof systems
// A lower Q value means more agressive filtering, R is the covariance of the
// sensor
template <typename T = float>
struct SingleKalman {
    T Q = 0;
    T R = 0;
    T A = 1;
    T B = 0;
    T C = 1;
    T D = 0;
    T x_hat = 0;
    T P = 0;
    SingleKalman(T q, T r) : Q(q), R(r) {}
    void setB(T b) { B = b; }
=======
//Kalman filter for single data point/1dof systems
//A lower Q value means more agressive filtering, R is the covariance of the sensor
struct SingleKalman{
float Q = 0;
float R = 0;
float A = 1;
float B = 0;
float C = 1;
float D = 0;
float x_hat = 0;
float P = 0;
SingleKalman(float q, float r) : Q(q), R(r){}
void setB(float b){B = b;}

float filter(float Y, float U = 0){
  auto x_hat_new = A * x_hat + B * U;
  P = A * P * A + Q;
  auto K = P * C * (1.0f / (C * P * C + R));
  x_hat_new += K * (Y - C * x_hat_new);
  P = (1.0f - K * C) * P;
  x_hat = x_hat_new;
  return x_hat;
}
>>>>>>> a997c9e (changed filters.h from template to float quickly)

    T filter(T Y, T U = 0) {
        auto x_hat_new = A * x_hat + B * U;
        P = A * P * A + Q;
        auto K = P * C * (T(1) / (C * P * C + R));
        x_hat_new += K * (Y - C * x_hat_new);
        P = (T(1) - K * C) * P;
        x_hat = x_hat_new;
        return x_hat;
    }
};

<<<<<<< HEAD
// First Order IIR lowpass filter
// Given alpha (filter coeffecient)
template <typename T = float>
struct LowPassFilter {
    T previous_output = 0;
    T alpha;
    explicit LowPassFilter(T a) { alpha = a; }
    T filter(T signal) {
        auto out = alpha * previous_output + (T(1) - alpha) * signal;
        previous_output = out;
        return out;
    }
=======

//First Order IIR lowpass filter 
//Given alpha (filter coeffecient)
struct LowPassFilter{
float previous_output = 0;
float alpha = 0;
LowPassFilter(float a) : alpha(a){}
float filter(float signal){
	auto out = alpha*previous_output + (1.0f - alpha) * signal;
	previous_output = out;
	return out;
}
>>>>>>> a997c9e (changed filters.h from template to float quickly)
};
