#pragma once

// Simple filter definitions

// Kalman filter for single data point/1dof systems
// A lower Q value means more agressive filtering, R is the covariance of the
// sensor
struct SingleKalman {
    float Q = 0;
    float R = 0;
    float A = 1;
    float B = 0;
    float C = 1;
    float D = 0;
    float x_hat = 0;
    float P = 0;
    SingleKalman(float q, float r) : Q(q), R(r) {}
    void setB(float b) { B = b; }

    float filter(float Y, float U = 0) {
        auto x_hat_new = A * x_hat + B * U;
        P = A * P * A + Q;
        auto K = P * C * (float(1) / (C * P * C + R));
        x_hat_new += K * (Y - C * x_hat_new);
        P = (float(1) - K * C) * P;
        x_hat = x_hat_new;
        return x_hat;
    }
};

// First Order IIR lowpass filter
// Given alpha (filter coeffecient)
struct LowPassFilter {
    float previous_output = 0.0f;
    float alpha = 0.0f;
    LowPassFilter(float a) { alpha = a; }
    float filter(float signal) {
        previous_output = alpha * previous_output + (1.0f - alpha) * signal;
        return previous_output;
    }
};
