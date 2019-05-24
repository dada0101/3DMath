#include <math.h>

#include "MathUtil.h"
#include "Vector3.h"

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

//--------------------------------------------------------------------
//ͨ�������ʵ���2pi���������Ƕ�������-pi��pi��������
float wrapPi(float theta)
{
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

//--------------------------------------------------------------------
//��acos��x����ͬ�������x������Χ��������Ϊ�ӽ�����Чֵ
//����ֵ��0��pi֮�䣬��C�����еı�׼acos����������ͬ
float safeAcos(float x)
{
    //���߽�����

    if(x <= -1.0f)
        return kPi;
    else if(x >= 1.0f)
        return 1.0f;

    //ʹ�ñ�׼C����

    return acos(x);
}
