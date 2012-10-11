#pragma once

#ifndef _UTILITY_H_
#define _UTILITY_H_

#define EPSILON 1.0e-5f
#define PI 3.1415926535897932384626433832795f
#define HALFPI 1.5707963267948966192313216916398f
#define TWOPI 2.0f * PI

#include <cmath>

/**
 * Test whether a number is zero, considering an epsilon value
 * (to correct small accuracy problems).
 *
 * @param a
 *
 * @return True if zero, false if not
 */
inline bool RFMathIsZero(float a) 
{
    return (fabs(a) < EPSILON);
}

/**
 * Test whether two floats are equal, considering an epsilon
 * value (to correct small accuracy problems).
 *
 * @param a
 * @param b
 *
 * @return True if equal, false if not
 */
inline bool RFMathIsEqual(float a, float b)
{
    return RFMathIsZero(a - b);
}

/**
 * Calculate the inverse square root.
 *
 * @param x
 *
 * @return Inverse square root
 */
inline float RFMathInvSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759d5 - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - xhalf * x * x);
    return x;
}

/**
 * Calculate the sine and cosine of an angle.
 *
 * @param angle
 * @param sina out
 * @param cosa out
 */
inline void RFMathSinCos(float angle, float& sin, float& cos)
{
    sin = sinf(angle);
    cos = cosf(angle);
}

/**
 * Convert degrees to radians.
 *
 * @param degrees
 *
 * @return Angle in radians
 */
inline float RFMathDegToRad(float degrees)
{
    return degrees * (PI / 180.0f);
}

/**
 * Convert radians to degrees.
 *
 * @param radians
 *
 * @return Angle in degrees
 */
inline float RFMathRadToDeg(float radians)
{
    return radians * (180.0f / PI);
}

/**
 * Clamp a value to a minimum and maximum value.
 * 
 * @param value
 * @param min
 * @param max
 *
 * @return Clamped value
 */
inline float RFMathClamp(float value, float min, float max)
{
    if(value > max)
    {
        return max;
    }

    if(value < min)
    {
        return min;
    }

    return value;
}

#endif