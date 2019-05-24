//////////////////////////////////////////////////////////////////////////
//
//3D Math Primer for Games and Graphics Development
//
//Quaternion.cpp - Quaternion implementation
//
//For more details see section 11.3
//
//////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <math.h>

#include "Quaternion.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"

//////////////////////////////////////////////////////////////////////////
//
//ȫ������
//
//////////////////////////////////////////////////////////////////////////
//ȫ�ֵ�λ��Ԫ����ע��Quaternion��û�й��캯������Ϊ���ǲ�����Ҫ��

const Quaternion kQuaternionIdentify = {1.0f, 0.0f, 0.0f, 0.0f};

//////////////////////////////////////////////////////////////////////////
//
//Quaternion���Ա
//
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
//Quaternion::setToRotateAboutX
//Quaternion::setToRotateAboutY
//Quaternion::setToRotateAboutZ
//Quaternion::setToRotateAboutAxis
//������ָ������ת����Ԫ��

void Quaternion::setToRotateAboutX(float theta)
{
    //������

    float thetaOver2 = theta * .5f;

    //��ֵ

    w = cos(thetaOver2);
    x = sin(thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
    //������

    float thetaOver2 = theta * .5f;

    //��ֵ

    w = cos(thetaOver2);
    x = 0.0f;
    y = sin(thetaOver2);
    z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
    //������

    float thetaOver2 = theta * .5f;

    //��ֵ

    w = cos(thetaOver2);
    x = 0.0f;
    y = 0.0f;
    z = sin(thetaOver2);
}

void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
    //��ת������׼��

    assert(fabs(vectorMsg(axis) - 1.0f) < .01f);

    //�����Ǻ�sinֵ

    float thetaOver2 = theta * .5f;
    float sinThetaOver2 = sin(thetaOver2);

    //��ֵ

    w = cos(thetaOver2);
    x = axis.x * sinThetaOver2;
    y = axis.y * sinThetaOver2;
    z = axis.z * sinThetaOver2;
}

//------------------------------------------------------------------------
//Quaternion::setToRotateObjectToInertial
//����ִ������-������ת����Ԫ��
//
//��λ������ŷ������ʽ����
void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{
    //�����ǵ�sin��cosֵ

    float sp, sh, sb;
    float cp, ch, cb;

    sinCos(&sp, &cp, orientation.pitch * .5f);
    sinCos(&sb, &cb, orientation.bank * .5f);
    sinCos(&sh, &ch, orientation.heading * .5f);

    //������

    w = ch*cp*cb + sh*sp*sb;
    x = ch*sp*cb + sh*cp*sb;
    y = -ch*sp*sb + sh*cb*cp;
    z = -sh*sp*cb + ch*cp*sb;
}

//------------------------------------------------------------------------
//Quaternion::setToRotateInertialToObject
//����ִ�й���-������ת����Ԫ��
//
//��λ������ŷ������ʽ����

void Quaternion::setToRotateInertialToObject(const EulerAngles &orientation)
{
    //�����ǵ�sin��cosֵ

    float sp, sh, sb;
    float cp, ch, cb;
    sinCos(&sp, &cp, orientation.pitch * .5f);
    sinCos(&sb, &cb, orientation.bank * .5f);
    sinCos(&sh, &ch, orientation.heading * .5f);

    //������

    w = ch*cp*cb + sh*sp*sb;
    x = -ch*sp*cb - sh*cp*sb;
    y = ch*sp*sb - sh*cb*cp;
    z = sh*sp*cb - ch*cp*sb;
}

//------------------------------------------------------------------------
//Quaternion::operator*
//��Ԫ��������㣬�������Ӷ����λ��
//�˵�˳���Ǵ�������
//�����Ԫ����˵ı�׼�����෴��

Quaternion Quaternion::operator*(const Quaternion &a) const
{
    Quaternion result;

    result.w = w*a.w - x*a.x - y*a.y - z*a.z;
    result.x = w*a.w + x*a.w + z*a.y - y*a.z;
    result.y = w*a.y + y*a.w + x*a.z - z*a.x;
    result.z = w*a.z + z*a.w + y*a.x - x*a.y;

    return result;
}

//------------------------------------------------------------------------
//Quaternion *=
//��˲���ֵ�����Ƿ���C++ϰ��д����

Quaternion &Quaternion::operator *= (const Quaternion &a)
{
    *this = *this * a;
    return *this;
}

//------------------------------------------------------------------------
//Quaternion::normalize
//������Ԫ����
//ͨ������Ԫ���������򻯵ġ�
//
//�ṩ���������Ҫ��Ϊ�˷�ֹ����������������Ԫ���������ܵ��²�������
//

void Quaternion::normalize()
{
    //������Ԫ����ģ

    float msg = sqrt(w*w + x*x + y*y + z*z);

    //���㳤�ȣ���ֹ�������

    if(msg > 0.0f)
    {
        //����

        float oneOverMsg = 1.0f / msg;
        w *= oneOverMsg;
        x *= oneOverMsg;
        y *= oneOverMsg;
        z *= oneOverMsg;
    }
    else
    {
        //���鷳��

        assert(false);

        //�ڷ������У����ص�Ԫ��Ԫ��

        identify();
    }
}

//------------------------------------------------------------------------
//Quaternion::getRotationAngle
//������ת��

float Quaternion::getRotationAngle() const
{
    //�����ǣ�w = cos(theta / 2)

    float thetaOver2 = safeAcos(w);

    //������ת��

    return thetaOver2 * 2.0f;
}

//------------------------------------------------------------------------
//Quaternion::getRotationAxis
//��ȡ��ת��

Vector3 Quaternion::getRotationAxis() const
{
    //����sin^2(theta/2)����סw = cos(theta/2)��sin^2(x) + cos^2(x) = 1

    float sinThetaOver2Sq = 1.0f - w*w;;

    //ע�Ᵽ֤��ֵ����

    if(sinThetaOver2Sq <= 0.0f)
    {
        //��λ��Ԫ���򲻻���ȷ����ֵ��ֻҪ������Ч����������

        return Vector3(1.0f, 0.0f, 0.0f);
    }

    //����1/sin(theta.2)

    float oneOverSinThetaOver2 = 1 / sqrt(sinThetaOver2Sq);

    //������ת��
    return Vector3(
        x * oneOverSinThetaOver2,
        y * oneOverSinThetaOver2,
        z * oneOverSinThetaOver2
        );
}

//////////////////////////////////////////////////////////////////
//
//�ǳ�Ա����
//
//////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------
//dotProduct
//��Ԫ�����
//�÷ǳ�Ա����ʵ����Ԫ������Ա����ڱ��ʽ��ʹ��ʱ���ֹ����﷨��

float dotProduct(const Quaternion &a, const Quaternion &b)
{
    return a.w*b.w +a.x*b.x + a.y*b.y + a.z*b.z;
}

//------------------------------------------------------------------------
//slerp
//�������Բ�ֵ
//

Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
    //������Ĳ����������鵽�����ر߽��

    if(t <= 0.0f)
        return q0;
    if(t >= 1.0f)
        return q1;

    //�õ�˼�����Ԫ���нǵ�cosֵ

    float cosOmega = dotProduct(q0, q1);

    //������Ϊ����ʹ��-q1
    //��Ԫ��q��-q������ͬ����ת�������ܲ�����ͬ��slerp���㣬����Ҫѡ����ȷ��һ��
    //�Ա�����ǽ�����ת��

    float q1w = q1.w;
    float q1x = q1.x;
    float q1y = q1.y;
    float q1z = q1.z;

    if(cosOmega < 0.0f)
    {
        q1w = -q1w;
        q1x = -q1x;
        q1y = -q1y;
        q1z = -q1z;
        cosOmega = -cosOmega;
    }

    //�����õ���������λ��Ԫ�������Ե�˽��Ӧ��<=1.0

    assert(cosOmega < 1.1f);

    //�����ֵƬ��ע����ǳ��ӽ������

    float k0, k1;
    if(cosOmega > 0.9999f)
    {
        //�ǳ��ӽ��������Բ�ֵ����ֹ����

        k0 = 1.0f - t;
        k1 = t;
    }
    else
    {
        //�����ǹ�ʽsin^2(omega) + cos^2(omega) = 1 ����sinֵ

        float sinOmega = sqrt(1.0f - cosOmega * cosOmega);

        //�����ĸ�ĵ���������ֻ��Ҫ��һ��

        float oneOverSinOmega = 1.0f / sinOmega;

        //����sin��cosֵ����Ƕ�

        float omega = atan2(sinOmega, cosOmega);

        //�����ֵ����

        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    //��ֵ

    Quaternion result;

    result.w = k0*q0.w + k1*q1w;
    result.x = k0*q0.x + k1*q1x;
    result.y = k0*q0.y + k1*q1y;
    result.z = k0*q0.z + k1*q1z;

    //����

    return result;
}

//------------------------------------------------------------------------
//conjugate
//��Ԫ���������ԭ��Ԫ����ת�����෴����Ԫ��
//

Quaternion conjugate(const Quaternion &q)
{
    Quaternion result;

    //��ת����ͬ

    result.w = q.w;

    //��ת���෴

    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;

    //����

    return result;
}

//------------------------------------------------------------------------
//pow
//��Ԫ����
//

Quaternion pow(const Quaternion &q, float exponent)
{
    //��鵥λ��Ԫ������ֹ����

    if(fabs(q.w) > .9999f)
        return q;

    //��ȡ���alpha(alpha = theta/2)

    float alpha = acos(q.w);

    //�����µ�alphaֵ

    float newAlpha = alpha * exponent;

    Quaternion result;

    //������wֵ

    result.w = cos(newAlpha);

    //������xyzֵ

    float mult = sin(newAlpha) / sin(alpha);
    result.x = q.x * mult;
    result.y = q.y * mult;
    result.z = q.z * mult;

    //����

    return result;
}
