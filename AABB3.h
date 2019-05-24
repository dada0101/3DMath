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
//实现3D轴对齐矩阵边界框类
class AABB3
{
public:
    //公共数据
    //最小点和最大点，非常简单
    Vector3 min;
    Vector3 max;

    //查询各种参数
    Vector3 size() const {return max - min;}
    float xSize() {return max.x - min.x;}
    float ySize() {return max.y - min.y;}
    float zSize() {return max.z - min.z;}
    Vector3 center() const {return (min + max) * .5f;}
    //提取8个顶点中的一个，参考.cpp文件中点的编号
    Vector3 corner(int i) const;
    //矩阵边界框操作
    //清空矩阵边界框
    void empty();
    //向矩阵边界框中添加点
    void add(const Vector3 &p);
    //向矩阵边界框中添加AABB
    void add(const AABB3 &box);
    //变换矩阵边界框，计算新的AABB
    void setToTransformedBox(const AABB3 &box, const Matrix4x3 &m);
    //包含/相交性测试
    //返回true，如果矩形边界框为空
    bool isEmpty() const;
    //返回true，如果矩形边界框包含该点
    bool contains(const Vector3 &p) const;
    //返回矩形边界框上的最近点
    Vector3 closestPointTo(const Vector3 &p) const;
    //返回true，如果和求相交
    bool intersectsSphere(const Vector3 &center, float radius) const;
    //和参数射线的相交性测试，如果不相交则返回值大于1
    float rayIntersect(const Vector3 &rayOrg, const Vector3 &rayDelta,
                       Vector3 *returnNormal = 0) const;
    //判断矩阵边界框在平面的哪一面
    int classifyPlane(const Vector3 &n, float d) const;
    //和平面的动态相交性测试
    float intersectPlane(const Vector3 &n, float planeD, const Vector3 &dir) const;

};
//检测两个AABB的相交性，如果相交返回true，还可以返回相交部分的AABB
bool intersectAABBs(const AABB3 &box1, const AABB3 &box2, AABB3 *boxIntersect = 0);

//返回运动AABB和静止AABB相交时的参数点，如果不相交则返回值大于1
float intersectMovingAABB(
                        const AABB3 &stationaryBox,
                        const AABB3 &movingBox,
                        const Vector3 &d
                        );
////////////////////////////////////////////////////////////////////////
#endif // AABB3_H_INCLUDED
