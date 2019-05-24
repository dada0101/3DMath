#ifndef GEOMETRICPRIMITIVES_H_INCLUDED
#define GEOMETRICPRIMITIVES_H_INCLUDED

//几何图元的相关算法

//计算点集的最佳平面
class Vector3;

Vector3 computeBestFitNormal(const Vector3 v[], int n);

//计算3D中任意点的中心坐标
bool computeBarycentricCoords3d(const Vector3 v[3], const Vector3 &p, float b[3]);

//3D中用角度和判断凸多边形
bool isConvex(int n, const Vector3 v1[]);

#endif // GEOMETRICPRIMITIVES_H_INCLUDED
