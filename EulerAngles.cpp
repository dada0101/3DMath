//////////////////////////////////////////////////////////////////
//
//3D Math Primer for Games and Graphics Development
//
//EulerAngles.cpp - Implementation of class EulerAngles
//
//////////////////////////////////////////////////////////////////

#include <math.h>
#include "EulerAngles.h"
#include "Quaternion.h"
#include "MathUtil.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//
//ȫ������
//
//////////////////////////////////////////////////////////////////////////////////////////////

//ȫ�֡���λ��ŷ���ǳ���
//�������ǻ���֪����������ȷ��ʱ������Ҫȡ����������������п����ڸö��󱻳�ʼ��֮ǰ����������
//�����ڴ����ʵ���У������ڳ���ʼʱ�ͱ���ʼ��Ϊ0�����������������󱻹���֮ǰ��

const EulerAngles kEulerAnglesIdentify(0.0f, 0.0f, 0.0f);

//////////////////////////////////////////////////////////////////////////////////////////////
//
//class EulerAngles Implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------
//EulerAngles::canonize
//��ŷ����ת�������Ƽ���
//�ͱ�ʾ3D��λ��Ŀ�Ķ��ԣ�������ı�ŷ���ǵ�ֵ
//������������ʾ��������ٶȵȣ�������Ӱ��

void EulerAngles::canonize()
{
    //���ȣ���pitch�任��-pi/2��pi/2֮��

    pitch = wrapPi(pitch);

    //���ڽ�pitch�任��-pi/2��pi/2֮��

    if(pitch < -kPiOver2)
    {
        pitch = -kPi - pitch;
        heading += kPi;
        bank += kPi;
    }
    else if(pitch > kPiOver2)
    {
        pitch = kPi - pitch;
        heading += kPi;
        bank += kPi;
    }

    //���ڼ����������������������һ�������

    if(fabs(pitch) > kPiOver2 - 1e4)
    {
        //���������У��������ƴ�ֱ�����ת����heading

        heading += bank;
        bank = 0.0f;
    }
    else
    {
        //������������bankת�������Ƽ���

        bank = wrapPi(bank);
    }
    //��headingת�������Ƽ���

    heading = wrapPi(heading);
}

//---------------------------------------------------------------------------
//EulerAngles::fromObjectToInertialQuaternion
//
//������-������Ԫ����ŷ����
//

void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
{
    //����sin��pitch��

    float sp = -2.0f * (q.y*q.z - q.w*q.x);

    //������������������һ�����

    if(fabs(sp) > 0.9999f)
    {
        //�����Ϸ������·���

        pitch = kPiOver2 * sp;

        //bank���㣬����heading
        heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
        bank = 0.0f;
    }
    else
    {
        //����Ƕȣ��������ǲ���ʹ�ð�ȫ��asin��������Ϊ֮ǰ�ڼ����������
        //��ʱ�Ѽ�����Χ������

        pitch = asin(sp);
        heading = atan2(q.x * q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
        bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
    }
}

//---------------------------------------------------------------------------
//EulerAngles::fromInertialToObjectQuaternion
//�ӹ���-������Ԫ����ŷ����
//

void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
{
    //����sin��pitch��

    float sp = -2.0f * (q.y*q.z +q.w*q.x);

    //���������������һ�����

    if(fabs(sp) > 0.9999f)
    {
        //�����Ϸ������·���

        pitch = kPiOver2 * sp;

        //bank���㣬����heading

        heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
        bank = 0.0f;
    }
    else
    {
        //����Ƕ�

        pitch = asin(sp);
        heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
        bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
    }
}

//---------------------------------------------------------------------------
//EulerAngles::fromObjectToWorldMatrix
//������-��������ϵ�任����ŷ����
//��������������ģ�����ƽ�Ʋ���
//
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
    //ͨ��m32����sin��pitch��

    float sp = -m.m32;

    //���������

    if(fabs(sp) > 0.9999f)
    {
        //�����Ϸ������·���

        pitch = kPiOver2 * sp;

        //bank���㣬����heading

        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //����Ƕ�

        heading = atan2(m.m31, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m12, m.m22);
    }
}

//---------------------------------------------------------------------------
//EulerAngles::fromWorldToObjectMatrix
//������-��������ϵ�任����ŷ����
//
//��������������ģ�����ƽ�Ʋ���
//

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
{
    //����m32����sin(pitch)

    float sp = -m.m23;

    //���������

    if(fabs(sp) > 0.9999f)
    {
        //�����Ϸ������·���

        pitch = kPiOver2 * sp;

        //bank���㣬����heading

        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //����Ƕ�

        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}

//---------------------------------------------------------------------
//EulerAngles::fromRotationMatrix
//������ת������ŷ����
//

void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
{
    //����m32����sin(pitch)

    float sp = -m.m23;

    //���������

    if(fabs(sp) > 0.9999f)
    {
        //�����Ϸ������·���

        pitch = kPiOver2 * sp;

        //bank���㣬����heading

        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //����Ƕ�

        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}
