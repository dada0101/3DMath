#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

//////////////////////////////////////////////////////////////
//
//3D Math Primer for Games and Graphics Development
//
//Quaternion.h - Declaretions for class Quaternion
//
//For more details, see Quaternion.cpp
//
//////////////////////////////////////////////////////////////

class Vector3;
class EulerAngles;

//---------------------------------------------------------------
//Quaternion��
//ʵ����3D�б�ʾ��λ�Ƶ���Ԫ��

class Quaternion
{
public:
    //��������

    //��Ԫ�����ĸ�ֵ��ͨ���ǲ���Ҫֱ�Ӵ������ǵ�
    //Ȼ����Ȼ����������Ϊpublic������Ϊ�˲���ĳЩ���������ļ�I/O����������Ҫ�ĸ�����

    float w, x, y, z;

    //��������

    //��Ϊ��λ��Ԫ��

    void identify() {w = 1; x = y = z = 0;}

    //����ִ����ת����Ԫ��

    void setToRotateAboutX(float theta);
    void setToRotateAboutY(float theta);
    void setToRotateAboutZ(float theta);
    void setToRotateAboutAxis(const Vector3 &axis, float theta);

    //����ִ������-������ת����Ԫ������λ������ŷ������ʽ����

    void setToRotateObjectToInertial(const EulerAngles &orientation);
    void setToRotateInertialToObject(const EulerAngles &orientation);

    //���

    Quaternion operator * (const Quaternion &a) const;

    //��ֵ�˷������Ƿ���C++ϰ�ߵ�д��

    Quaternion &operator *= (const Quaternion &a);

    //����Ԫ������

    void normalize();

    //��ȡ��ת�Ǻ���ת��

    float getRotationAngle() const;
    Vector3 getRotationAxis() const;
};

//ȫ�ֵ�λ��Ԫ��

extern const Quaternion kQuaternionIdentify;

//��Ԫ�����

extern float dotProduct(const Quaternion &a, const Quaternion &b);

//�������Բ�ֵ

extern Quaternion slerp(const Quaternion &p, const Quaternion &q, float t);

//��Ԫ������

extern Quaternion conjugate(const Quaternion &q);

//��Ԫ����

extern Quaternion pow(const Quaternion &q, float exponent);

//////////////////////////////////////////////////////////////
#endif // QUATERNION_H_INCLUDED
