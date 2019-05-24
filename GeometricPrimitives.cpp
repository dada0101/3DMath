#include "Vector3.h"
#include "MathUtil.h"
#include "GeometricPrimitives.h"
//------------------------------------------------------------
//computeBestFitNormal
//
//����㼯�����ƽ��
Vector3 computeBestFitNormal(const Vector3 v[], int n)
{
    //������
    Vector3 result = kZeroVector;
    //�����һ�����㿪ʼ��������ѭ������if�ж�
    const Vector3 *p = &v[n-1];
    //�������ж���
    for(int i = 0; i < n; ++i)
    {
        //�õ���ǰ����
        const Vector3 *c = &v[i];
        //�������˻����
        result.x += (p->z + c->z) * (p->y - c->y);
        result.y += (p->x + c->x) * (p->z - c->z);
        result.z += (p->y + c->y) * (p->x - c->x);
        //��һ������
        p = c;
    }
    //���򻯽��������
    result.normalize();
    return result;
}

//------------------------------------------------------------
//computeBarycentricCoords3d
//
//����3D����������������
bool computeBarycentricCoords3d(const Vector3 v[3],         //�����ζ���
                                const Vector3 &p,           //Ҫ����������ĵ�
                                float b[3])                 //������������
{
    //���ȣ�������������������˳ʱ�뷽��
    Vector3 d1 = v[1] - v[0];
    Vector3 d2 = v[2] - v[1];
    //�ò�˼��㷨�������������£���һ��������ʡ�ԣ���Ϊ��������Ԥ�ȼ����
    //����Ҫ���򻯣�����Ԥ�ȼ���ķ������Ƿ����򻯹���
    Vector3 n = crossProduct(d1, d2);

    //�жϷ�������ռ���Ƶ��ᣬѡ��ͶӰƽ��
    float u1, u2, u3, u4;
    float v1, v2, v3, v4;

    if((fabs(n.x) >= fabs(n.y)) && (fbs(n.x) >= fabs(n.z))
    {
        //����x����yzƽ��ͶӰ
        u1 = v[0].y - v[2].y;
        u2 = v[1].y - v[2].y;
        u3 = p.y - v[0].y;
        u4 = p.y - v[2].y;
        v1 = v[0].z - v[2].z;
        v2 = v[1].z - v[2].z;
        v3 = p.z - v[0].z;
        v4 = p.z - v[2].z;
    }
    else if(fabs(n.y) >= fabs(n.z))
    {
        //����y����xzƽ��ͶӰ
        u1 = v[0].z - v[2].z;
        u2 = v[1].z - v[2].z;
        u3 = p.z - v[0].z;
        u4 = p.z - v[2].z;
        v1 = v[0].x - v[2].x;
        v2 = v[1].x - v[2].x;
        v3 = p.x - v[0].x;
        v4 = p.x - v[2].x;
    }
    else
    {
        u1 = v[0].x - v[2].x;
        u2 = v[1].x - v[2].x;
        u3 = p.x - v[0].x;
        u4 = p.x - v[2].x;
        v1 = v[0].y - v[2].y;
        v2 = v[1].y - v[2].y;
        v3 = p.y - v[0].y;
        v4 = p.y - v[2].y;
    }

    //�����ĸ�����ж��Ƿ�Ϸ�
    float denom = v1 * u2 - v2 * u1;
    if(denom == 0.0f)
    {
        //�˻�������-���Ϊ���������
        return false;
    }

    //������������
    float oneOverDenom = 1.0f / denom;
    b[0] = (v4*u2 - v2*u4) * oneOverDenom;
    b[1] = (v1*u3 - v3*u1) * oneOverDenom;
    b[2] = 1.0f - b[0] - b[1];

    //OK
    return true;
}

//------------------------------------------------------------
//isConvex
//
//�ж϶�����Ƿ�Ϊ͹����Σ�����������ƽ���
//���룺
//n ������Ŀ
//v1 ָ�򶥵������ָ��
bool isConvex(int n, const Vector3 v1[])
{
    //�ͳ�ʼ��Ϊ��
    float angleSum = 0.0f;
    //������������Σ����Ƕ����
    for(int i = 0; i < n; ++i)
    {
        //�����������������Ϣ��һ�������һ�����㣬��Ȼ�����Ż������
        Vector3 e1;
        if(i == 0)
            e1 = v1[n-1] - v1[i];
        else
            e1 = v1[i-1] - v1[i];

        Vector3 e2;
        if(i == n-1)
            e2 = v[0] - v[i];
        else
            e2 = v[i+1] - v[i];

        //��׼����������
        e1.normalize();
        e2.normalize();
        float dot = e1 * e2;
        //�����С�Ľǣ��ð�ȫ�����Ǻ��������ⷢ����ֵ��������
        float theta = safeAcos(dot);
        //�Ӻ�
        angleSum += theta;
    }

    //�����ڽǺ�
    float convexAngleSum = (float)(n - 2) * kPi;

    //���ڿ����жϰ�͹�ԣ�����һЩ������ֵ���
    if(angleSum < convexAngleSum - (float)n * 0.0001f)
    {
        //�������
        return false;
    }
    //i͹����Σ���һ�����
    return true;
}
