#include "Vector3.h"
#include "MathUtil.h"
#include "GeometricPrimitives.h"
//------------------------------------------------------------
//computeBestFitNormal
//
//计算点集的最佳平面
Vector3 computeBestFitNormal(const Vector3 v[], int n)
{
    //和置零
    Vector3 result = kZeroVector;
    //从最后一个顶点开始，避免在循环中做if判断
    const Vector3 *p = &v[n-1];
    //迭代所有顶点
    for(int i = 0; i < n; ++i)
    {
        //得到当前顶点
        const Vector3 *c = &v[i];
        //边向量乘积相加
        result.x += (p->z + c->z) * (p->y - c->y);
        result.y += (p->x + c->x) * (p->z - c->z);
        result.z += (p->y + c->y) * (p->x - c->x);
        //下一个顶点
        p = c;
    }
    //正则化结果并返回
    result.normalize();
    return result;
}

//------------------------------------------------------------
//computeBarycentricCoords3d
//
//计算3D中任意点的重心坐标
bool computeBarycentricCoords3d(const Vector3 v[3],         //三角形顶点
                                const Vector3 &p,           //要求重心坐标的点
                                float b[3])                 //保存重心坐标
{
    //首先，计算两个边向量，呈顺时针方向
    Vector3 d1 = v[1] - v[0];
    Vector3 d2 = v[2] - v[1];
    //用叉乘计算法向量，许多情况下，这一步都可以省略，因为法向量是预先计算的
    //不需要正则化，不管预先计算的法向量是否正则化过。
    Vector3 n = crossProduct(d1, d2);

    //判断法向量中占优势的轴，选择投影平面
    float u1, u2, u3, u4;
    float v1, v2, v3, v4;

    if((fabs(n.x) >= fabs(n.y)) && (fbs(n.x) >= fabs(n.z))
    {
        //抛弃x，向yz平面投影
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
        //抛弃y，向xz平面投影
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

    //计算分母，并判断是否合法
    float denom = v1 * u2 - v2 * u1;
    if(denom == 0.0f)
    {
        //退化三角形-面积为零的三角形
        return false;
    }

    //计算重心坐标
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
//判断多边形是否为凸多边形，假设多边形是平面的
//输入：
//n 顶点数目
//v1 指向顶点数组的指针
bool isConvex(int n, const Vector3 v1[])
{
    //和初始化为零
    float angleSum = 0.0f;
    //遍历整个多边形，将角度相加
    for(int i = 0; i < n; ++i)
    {
        //计算边向量，必须消息第一个和最后一个顶点，当然还有优化的余地
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

        //标准化并计算点乘
        e1.normalize();
        e2.normalize();
        float dot = e1 * e2;
        //计算较小的角，用安全反三角函数，避免发生数值精度问题
        float theta = safeAcos(dot);
        //加和
        angleSum += theta;
    }

    //计算内角和
    float convexAngleSum = (float)(n - 2) * kPi;

    //现在可以判断凹凸性，允许一些经验数值误差
    if(angleSum < convexAngleSum - (float)n * 0.0001f)
    {
        //凹多边形
        return false;
    }
    //i凸多边形，有一定误差
    return true;
}
