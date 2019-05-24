///////////////////////////////////////////////////////////////////////////////////
//
//3D Math Primer for Graphics and Game Development
//MathUtil.h - Declarations for miscellaneous math utilities
//Visit gamemath.com for the latest version of this file.
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef MATHUTIL_H_INCLUDED
#define MATHUTIL_H_INCLUDED

#include <math.h>

//定义与pi有关的常量
const float kPi = 3.1415926f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0 / k2Pi;

//通过加适当的2pi倍数将角度限制在-pi到pi的区间内
extern float wrapPi(float theta);

//安全反三角函数
extern float safeAcos(float x);

//计算角度的sin和cos值
//在某些平台上，如果需要这两个值，同时计算要比分开计算快
inline void sinCos(float *returnSin, float *returnCos, float theta)
{
    //为了简单，我们只使用标准三角函数
    //注意在某些平台上可以做的更好一些
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

#endif // MATHUTIL_H_INCLUDED
