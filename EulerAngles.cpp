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
//全局数据
//
//////////////////////////////////////////////////////////////////////////////////////////////

//全局”单位“欧拉角常量
//现在我们还不知道构造它的确切时机，这要取决于其他对象，因此有可能在该对象被初始化之前就引用它。
//不过在大多数实现中，它将在程序开始时就被初始化为0，即发生在其他对象被构造之前。

const EulerAngles kEulerAnglesIdentify(0.0f, 0.0f, 0.0f);

//////////////////////////////////////////////////////////////////////////////////////////////
//
//class EulerAngles Implementation
//
//////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------
//EulerAngles::canonize
//将欧拉角转换到限制集中
//就表示3D方位的目的而言，它不会改变欧拉角的值
//但对于其他表示对象如加速度等，则会产生影响

void EulerAngles::canonize()
{
    //首先，将pitch变换到-pi/2到pi/2之间

    pitch = wrapPi(pitch);

    //现在将pitch变换到-pi/2到pi/2之间

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

    //现在检查万向锁的情况，允许存在一定的误差

    if(fabs(pitch) > kPiOver2 - 1e4)
    {
        //在万向锁中，将所有绕垂直轴的旋转赋给heading

        heading += bank;
        bank = 0.0f;
    }
    else
    {
        //非万向锁，将bank转换到限制集中

        bank = wrapPi(bank);
    }
    //将heading转换到限制集中

    heading = wrapPi(heading);
}

//---------------------------------------------------------------------------
//EulerAngles::fromObjectToInertialQuaternion
//
//从物体-惯性四元数到欧拉角
//

void EulerAngles::fromObjectToInertialQuaternion(const Quaternion &q)
{
    //计算sin（pitch）

    float sp = -2.0f * (q.y*q.z - q.w*q.x);

    //检查万向锁，允许存在一定误差

    if(fabs(sp) > 0.9999f)
    {
        //从正上方或正下方看

        pitch = kPiOver2 * sp;

        //bank置零，计算heading
        heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
        bank = 0.0f;
    }
    else
    {
        //计算角度，这里我们不必使用安全的asin函数，因为之前在检查万向锁问
        //题时已检查过范围错误了

        pitch = asin(sp);
        heading = atan2(q.x * q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
        bank = atan2(q.x*q.y + q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
    }
}

//---------------------------------------------------------------------------
//EulerAngles::fromInertialToObjectQuaternion
//从惯性-物体四元数到欧拉角
//

void EulerAngles::fromInertialToObjectQuaternion(const Quaternion &q)
{
    //计算sin（pitch）

    float sp = -2.0f * (q.y*q.z +q.w*q.x);

    //检查万向锁，允许一定误差

    if(fabs(sp) > 0.9999f)
    {
        //从正上方或正下方看

        pitch = kPiOver2 * sp;

        //bank置零，计算heading

        heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
        bank = 0.0f;
    }
    else
    {
        //计算角度

        pitch = asin(sp);
        heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
        bank = atan2(q.x*q.y - q.w*q.z, 0.5f - q.x*q.x - q.z*q.z);
    }
}

//---------------------------------------------------------------------------
//EulerAngles::fromObjectToWorldMatrix
//从物体-世界坐标系变换矩阵到欧拉角
//假设矩阵是正交的，忽略平移部分
//
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
    //通过m32计算sin（pitch）

    float sp = -m.m32;

    //检查万向锁

    if(fabs(sp) > 0.9999f)
    {
        //向正上方或正下方看

        pitch = kPiOver2 * sp;

        //bank置零，计算heading

        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //计算角度

        heading = atan2(m.m31, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m12, m.m22);
    }
}

//---------------------------------------------------------------------------
//EulerAngles::fromWorldToObjectMatrix
//从世界-物体坐标系变换矩阵到欧拉角
//
//假设矩阵是正交的，忽略平移部分
//

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 &m)
{
    //根据m32计算sin(pitch)

    float sp = -m.m23;

    //检查万向锁

    if(fabs(sp) > 0.9999f)
    {
        //向正上方或正下方看

        pitch = kPiOver2 * sp;

        //bank置零，计算heading

        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //计算角度

        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}

//---------------------------------------------------------------------
//EulerAngles::fromRotationMatrix
//根据旋转矩阵构造欧拉角
//

void EulerAngles::fromRotationMatrix(const RotationMatrix &m)
{
    //根据m32计算sin(pitch)

    float sp = -m.m23;

    //检查万向锁

    if(fabs(sp) > 0.9999f)
    {
        //向正上方或正下方看

        pitch = kPiOver2 * sp;

        //bank置零，计算heading

        heading = atan2(-m.m31, m.m11);
        bank = 0.0f;
    }
    else
    {
        //计算角度

        heading = atan2(m.m13, m.m33);
        pitch = asin(sp);
        bank = atan2(m.m21, m.m22);
    }
}
