#pragma once
#include "utility.h"
#include "quaternion.h"
#include "sk_math.h"
#include "vector.h"
#include "BasicLinearAlgebra.h"

#define GYRO_MEAN_ERROR  PI * (5.0f / 180.0f) // 5 deg/s gyroscope measurement error (in rad/s)  *from paper*
#define BETA sqrt(3.0f/4.0f) * GYRO_MEAN_ERROR

namespace ori{
    Quat q_est = Quat();

    Vec resolve_orientation(Vec accel, Vec gyro, float dt){
    
        //Variables and constants
        Quat q_est_prev(q_est);
        Quat q_est_dot(0,0,0,0);            // used as a place holder in equations 42 and 43
        //const struct quaternion q_g_ref = {0, 0, 0, 1};// equation (23), reference to field of gravity for gradient descent optimization (not needed because I used eq 25 instead of eq 21
        Quat q_a(0.0f,accel);    // equation (24) raw acceleration values, needs to be normalized
        
        Vec F_g;                        // equation(15/21/25) objective function for gravity
        BLA::Matrix<3,4> J_g;
        
        Quat gradient(0,0,0,0);
        
        /* Integrate angluar velocity to obtain position in angles. */
        Quat q_w(0.0f,gyro);                   // equation (10), places gyroscope readings in a quaternion
        
        q_w = q_w * 0.5f;                // equation (12) dq/dt = (1/2)q*w
        q_w = q_est_prev * q_w;
        PRINT(gradient);
        delay(10000);
        /* NOTE
        * Page 10 states equation (40) substitutes equation (13) into it. This seems false, as he actually
        * substitutes equation (12), q_se_dot_w, not equation (13), q_se_w.
        * 
        * // quat_scalar(&q_w, deltaT);               // equation (13) integrates the angles velocity to position
        * // quat_add(&q_w, q_w, q_est_prev);         // addition part of equation (13)
        */

        /* Compute the gradient by multiplying the jacobian matrix by the objective function. This is equation 20.
        The Jacobian matrix, J, is a 3x4 matrix of partial derivatives for each quaternion component in the x y z axes
        The objective function, F, is a 3x1 matrix for x y and z.
        To multiply these together, the inner dimensions must match, so use J'.
        I calculated "by hand" the transpose of J, so I will be using "hard coordinates" to get those values from J.
        The matrix multiplcation can also be done hard coded to reduce code.
        
        Note: it is possible to compute the objective function with quaternion multiplcation functions, but it does not take into account the many zeros that cancel terms out and is not optimized like the paper shows
        */
        
        q_a.normalize();              // normalize the acceleration quaternion to be a unit quaternion
        //Compute the objective function for gravity, equation(15), simplified to equation (25) due to the 0's in the acceleration reference quaternion
        F_g.x = 2.0f*(q_est_prev.i * q_est_prev.k - q_est_prev.w * q_est_prev.j) - q_a.i;
        F_g.y = 2.0f*(q_est_prev.w * q_est_prev.i + q_est_prev.j* q_est_prev.k) - q_a.j;
        F_g.z = 2.0f*(0.5f - q_est_prev.i * q_est_prev.i - q_est_prev.j * q_est_prev.j) - q_a.k;
        
        //Compute the Jacobian matrix, equation (26), for gravity
        J_g(0,0) = -2.0f * q_est_prev.j;
        J_g(0,1) =  2.0f * q_est_prev.k;
        J_g(0,2) = -2.0f * q_est_prev.w;
        J_g(0,3) =  2.0f * q_est_prev.i;
        
        J_g(1,0) = 2.0f * q_est_prev.i;
        J_g(1,1) = 2.0f * q_est_prev.w;
        J_g(1,2) = 2.0f * q_est_prev.k;
        J_g(1,3) = 2.0f * q_est_prev.j;
        
        J_g(2,0) = 0.0f;
        J_g(2,1) = -4.0f * q_est_prev.i;
        J_g(2,2) = -4.0f * q_est_prev.j;
        J_g(2,3) = 0.0f;
        
        // now computer the gradient, equation (20), gradient = J_g'*F_g
        gradient.w = J_g(0,0) * F_g[0] + J_g(1,0) * F_g[1] + J_g(2,0) * F_g[2];
        gradient.i = J_g(0,1) * F_g[0] + J_g(1,1) * F_g[1] + J_g(2,1) * F_g[2];
        gradient.j = J_g(0,2) * F_g[0] + J_g(1,2) * F_g[1] + J_g(2,2) * F_g[2];
        gradient.k = J_g(0,3) * F_g[0] + J_g(1,3) * F_g[1] + J_g(2,3) * F_g[2];
        
        // Normalize the gradient, equation (44)
        gradient.normalize();
    
        /* This is the sensor fusion part of the algorithm.
        Combining Gyroscope position angles calculated in the beginning, with the quaternion orienting the accelerometer to gravity created above.
        Noticably this new quaternion has not be created yet, I have only calculated the gradient in equation (19).
        Madgwick however uses assumptions with the step size and filter gains to optimize the gradient descent,
            combining it with the sensor fusion in equations (42-44).
        He says the step size has a var alpha, which he assumes to be very large.
        This dominates the previous estimation in equation (19) to the point you can ignore it.
        Eq. 36 has the filter gain Gamma, which is related to the step size and thus alpha. With alpha being very large,
            you can make assumptions to simplify the fusion equatoin of eq.36.
        Combining the simplification of the gradient descent equation with the simplification of the fusion equation gets you eq.
        41 which can be subdivided into eqs 42-44.
        */
        PRINT(BETA); 
        gradient = gradient * BETA;
        q_est_dot = q_w - gradient;
        q_est_dot = q_est_dot * dt;
        q_est = q_est_prev + q_est_dot;
        q_est.normalize();
        Vec out;
        q_est.toEulerVector(&out);
        return out;
                                                    //(shown in diagram, plus always use unit quaternions for orientation)
   
}






};