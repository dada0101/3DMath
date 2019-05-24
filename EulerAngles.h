///////////////////////////////////////////////////////////////////////////
//
//3D Math Primer for Games and Graphics Development
//
//EulerAngles.h - Declarations for class EulerAngles
//
//for more details, see EulerAngles.cpp
//
///////////////////////////////////////////////////////////////////////////

#ifndef EULERANGLES_H_INCLUDED
#define EULERANGLES_H_INCLUDED

//Ԥ����

class Quaternion;
class Matrix4x3;
class RotationMatrix;

//---------------------------------------------------------------------
// class EulerAngles
//
//�������ڱ�ʾheading-pitch-bankŷ����ϵͳ

class EulerAngles
{
public:
    //��������

    //ֱ�ӵı�ʾ��ʽ
    //�û��ȱ��������Ƕ�
    float heading;
    float pitch;
    float bank;

    //��������
    //ȱʡ���캯��
    EulerAngles(){}

    //������������
    EulerAngles(float h, float p, float b):heading(h),
    pitch(p), bank(b){}
    //����
    void identify() {heading = pitch = bank = 0.0f;}
    //�任Ϊ���Ƽ�ŷ����
    void canonize();

    //����Ԫ��ת����ŷ����
    //�������Ԫ������Ϊ����-���Ի����-������Ԫ������������ʾ��
    void fromObjectToInertialQuaternion(const Quaternion &q);
    void fromInertialToObjectQuaternion(const Quaternion &q);

    //�Ӿ���ת����ŷ����
    //����������Ϊ����-���������-����ת������
    //ƽ�Ʋ��ֱ�ʡ�ԣ����Ҽ��������������
    void fromObjectToWorldMatrix(const Matrix4x3 &m);
    void fromWorldToObjectMatrix(const Matrix4x3 &m);

    //����ת����ת����ŷ����
    void fromRotationMatrix(const RotationMatrix &m);
};

//ȫ�ֵĵ�λŷ����
extern const EulerAngles kEulerAnglesIdentify;

#endif // EULERANGLES_H_INCLUDED
