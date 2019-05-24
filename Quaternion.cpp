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
//全局数据
//
//////////////////////////////////////////////////////////////////////////
//全局单位四元数，注意Quaternion类没有构造函数，因为我们并不需要。

const Quaternion kQuaternionIdentify = {1.0f, 0.0f, 0.0f, 0.0f};

//////////////////////////////////////////////////////////////////////////
//
//Quaternion类成员
//
//////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------
//Quaternion::setToRotateAboutX
//Quaternion::setToRotateAboutY
//Quaternion::setToRotateAboutZ
//Quaternion::setToRotateAboutAxis
//构造绕指定轴旋转的四元数

void Quaternion::setToRotateAboutX(float theta)
{
    //计算半角

    float thetaOver2 = theta * .5f;

    //赋值

    w = cos(thetaOver2);
    x = sin(thetaOver2);
    y = 0.0f;
    z = 0.0f;
}

void Quaternion::setToRotateAboutY(float theta)
{
    //计算半角

    float thetaOver2 = theta * .5f;

    //赋值

    w = cos(thetaOver2);
    x = 0.0f;
    y = sin(thetaOver2);
    z = 0.0f;
}

void Quaternion::setToRotateAboutZ(float theta)
{
    //计算半角

    float thetaOver2 = theta * .5f;

    //赋值

    w = cos(thetaOver2);
    x = 0.0f;
    y = 0.0f;
    z = sin(thetaOver2);
}

void Quaternion::setToRotateAboutAxis(const Vector3 &axis, float theta)
{
    //旋转轴必须标准化

    assert(fabs(vectorMsg(axis) - 1.0f) < .01f);

    //计算半角和sin值

    float thetaOver2 = theta * .5f;
    float sinThetaOver2 = sin(thetaOver2);

    //赋值

    w = cos(thetaOver2);
    x = axis.x * sinThetaOver2;
    y = axis.y * sinThetaOver2;
    z = axis.z * sinThetaOver2;
}

//------------------------------------------------------------------------
//Quaternion::setToRotateObjectToInertial
//构造执行物体-惯性旋转的四元数
//
//方位参数由欧拉角形式给出
void Quaternion::setToRotateObjectToInertial(const EulerAngles &orientation)
{
    //计算半角的sin和cos值

    float sp, sh, sb;
    float cp, ch, cb;

    sinCos(&sp, &cp, orientation.pitch * .5f);
    sinCos(&sb, &cb, orientation.bank * .5f);
    sinCos(&sh, &ch, orientation.heading * .5f);

    //计算结果

    w = ch*cp*cb + sh*sp*sb;
    x = ch*sp*cb + sh*cp*sb;
    y = -ch*sp*sb + sh*cb*cp;
    z = -sh*sp*cb + ch*cp*sb;
}

//------------------------------------------------------------------------
//Quaternion::setToRotateInertialToObject
//构造执行惯性-物体旋转的四元数
//
//方位参数由欧拉角形式给出

void Quaternion::setToRotateInertialToObject(const EulerAngles &orientation)
{
    //计算半角的sin和cos值

    float sp, sh, sb;
    float cp, ch, cb;
    sinCos(&sp, &cp, orientation.pitch * .5f);
    sinCos(&sb, &cb, orientation.bank * .5f);
    sinCos(&sh, &ch, orientation.heading * .5f);

    //计算结果

    w = ch*cp*cb + sh*sp*sb;
    x = -ch*sp*cb - sh*cp*sb;
    y = ch*sp*sb - sh*cb*cp;
    z = sh*sp*cb - ch*cp*sb;
}

//------------------------------------------------------------------------
//Quaternion::operator*
//四元数叉乘运算，用以连接多个角位移
//乘的顺序是从左向右
//这和四元数叉乘的标准定义相反。

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
//叉乘并赋值，这是符合C++习惯写法的

Quaternion &Quaternion::operator *= (const Quaternion &a)
{
    *this = *this * a;
    return *this;
}

//------------------------------------------------------------------------
//Quaternion::normalize
//正则化四元数。
//通常，四元数都是正则化的。
//
//提供这个函数主要是为了防止误差扩大，连续多个四元数操作可能导致操作扩大。
//

void Quaternion::normalize()
{
    //计算四元数的模

    float msg = sqrt(w*w + x*x + y*y + z*z);

    //计算长度，防止除零错误

    if(msg > 0.0f)
    {
        //正则化

        float oneOverMsg = 1.0f / msg;
        w *= oneOverMsg;
        x *= oneOverMsg;
        y *= oneOverMsg;
        z *= oneOverMsg;
    }
    else
    {
        //有麻烦了

        assert(false);

        //在发布版中，返回单元四元数

        identify();
    }
}

//------------------------------------------------------------------------
//Quaternion::getRotationAngle
//返回旋转角

float Quaternion::getRotationAngle() const
{
    //计算半角，w = cos(theta / 2)

    float thetaOver2 = safeAcos(w);

    //返回旋转角

    return thetaOver2 * 2.0f;
}

//------------------------------------------------------------------------
//Quaternion::getRotationAxis
//提取旋转轴

Vector3 Quaternion::getRotationAxis() const
{
    //计算sin^2(theta/2)，记住w = cos(theta/2)，sin^2(x) + cos^2(x) = 1

    float sinThetaOver2Sq = 1.0f - w*w;;

    //注意保证数值精度

    if(sinThetaOver2Sq <= 0.0f)
    {
        //单位四元数或不基精确的数值，只要返回有效的向量即可

        return Vector3(1.0f, 0.0f, 0.0f);
    }

    //计算1/sin(theta.2)

    float oneOverSinThetaOver2 = 1 / sqrt(sinThetaOver2Sq);

    //返回旋转轴
    return Vector3(
        x * oneOverSinThetaOver2,
        y * oneOverSinThetaOver2,
        z * oneOverSinThetaOver2
        );
}

//////////////////////////////////////////////////////////////////
//
//非成员函数
//
//////////////////////////////////////////////////////////////////


//------------------------------------------------------------------------
//dotProduct
//四元数点乘
//用非成员函数实现四元数点乘以避免在表达式中使用时出现怪异语法。

float dotProduct(const Quaternion &a, const Quaternion &b)
{
    return a.w*b.w +a.x*b.x + a.y*b.y + a.z*b.z;
}

//------------------------------------------------------------------------
//slerp
//球面线性插值
//

Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t)
{
    //检查出界的参数，如果检查到，返回边界点

    if(t <= 0.0f)
        return q0;
    if(t >= 1.0f)
        return q1;

    //用点乘计算四元数夹角的cos值

    float cosOmega = dotProduct(q0, q1);

    //如果点乘为负，使用-q1
    //四元数q和-q代表相同的旋转，但可能产生不同的slerp运算，我们要选择正确的一个
    //以便用锐角进行旋转。

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

    //我们用的是两个单位四元数，所以点乘结果应该<=1.0

    assert(cosOmega < 1.1f);

    //计算插值片，注意检查非常接近的情况

    float k0, k1;
    if(cosOmega > 0.9999f)
    {
        //非常接近，即线性插值，防止除零

        k0 = 1.0f - t;
        k1 = t;
    }
    else
    {
        //用三角公式sin^2(omega) + cos^2(omega) = 1 计算sin值

        float sinOmega = sqrt(1.0f - cosOmega * cosOmega);

        //计算分母的倒数，这样只需要除一次

        float oneOverSinOmega = 1.0f / sinOmega;

        //根据sin和cos值计算角度

        float omega = atan2(sinOmega, cosOmega);

        //计算插值变量

        k0 = sin((1.0f - t) * omega) * oneOverSinOmega;
        k1 = sin(t * omega) * oneOverSinOmega;
    }

    //插值

    Quaternion result;

    result.w = k0*q0.w + k1*q1w;
    result.x = k0*q0.x + k1*q1x;
    result.y = k0*q0.y + k1*q1y;
    result.z = k0*q0.z + k1*q1z;

    //返回

    return result;
}

//------------------------------------------------------------------------
//conjugate
//四元数共轭，即与原四元数旋转方向相反的四元数
//

Quaternion conjugate(const Quaternion &q)
{
    Quaternion result;

    //旋转量相同

    result.w = q.w;

    //旋转轴相反

    result.x = -q.x;
    result.y = -q.y;
    result.z = -q.z;

    //返回

    return result;
}

//------------------------------------------------------------------------
//pow
//四元数幂
//

Quaternion pow(const Quaternion &q, float exponent)
{
    //检查单位四元数，防止除零

    if(fabs(q.w) > .9999f)
        return q;

    //提取半角alpha(alpha = theta/2)

    float alpha = acos(q.w);

    //计算新的alpha值

    float newAlpha = alpha * exponent;

    Quaternion result;

    //计算新w值

    result.w = cos(newAlpha);

    //计算新xyz值

    float mult = sin(newAlpha) / sin(alpha);
    result.x = q.x * mult;
    result.y = q.y * mult;
    result.z = q.z * mult;

    //返回

    return result;
}
