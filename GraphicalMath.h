#ifndef GRAPHICALMATH_H_INCLUDED
#define GRAPHICALMATH_H_INCLUDED

class Vector3;

//δ�任��û�й��յĶ���
struct RenderVertex
{
    Vector3 p;    //����
    Vector3 n;    //������
    float u,v;    //����ӳ������
};

//�任���й��ն���
struct RenderVertexTL
{
    Vertor3 p;              //��Ļ��������
    float w;                //1/z
    unsigned argb;          //������
    unsigned spec;          //���淴��
    float u,v;              //����ӳ������
};

//δ�任���й��յĶ���
struct RenderVertexL
{
    Vector3 p;              //����
    unsigned argb;          //������
    unsigned spec;          //���淴��
    float u,v;              //����ӳ������
};

#endif // GRAPHICALMATH_H_INCLUDED
