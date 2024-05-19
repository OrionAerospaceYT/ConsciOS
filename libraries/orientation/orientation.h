#pragma once
#include "utility.h"
#include "quaternion.h"
#include "sk_math.h"
#include "vector.h"

// THIS NEEDS TO BE CHANGED
/*
struct Orientation {
    Quat base;
    Vec *ypr;
    Orientation(Quat base, Vec &ypr) : base(base), ypr(&ypr) {}
    explicit Orientation(const Vec &ypr) { ypr = ypr; }
    Orientation() = default;
    ~Orientation() = default;
    // purely gyro based orientation resolution
    // this will suffer from gyro drift
    template <typename T, typename F>
    void resolveOrientation(const T &gyro, const F &dt) {
        base += base.fromAngularRate(gyro) * dt;
        base.normalize();
        base.toEulerVector(*(ypr));
    }

    // using gradient descent with accel data and gyro data to give orientation
    // (madgwick paper) FLOAT CASTING ALL THROUGH REEE IS THIS OKAY??? also need
    // to look into why accell is not a const we are importing vec and quat so
    // can do a template type T,S etc and make Quat<T> as a passed parameter
    // this will also allow the typing T to be used to cast the floats used rn
    template <typename T, typename S, typename F>
    void resolveOrientation(const T &gyro, const T &accel, const T &ypr, const S &base,
                            const F &dt) {
        auto qdot = base.fromAngularRate(gyro);
        auto norm = accel.magnitude();
        auto norm_accel = accel / norm;
        auto base_2 = base * 2.0f;
        auto base_4 = base * 4.0f;
        auto basei_8 = base.i * 8.0f;
        auto basej_8 = base.j * 8.0f;
        auto base_sq = base.squareElements();
        auto s0 = base_4.w * base_sq.j + base_2.j * norm_accel.x +
                  base_4.w * base_sq.i - base_2.i * norm_accel.y;
        auto s1 = base_4.i * base_sq.k - base_2.k * norm_accel.x +
                  4.0f * base_sq.w * base.i - base_2.w * norm_accel.y -
                  base_4.i + basei_8 * base_sq.i + basei_8 * base_sq.j +
                  base_4.i * norm_accel.z;
        auto s2 = 4.0f * base_sq.w * base.j + base_2.w * norm_accel.x +
                  base_4.j * base_sq.k - base_2.k * norm_accel.y - base_4.j +
                  basej_8 * base_sq.i + basej_8 * base_sq.j +
                  base_4.j * norm_accel.z;
        auto s3 = 4.0f * base_sq.i * base.k - base_2.i * norm_accel.x +
                  4.0f * base_sq.j * base.k - base_2.j * norm_accel.y;
        auto anorm = sk_math::FASTINVSQ(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);
        s0 *= anorm;
        s1 *= anorm;
        s2 *= anorm;
        s3 *= anorm;

            // Apply feedback step
            qDot1 -= beta * s0;
            qDot2 -= beta * s1;
            qDot3 -= beta * s2;
            qDot4 -= beta * s3;
        }

        // Integrate rate of change of quaternion to yield quaternion
        q0 += qDot1 * dt;
        q1 += qDot2 * dt;
        q2 += qDot3 * dt;
        q3 += qDot4 * dt;

        // Normalise quaternion
        recipNorm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
        q0 *= recipNorm;
        q1 *= recipNorm;
        q2 *= recipNorm;
        q3 *= recipNorm;
        Quat temp = Quat(q0, q1, q2, q3);
        Vec out;
        temp.toEulerVector(&out);
        return out;
    }

}  // namespace ori
