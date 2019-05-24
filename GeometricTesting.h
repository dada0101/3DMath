#ifndef GEOMETRICTESTING_H_INCLUDED
#define GEOMETRICTESTING_H_INCLUDED

//判断求在平面的哪一边
int classifySpherePlane(const Vector3 &planeNormal,
                        float planeD,
                        const Vector3 &sphereCenter,
                        float sphereRadius);

//射线与三角形的相交性检测，算法来自Didier Badouel，Graphics Gess I，pp 390-393
float rayTriangleIntersect(
const Vector3 &rayOrg,          //射线七点
const Vector3 &rayDelta,        //射线长度和方向
const Vector3 &p0,              //三角形顶点
const Vector3 &p1,              //.
const Vector3 &p2,              //.
float minT                      //目前为止最近的点，从1.0开始
);

#endif // GEOMETRICTESTING_H_INCLUDED
