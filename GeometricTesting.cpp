#include "Vector3.h"
#include "assert.h"
#include "GeometricPrimitives.h"

//-----------------------------------------------------------------
//classifySpherePlane
//
//����һ�����ƽ�棬�ж�����ƽ�����һ��
//
//������ֵ:
//
//< 0 ��ʾ����ȫ�ڱ���
//> 0 ��ʾ����ȫ������
//0 ��ʾ����ƽ��
int classifySpherePlane(const Vector3 &planeNormal,     //��������
                        float planeD,                   //p * planeNormal = planeD
                        const Vector3 &sphereCenter,    //����
                        float sphereRadius)             //��뾶
{
    //�������ĵ�ƽ��ľ���
    float d = planeNormal * sphereCenter - planeD;
    //��ȫ��ǰ�棿
    if(d >= sphereRadius)
        return 1;
    //��ȫ�ڱ���
    if(d <= -sphereRadius)
        return -1;

    //����ƽ��
    return 0;
}

//�����������ε��ཻ�Լ��
//��0���������ĵĵط�����⣬�빫ʽ��֮ǰ��ʾ�����벻ͬ��
float rayTriangleIntersect(
const Vector3 &rayOrg,              //�����ߵ�
const Vector3 &rayDelta,            //���߳��Ⱥͷ���
const Vector3 &p0,                  //�����ζ���
const Vector3 &p1,                  //.
const Vector3 &p2,                  //.
float minT                          //ĿǰΪֹ����ĵ㣬��1.0��ʼ
)
{
    //���û���ཻ�ͷ����������
    const float kNoIntersection = 1e30f;
    //����˳ʱ��ı�����
    Vector3 e1 = p1 - p0;
    Vector3 e2 = p2 - p1;
    //������淨����
    Vector3 n =  crossProduct(e1, e2);

    //������б�ǣ���ʾ���������Ρ����桱�ĳ̶�
    float dot = n * rayDelta;

     //�������ƽ���������λ�δָ����������������
     //ע���⽫�ܾ��˻������κ����ߣ�����ı��뷽ʽ�ǳ����⣬NAN������ͨ�����
     //�����漰��NANʱ����dot >= 0.0fʱ�ı��ֲ�ͬ��

    if(!(dot < 0.0f))
       return kNoIntersection;
    //����ƽ�淽�̵�dֵ�����ұ�ʹ�ô�d��ƽ�淽��
    //
    //Ax + By + Cz = d
    float d = n * p0;

    //����Ͱ��������ε�ƽ��Ĳ�������
    float t = d - n * rayOrg;

    //��������ڶ���εı���?
    if(!(t <= 0))
        return kNoIntersection;
    //�����Ѿ��ҵ��������߲�δ����ƽ�棩��
    //
    //��Ϊdot < 0;
    //
    //t/dot > minT
    //
    //��
    //
    //t < dot*minT
    //����ͬ��
    if(!(t >= dot * minT))
        return kNoIntersection;

    //�õģ�������ƽ���ཻ������ʵ�ʵĽ���
    t /= dot;

    assert(t >= 0.0f);
    assert(t <= minT);

    //����3D����
    Vector3 p = rayOrg + rayDelta*t;
    //�ҵ�����Ҫ���ᣬѡ��ͶӰƽ��
    float u0, u1, u2;
    float v0, v1, v2;

    if(fabs(n.x) > fabs(n.y))
    {
        if(fabs(n.x) > fabs(n.z))
        {
            u0 = p.y - p0.y;
            u1 = p1.y - p0.y;
            u2 = p2.y - p0.y;
            v0 = p.z - p0.z;
            v1 = p1.z - p0.z;
            v2 = p2.z - p0.z;
        }
        else
        {
            u0 = p.x - p0.x;
            u1 = p1.x - p0.x;
            u2 = p2.x - p0.x;
            v0 = p.y - p0.y;
            v1 = p1.y - p0.y;
            v2 = p2.y - p0.y;
        }
    }
    else
    {
        if(fabs(n.y) > fabs(n.z))
        {
            u0 = p.x - p0.x;
            u1 = p1.x - p0.x;
            u2 = p2.x - p0.x;
            v0 = p.z - p0.z;
            v1 = p1.z - p0.z;
            v2 = p2.z - p0.z;
        }
        else
        {
            u0 = p.x - p0.x;
            u1 = p1.x - p0.x;
            u2 = p2.x - p0.x;
            v0 = p.y - p0.y;
            v1 = p1.y - p0.y;
            v2 = p2.y - p0.y;
        }
    }
    //�����ĸ���������Ч��
    float temp = u1 * v2 - v1 * u2;
    if(!(temp != 0.0f))
        return kNoIntersection;

    temp = 1.0f / temp;
    //�����������꣬ÿһ�������߽�����
    float alpha = (u0 * v2 - v0 * u2) * temp;
    if(!(alpha >= 0.0f))
        return kNoIntersection;

    float beta = (u1 * v0 - v1 * v0) * temp;
    if(! (beta >= 0.0f))
        return kNoIntersection;

    float gamma = 1.0f - alpha - beta;
    if(!(gamma >= 0.0f))
        return kNoIntersection;

    //���ز�������

    return t;
}

