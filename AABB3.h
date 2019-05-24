////////////////////////////////////////////////////////////////////////
//
//3D Math Primer for Graphics and Game Development//
//
//AABB3.h - Declarations for class AABB3
//
//For more details, see AABB3.cpp
//
////////////////////////////////////////////////////////////////////////
#ifndef AABB3_H_INCLUDED
#define AABB3_H_INCLUDED
#ifndef VECTOR_H_INCLUDED
#include "Vector3.h"
#endif // VECTOR_H_INCLUDED

class Matrix4x3;
//-----------------------------------------------------------------------
//ʵ��3D��������߽����
class AABB3
{
public:
    //��������
    //��С������㣬�ǳ���
    Vector3 min;
    Vector3 max;

    //��ѯ���ֲ���
    Vector3 size() const {return max - min;}
    float xSize() {return max.x - min.x;}
    float ySize() {return max.y - min.y;}
    float zSize() {return max.z - min.z;}
    Vector3 center() const {return (min + max) * .5f;}
    //��ȡ8�������е�һ�����ο�.cpp�ļ��е�ı��
    Vector3 corner(int i) const;
    //����߽�����
    //��վ���߽��
    void empty();
    //�����߽������ӵ�
    void add(const Vector3 &p);
    //�����߽�������AABB
    void add(const AABB3 &box);
    //�任����߽�򣬼����µ�AABB
    void setToTransformedBox(const AABB3 &box, const Matrix4x3 &m);
    //����/�ཻ�Բ���
    //����true��������α߽��Ϊ��
    bool isEmpty() const;
    //����true��������α߽������õ�
    bool contains(const Vector3 &p) const;
    //���ؾ��α߽���ϵ������
    Vector3 closestPointTo(const Vector3 &p) const;
    //����true����������ཻ
    bool intersectsSphere(const Vector3 &center, float radius) const;
    //�Ͳ������ߵ��ཻ�Բ��ԣ�������ཻ�򷵻�ֵ����1
    float rayIntersect(const Vector3 &rayOrg, const Vector3 &rayDelta,
                       Vector3 *returnNormal = 0) const;
    //�жϾ���߽����ƽ�����һ��
    int classifyPlane(const Vector3 &n, float d) const;
    //��ƽ��Ķ�̬�ཻ�Բ���
    float intersectPlane(const Vector3 &n, float planeD, const Vector3 &dir) const;

};
//�������AABB���ཻ�ԣ�����ཻ����true�������Է����ཻ���ֵ�AABB
bool intersectAABBs(const AABB3 &box1, const AABB3 &box2, AABB3 *boxIntersect = 0);

//�����˶�AABB�;�ֹAABB�ཻʱ�Ĳ����㣬������ཻ�򷵻�ֵ����1
float intersectMovingAABB(
                        const AABB3 &stationaryBox,
                        const AABB3 &movingBox,
                        const Vector3 &d
                        );
////////////////////////////////////////////////////////////////////////
#endif // AABB3_H_INCLUDED
