#ifndef GEOMETRICTESTING_H_INCLUDED
#define GEOMETRICTESTING_H_INCLUDED

//�ж�����ƽ�����һ��
int classifySpherePlane(const Vector3 &planeNormal,
                        float planeD,
                        const Vector3 &sphereCenter,
                        float sphereRadius);

//�����������ε��ཻ�Լ�⣬�㷨����Didier Badouel��Graphics Gess I��pp 390-393
float rayTriangleIntersect(
const Vector3 &rayOrg,          //�����ߵ�
const Vector3 &rayDelta,        //���߳��Ⱥͷ���
const Vector3 &p0,              //�����ζ���
const Vector3 &p1,              //.
const Vector3 &p2,              //.
float minT                      //ĿǰΪֹ����ĵ㣬��1.0��ʼ
);

#endif // GEOMETRICTESTING_H_INCLUDED
