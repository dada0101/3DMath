/////////////////////////////////////////////////////
//
//3D Math Primer for Games and Graphics Development
//
//RotationMatrix.h - Declarations for class RotationMatrix
//
//For more details, see RotationMatrix.cop
//
/////////////////////////////////////////////////////

#ifndef ROTATIONMATRIX_H_INCLUDED
#define ROTATIONMATRIX_H_INCLUDED

class Vector3;
class EulerAngles;
class Quaternion;

//------------------------------------------------------
//RotationMatrix类
//实现了一个简单的3x3矩阵，仅用旋转
//矩阵假设是正交的，在变换时指定方向

class RotationMatrix
{
public:

    //Public data

    //矩阵的9个值

    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;

    //公共操作

    //置为单位矩阵

    void identify();

    //根据指定的方位构造矩阵

    void setup(const EulerAngles &orientation);

    //根据四元数构造矩阵，假设该四元数参数代表指定方向的变换

    void fromInertialToObjectQuaternion(const Quaternion &q);

    void fromObjectToInertialQuaternion(const Quaternion &q);

    //执行旋转

    Vector3 inertialToObject(const Vector3 &v) const;
    Vector3 objectToInertial(const Vector3 &v) const;
};

/////////////////////////////////////////////////////
#endif // ROTATIONMATRIX_H_INCLUDED
