/////////////////////////////////////////////////////////////////
//
//3D Math Primer for Games and Graphics Development
//
//RotationMatrix.cpp - Implementation of class RotationMatrix
//
/////////////////////////////////////////////////////////////////

#include "Vector3.h"
#include "RotationMatrix.h"
#include "MathUtil.h"
#include "Quaternion.h"
#include "EulerAngles.h"

/////////////////////////////////////////////////////////////////
//
//RotationMatrix��
//
//---------------------------------------------------------------
//
//MATRIX ORGANIZATION
//������ʹ����Ӧ�ú�����Ҫ���ľ������֯��ʽ
//��Ȼ��������������˵Ӧ��ʹһ�����鶼�Ե÷ǳ�ֱ��
//��������Ϊ��ת�����������������
//�þ�������ǹ��Ե�����ı任�����Ҫִ�����嵽���Եı任��Ӧ�ó�������ת��
//Ҳ����˵
//
//���Ե�����ı任
//
//           | m11 m12 m13 |
//   [ix iy iz] | m21 m22 m23 | = [ ox oy oz ]
//           | m31 m32 m33 |
//
//���嵽���Եı任
//
//           | m11 m21 m31 |
//   [ox oy oz] | m12 m22 m32 | = [ ix iy iz ]
//           | m13 m23 m33 |
//
//Ҳ����ʹ������������ʽ�ı任
//
//���Ե�����ı任
//
//      | m11 m21 m13 | | ix |    | ox |
//      | m12 m22 m32 | | iy |  = | oy |
//      | m13 m23 m33 | | iz |    | oz |
//
//���嵽���Եı任
//
//      | m11 m12 m13 | | ox |    | ix |
//      | m21 m22 m23 | | oy |  = | iy |
//      | m31 m32 m33 | | oz |    | iz |
/////////////////////////////////////////////////////////////////

//---------------------------------------------------------------
//RotationMatrix::identify
//��Ϊ��λ����

void RotationMatrix::identify()
{
    m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
    m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
    m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

//---------------------------------------------------------------
//RotationMatrix::setup
//��ŷ���ǲ����������
//

void RotationMatrix::setup(const EulerAngles &orientation)
{
    // ����Ƕȵ�sin��cosֵ

    float sh,ch, sp,cp, sb,cb;

    sinCos(&sh, &ch, orientation.heading);
    sinCos(&sp, &cp, orientation.pitch);
    sinCos(&sb, &cb, orientation.bank);

    //������

    m11 = ch * cb + sh * sp * sb;
    m12 = -ch * sb +sh * sp * cb;
    m13 = sh * cp;

    m21 = sb * cp;
    m22 = cb * cp;
    m23 = -sp;

    m31 = -sh * cb + ch * sp * sb;
    m32 = sb * sh + ch * sp * cb;
    m33 = ch * cp;
}

//---------------------------------------------------------------
//RotationMatrix::fromInertialToObjectQuaternion
//���ݹ���-������ת��Ԫ���������
//

void RotationMatrix::fromInertialToObjectQuaternion(const Quaternion &q)
{
    //�����󣬻����Ż��Ŀ��ܣ���Ϊ����ӱ��ʽ����ͬ�ģ����ǰ��Ż���������������

    m11 = 1.0f - 2.0f * (q.y*q.y + q.z*q.z);
    m12 = 2.0f * (q.x*q.y + q.w*q.z);
    m13 = 2.0f * (q.x*q.z - q.w*q.y);

    m21 = 2.0f * (q.x*q.y - q.w*q.z);
    m22 = 1.0f - 2.0f * (q.x*q.x + q.z*q.z);
    m23 = 2.0f * (q.y*q.z + q.w*q.x);

    m31 = 2.0f * (q.x*q.z + q.w*q.y);
    m32 = 2.0f * (q.y*q.z - q.w*q.x);
    m33 = 1.0f - 2.0f * (q.x*q.x + q.y*q.y);
}

//---------------------------------------------------------------
//RotationMatrix::fromObjectToInertialQuaternion
//��������-������ת��Ԫ���������
//

void RotationMatrix::fromObjectToInertialQuaternion(const Quaternion &q)
{
    //�����󣬻����Ż��Ŀ��ܣ���Ϊ����ӱ��ʽ����ͬ�ģ����ǰ��Ż�����������������

    m11 = 1.0f - 2.0f * (q.y*q.y + q.z*q.z);
    m12 = 2.0f *(q.x*q.y - q.w*q.z);
    m13 = 2.0f * (q.x*q.z + q.w*q.y);

    m21 = 2.0f * (q.x*q.y + q.w*q.z);
    m22 = 1.0f - 2.0f * (q.x*q.x + q.z*q.z);
    m23 = 2.0f * (q.y*q.z - q.w*q.x);

    m31 = 2.0f * (q.x*q.z - q.w*q.y);
    m32 = 2.0f * (q.y*q.z + q.w*q.x);
    m33 = 1.0f - 2.0f * (q.x*q.x + q.y*q.y);
}

//---------------------------------------------------------------
//RotationMatrix::intertialToObject
//������������-����任
//

Vector3 RotationMatrix::inertialToObject(const Vector3 &v) const
{
    //�Ա�׼��ʽִ�о���˷�

    return Vector3(
        m11*v.x + m21*v.y + m31*v.z,
        m12*v.x + m22*v.y + m32*v.z,
        m13*v.x + m23*v.y + m33*v.z
    );
}

//---------------------------------------------------------------
//RotationMatrix::objectToInertial
//������������-���Ա任

Vector3 RotationMatrix::objectToInertial(const Vector3 &v) const
{
    //����ת��

    return Vector3(
    m11*v.x + m12*v.y + m13*v.z,
    m21*v.x + m22*v.y + m23*v.z,
    m31*v.x + m32*v.y + m33*v.z
    );
}
