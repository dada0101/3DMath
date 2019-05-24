#ifndef GRAPHICALMATH_H_INCLUDED
#define GRAPHICALMATH_H_INCLUDED

class Vector3;

//未变换，没有光照的顶点
struct RenderVertex
{
    Vector3 p;    //坐标
    Vector3 n;    //法向量
    float u,v;    //纹理映射坐标
};

//变换后，有光照顶点
struct RenderVertexTL
{
    Vertor3 p;              //屏幕坐标和深度
    float w;                //1/z
    unsigned argb;          //漫反射
    unsigned spec;          //镜面反射
    float u,v;              //纹理映射坐标
};

//未变换，有光照的顶点
struct RenderVertexL
{
    Vector3 p;              //坐标
    unsigned argb;          //漫反射
    unsigned spec;          //镜面反射
    float u,v;              //纹理映射坐标
};

#endif // GRAPHICALMATH_H_INCLUDED
