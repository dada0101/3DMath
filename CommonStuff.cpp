#include "Vector3.h"

//����������ƽ��
float distanceSquared(const Vector3 &a, const Vector3 &b)
{
    float dis = distance(a, b);
    return dis * dis;
}
