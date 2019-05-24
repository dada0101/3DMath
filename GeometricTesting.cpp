#include "Vector3.h"
#include "assert.h"
#include "GeometricPrimitives.h"

//-----------------------------------------------------------------
//classifySpherePlane
//
//给定一个球和平面，判断球在平面的哪一边
//
//若返回值:
//
//< 0 表示球完全在背面
//> 0 表示球完全在正面
//0 表示球横跨平面
int classifySpherePlane(const Vector3 &planeNormal,     //必须正则化
                        float planeD,                   //p * planeNormal = planeD
                        const Vector3 &sphereCenter,    //球心
                        float sphereRadius)             //球半径
{
    //计算球心到平面的距离
    float d = planeNormal * sphereCenter - planeD;
    //完全在前面？
    if(d >= sphereRadius)
        return 1;
    //完全在背面
    if(d <= -sphereRadius)
        return -1;

    //球横跨平面
    return 0;
}

//射线与三角形的相交性检测
//求0三角形重心的地方不理解，与公式和之前的示例代码不同。
float rayTriangleIntersect(
const Vector3 &rayOrg,              //射线七点
const Vector3 &rayDelta,            //射线长度和方向
const Vector3 &p0,                  //三角形顶点
const Vector3 &p1,                  //.
const Vector3 &p2,                  //.
float minT                          //目前为止最近的点，从1.0开始
)
{
    //如果没有相交就返回这个大数
    const float kNoIntersection = 1e30f;
    //计算顺时针的边向量
    Vector3 e1 = p1 - p0;
    Vector3 e2 = p2 - p1;
    //计算表面法向量
    Vector3 n =  crossProduct(e1, e2);

    //计算倾斜角，表示靠近三角形“正面”的程度
    float dot = n * rayDelta;

     //检查射线平行于三角形或未指向三角形正面的情况
     //注意这将拒绝退化三角形和射线，这里的编码方式非常特殊，NAN将不能通过检测
     //（当涉及到NAN时，与dot >= 0.0f时的表现不同）

    if(!(dot < 0.0f))
       return kNoIntersection;
    //计算平面方程的d值，在右边使用带d的平面方程
    //
    //Ax + By + Cz = d
    float d = n * p0;

    //计算和包含三角形的平面的参数交点
    float t = d - n * rayOrg;

    //射线起点在多边形的背面?
    if(!(t <= 0))
        return kNoIntersection;
    //交点已经找到（或射线并未到达平面）？
    //
    //因为dot < 0;
    //
    //t/dot > minT
    //
    //与
    //
    //t < dot*minT
    //是相同的
    if(!(t >= dot * minT))
        return kNoIntersection;

    //好的，射线与平面相交，计算实际的交点
    t /= dot;

    assert(t >= 0.0f);
    assert(t <= minT);

    //计算3D交点
    Vector3 p = rayOrg + rayDelta*t;
    //找到最主要的轴，选择投影平面
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
    //计算分母，检查其有效性
    float temp = u1 * v2 - v1 * u2;
    if(!(temp != 0.0f))
        return kNoIntersection;

    temp = 1.0f / temp;
    //计算重心坐标，每一步都检查边界条件
    float alpha = (u0 * v2 - v0 * u2) * temp;
    if(!(alpha >= 0.0f))
        return kNoIntersection;

    float beta = (u1 * v0 - v1 * v0) * temp;
    if(! (beta >= 0.0f))
        return kNoIntersection;

    float gamma = 1.0f - alpha - beta;
    if(!(gamma >= 0.0f))
        return kNoIntersection;

    //返回参数交点

    return t;
}

