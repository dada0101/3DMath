#ifndef GEOMETRICPRIMITIVES_H_INCLUDED
#define GEOMETRICPRIMITIVES_H_INCLUDED

//����ͼԪ������㷨

//����㼯�����ƽ��
class Vector3;

Vector3 computeBestFitNormal(const Vector3 v[], int n);

//����3D����������������
bool computeBarycentricCoords3d(const Vector3 v[3], const Vector3 &p, float b[3]);

//3D���ýǶȺ��ж�͹�����
bool isConvex(int n, const Vector3 v1[]);

#endif // GEOMETRICPRIMITIVES_H_INCLUDED
