#pragma once

#include "utility.h"
#include "sk_math.h"

// Conversions Taken From Madgwick Paper
// https://www.researchgate.net/publication/221775760_Estimation_of_IMU_and_MARG_orientation_using_a_gradient_descent_algorithm

struct Quat {
    float w = 1;
    float i = 0;
    float j = 0;
    float k = 0;

    Quat(float w, float i, float j, float k) : w(w), i(i), j(j), k(k) {}
    Quat(const Quat &q) : w(q.w), i(q.i), j(q.j), k(q.k) {}
    template <typename S>
    Quat(float w, S vec): w(w),i(vec.x),j(vec.y),k(vec.z) {}
    Quat() = default;
    ~Quat() = default;

    //  friend std::ostream& operator<<(std::ostream& o, const Quat<T>& q){
    //    return o << q.w << ", " << q.i << ", " << q.j << ", " << q.k <<
    //    std::endl;
    //  }

    // Arduino override for Serial Print
    operator String() const {
        return String(w) + "," + String(i) + "," + String(j) + "," + String(k);
    }

    // Basic Types
    template <typename S>
    Quat operator*(S f) {
        return Quat(w * f, i * f, j * f, k * f);
    }
    template <typename S>
    Quat operator/(S f) {
        return Quat(w / f, i / f, j / f, k / f);
    }
    template <typename S>
    Quat operator+(S f) {
        return Quat(w + f, i + f, j + f, k + f);
    }
    template <typename S>
    Quat operator-(S f) {
        return Quat(w - f, i - f, j - f, k - f);
    }
    template <typename S>
    void operator*=(S f) {
        *this = *this * f;
    }
    template <typename S>
    void operator/=(S f) {
        *this = *this / f;
    }

    // Quat to Quat operations
    Quat operator*(const Quat &q) {
        Quat r;
        r.w = w * q.w - i * q.i - j * q.j - k * q.k;
        r.i = w * q.i + i * q.w + j * q.k - k * q.j;
        r.j = w * q.j - i * q.k + j * q.w + k * q.i;
        r.k = w * q.k + i * q.j - j * q.i + k * q.w;
        return r;
    }

    // Division of quaternion A by quaternion B is nothing more than multiplying
    // A by the multiplicative inverse of B
    Quat operator/(const Quat &q) {
        Quat r;
        float q_sq = q.square();
        r.w = (q.w * w + q.i * i + q.j * j + q.k * k) / (q_sq);
        r.i = (q.w * i - q.i * w - q.j * k + q.k * j) / (q_sq);
        r.j = (q.w * j + q.i * k - q.j * w - q.k * i) / (q_sq);
        r.k = (q.w * k - q.i * j - q.j * i - q.k * w) / (q_sq);
        return r;
    }
    Quat operator+(const Quat &q) {
        return Quat(w + q.w, i + q.i, j + q.j, k + q.k);
    }
    Quat operator-(const Quat &q) {
        return Quat(w - q.w, i - q.i, j - q.j, k - q.k);
    }
    Quat operator+=(const Quat &q) {
        return Quat(w += q.w, i += q.i, j += q.j, k += q.k);
    }
    Quat operator-=(const Quat &q) {
        return Quat(w -= q.w, i -= q.i, j -= q.j, k -= q.k);
    }

    // BOOL operations
    bool operator==(const Quat &q) {
        return w == q.w && i == q.i && j == q.j && k == q.k;
    }

    bool operator!=(const Quat &q) {
        return !(w == q.w && i == q.i && j == q.j && k == q.k);
    }

    // Convert to Euler Angles array
    float *toEuler() {
        float ypr[3];
        ypr[0] = atan2((2.0f) * (i * j + w * k), w * w + i * i - j * j - k * k);
        ypr[1] = -asin((2.0f) * (i * k - w * j));
        ypr[2] = atan2((2.0f) * (w * i + j * k), w * w - i * i - j * j + k * k);
        return ypr;
    }

    // Convert to Euler Angles vector
    template <typename S>
    S* toEulerVector(S* vec) {
        vec->x = atan2(2.0f * i * j - 2.0f * w * k,
                      2.0f * w * w + 2.0f * i * i - 1.0f);
        auto check = 2.0f * i * k + 2.0f * w * j;
        if (abs(check) >= 1.0f) {
            vec->y = -sk_math::SIGN(check) * PI / 2.0f;
        } else {
            vec->y = -asin(check);
        }
        vec->z = atan2(2.0f * j * k - 2.0f * w * i,
                      2.0f * w * w + 2.0f * k * k - 1.0f);
        return vec;
    }

    // Angular rate must be given in rad/s
    template <typename S>
    Quat fromAngularRate(const S &v) {
        Quat r(0, v.x, v.y, v.z);
        return (*this * 0.5f) * r;
    }

    template <typename S>
    Quat fromEuler(S x, S y, S z) {
        Quat q;
        q.w = cos(z * 0.5f) * cos(y * 0.5f) * cos(x * 0.5f) +
              sin(z * 0.5f) * sin(y * 0.5f) * sin(x * 0.5f);
        q.i = sin(z * 0.5f) * cos(y * 0.5f) * cos(x * 0.5f) -
              cos(z * 0.5f) * sin(y * 0.5f) * sin(x * 0.5f);
        q.j = cos(z * 0.5f) * sin(y * 0.5f) * cos(x * 0.5f) +
              sin(z * 0.5f) * cos(y * 0.5f) * sin(x * 0.5f);
        q.k = cos(z * 0.5f) * cos(y * 0.5f) * sin(x * 0.5f) -
              sin(z * 0.5f) * sin(y * 0.5f) * cos(x * 0.5f);
        return q;
    }

    template <typename S>
    Quat fromEuler(const S &v) {
        Quat q;
        q.w = cos(v.z * 0.5f) * cos(v.y * 0.5f) * cos(v.x * 0.5f) +
              sin(v.z * 0.5f) * sin(v.y * 0.5f) * sin(v.x * 0.5f);
        q.i = sin(v.z * 0.5f) * cos(v.y * 0.5f) * cos(v.x * 0.5f) -
              cos(v.z * 0.5f) * sin(v.y * 0.5f) * sin(v.x * 0.5f);
        q.j = cos(v.z * 0.5f) * sin(v.y * 0.5f) * cos(v.x * 0.5f) +
              sin(v.z * 0.5f) * cos(v.y * 0.5f) * sin(v.x * 0.5f);
        q.k = cos(v.z * 0.5f) * cos(v.y * 0.5f) * sin(v.x * 0.5f) -
              sin(v.z * 0.5f) * sin(v.y * 0.5f) * cos(v.x * 0.5f);
        return q;
    }

    // BLA Matrix conversions
    template <typename S>
    Quat fromMat(const S &mat) {
        return Quat(mat(0), mat(1), mat(2), mat(3));
    }

    template <typename S>
    S toMat(S* mat) {
        mat(0) = w;
        mat(1) = i;
        mat(2) = j;
        mat(3) = k;
        return mat;
    }

    float magnitude() const { return sqrt(w * w + i * i + j * j + k * k); }

    float square() const { return w * w + i * i + j * j + k * k; }

    Quat squareElements() { return Quat(w * w, i * i, j * j, k * k); }

    void normalize() { *this = Quat((*this) / magnitude()); }
};
