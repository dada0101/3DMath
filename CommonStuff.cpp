#include "Vector3.h"

//求两点距离的平方
float distanceSquared(const Vector3 &a, const Vector3 &b)
{
    float dis = distance(a, b);
    return dis * dis;
}
