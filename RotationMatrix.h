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
//RotationMatrix��
//ʵ����һ���򵥵�3x3���󣬽�����ת
//��������������ģ��ڱ任ʱָ������

class RotationMatrix
{
public:

    //Public data

    //�����9��ֵ

    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;

    //��������

    //��Ϊ��λ����

    void identify();

    //����ָ���ķ�λ�������

    void setup(const EulerAngles &orientation);

    //������Ԫ��������󣬼������Ԫ����������ָ������ı任

    void fromInertialToObjectQuaternion(const Quaternion &q);

    void fromObjectToInertialQuaternion(const Quaternion &q);

    //ִ����ת

    Vector3 inertialToObject(const Vector3 &v) const;
    Vector3 objectToInertial(const Vector3 &v) const;
};

/////////////////////////////////////////////////////
#endif // ROTATIONMATRIX_H_INCLUDED
