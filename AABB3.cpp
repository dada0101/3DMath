////////////////////////////////////////////////////////////
//
//3D Math Primer for Graphics and Game Development
//
//AABB3.cpp - Implementation for class AABB3
//
//For more details, see Chapter 12
//
////////////////////////////////////////////////////////////

#include <assert.h>
#include <stdlib.h>
#include <algorithm>
#include "AABB3.h"
#include "Matrix4x3.h"
#include "CommonStuff.h"

using std::max;
using std::min;
using std::swap;
////////////////////////////////////////////////////////////
//
//AABB3���Ա����
//
////////////////////////////////////////////////////////////
//------------------------------------------------------------
//AABB3::corner
//����8�������е�һ����������������ʾ��
//
//                  6                        7
//                     -------------------------
//                  /|                       /|
//                 / |                      / |
//                /  |                     /  |
//               /   |                    /   |
//              /    |                   /    |
//             /     |                  /     |
//            /      |                 /      |
//           /       |                /       |
//          /        |               /        |
//         2/        |              3/        |
//        /------------------------/          |
//        |          |             |          |
//        |          |             |          |    +Y
//        |         4|             |          |
//        |          |-------------|----------|     |
//        |         /              |         / 5    |
//        |        /               |        /      |      +Z
//        |       /                |       /       |
//        |      /                 |      /        |     /
//        |     /                  |     /         |    /
//        |    /                   |    /          |   /
//        |   /                    |   /           |  /
//        |  /                     |  /            | /
//        | /                      | /              |/
//        |/                       |/              -------------+X
//        --------------------------
//        0                        1
//
//��0λѡ��min.x vs. max.x
//��1λѡ��min.y vs. max.y
//��2λѡ��min.z vs. max.z

Vector3 AABB3::corner(int i) const
{
    //ȷ�������Ϸ�
    assert(i >= 0);
    assert(i <= 7);
    //���ص�
    return Vector3(
        (i & 1) ? max.x : min.x,
        (i & 2) ? max.y : min.y,
        (i & 4) ? max.y : min.y
    );
}

//------------------------------------------------------------
//AABB3::empty
//��ֵ��Ϊ����/��Сֵ����վ��α߽��
void AABB3::empty()
{
    const float kBigNumber = 1e37f;

    min.x = min.y = min.z = kBigNumber;
    max.x = max.y = max.z = -kBigNumber;
}
//------------------------------------------------------------
//AABB3::add
//����α߽���м�һ����
void AABB3::add(const Vector3 &p)
{
    //��Ҫ��ʱ�����ž��α߽���԰��������
    if(p.x < min.x)
        min.x = p.x;
    if(p.x > max.x)
        max.x = p.x;
    if(p.y < min.y)
        min.y = p.y;
    if(p.y > max.y)
        max.y = p.y;
    if(p.z < min.z)
        min.z = p.z;
    if(p.z > max.z)
        max.z = p.z;
}
//------------------------------------------------------------
//AABB3::add
//����α߽�������AAB
void AABB3::add(const AABB3 &box)
{
    //��Ҫ��ʱ�����ž��α߽��
    if(min.x > box.min.x)
        min.x = box.min.x;
    if(max.x < box.max.x)
        max.x = box.max.x;
    if(min.y > box.min.y)
        min.y = box.min.y;
    if(max.y < box.max.y)
        max.y = box.max.y;
    if(min.z > box.min.z)
        min.z = box.min.z;
    if(max.z < box.max.z)
        max.z = box.max.z;
}
//------------------------------------------------------------
//AABB3::setToTransformedBox
//�任���α߽�򲢼����µ�AABB
//��ס���⽫�õ�һ��������ԭAABBһ�����AABB�����Ķ��AABB
void AABB3::setToTransformedBox(const AABB3 &box, const Matrix4x3 &m)
{
    //���Ϊ�գ��򷵻�
    if(box.isEmpty())
    {
        empty();
        return;
    }
    //��ƽ�Ʋ��ֿ�ʼ
    min = max = getTranslation(m);
    //���μ������9��Ԫ�أ������µ�AABB
    if(m.m11 > 0.0f)
    {
        min.x += m.m11 * box.min.x;
        max.x += m.m11 * box.max.x;
    }
    else
    {
        min.x += m.m11 * box.max.x;
        max.x += m.m11 * box.min.x;
    }
    if(m.m12 > 0.0f)
    {
        min.y += m.m12 * box.min.x;
        max.y += m.m12 * box.max.x;
    }
    else
    {
        min.y += m.m12 * box.max.x;
        max.y += m.m12 * box.min.x;
    }
    if(m.m13 > 0.0f)
    {
        min.z += m.m13 * box.min.x;
        max.z += m.m13 * box.max.x;
    }
    else
    {
        min.z += m.m13 * box.max.x;
        max.z += m.m13 * box.min.x;
    }
    if(m.m21 > 0.0f)
    {
        min.x += m.m21 * box.min.y;
        max.x += m.m11 * box.max.y;
    }
    else
    {
        min.x += m.m21 * box.max.y;
        max.x += m.m21 * box.min.y;
    }
    if(m.m22 > 0.0f)
    {
        min.y += m.m22 * box.min.y;
        max.y += m.m22 * box.max.y;
    }
    else
    {
        min.y += m.m22 * box.max.y;
        max.y += m.m22 * box.min.y;
    }
    if(m.m23 > 0.0f)
    {
        min.z += m.m23 * box.min.y;
        max.z += m.m23 * box.max.y;
    }
    else
    {
        min.z += m.m23 * box.max.y;
        max.z += m.m23 * box.min.y;
    }
    if(m.m31 > 0.0f)
    {
        min.x += m.m31 * box.min.z;
        max.x += m.m31 * box.max.z;
    }
    else
    {
        min.x += m.m31 * box.max.z;
        max.x += m.m31 * box.min.z;
    }
    if(m.m32 > 0.0f)
    {
        min.y += m.m32 * box.min.z;
        max.y += m.m32 * box.max.z;
    }
    else
    {
        min.y += m.m32 * box.max.z;
        max.y += m.m32 * box.min.z;
    }
    if(m.m33 > 0.0f)
    {
        min.z += m.m33 * box.min.z;
        max.z += m.m33 * box.max.z;
    }
    else
    {
        min.z += m.m33 * box.max.z;
        max.z += m.m33 * box.min.z;
    }
}
//------------------------------------------------------------
//AABB3::isEmpty
//���Ϊ���򷵻�true
bool AABB3::isEmpty() const
{
    //����Ƿ���ĳ�����Ϸ�������
    return (min.x > max.x) || (min.y > max.y) || (min.z > max.z);
}
//------------------------------------------------------------
//AABB3::contains
//��������õ��򷵻�true
bool AABB3::contains(const Vector3 &p) const
{
    //���ÿ�������Ƿ�����ص�����
    return
     (p.x >= min.x) && (p.x <= max.x) &&
      (p.y >= min.y) && (p.y <= max.y) &&
      (p.z >= min.z) && (p.z <= max.z);
}
//------------------------------------------------------------
//AABB3::closestPointTo
//����AABB�ϵ������
Vector3 AABB3::closestPointTo(const Vector3 &p) const
{
    //��ÿһά�Ͻ�p������α߽��
    Vector3 r;

    if(p.x < min.x)
        r.x = min.x;
    else if(p.x > max.x)
        r.x = max.x;
    else
        r.x = p.x;
    if(p.y < min.y)
        r.y = min.y;
    else if(p.y > max.y)
        r.y = max.y;
    else
        r.y = p.y;
    if(p.z < min.z)
        r.z = min.z;
    else if(p.z > max.z)
        r.z = max.z;
    else
        r.z= p.z;

    //����
    return r;
}
//------------------------------------------------------------
//AABB3::intersectsSphere
//�����ཻ�򷵻�true��ʹ��Arvo���㷨

bool AABB3::intersectsSphere(const Vector3 &center, float radius) const
{
    //�ҵ����α߽��������������ĵ�
    Vector3 closestPoint = closestPointTo(center);
    //������������ĵľ����Ƿ�С�ڰ뾶
    return distanceSquared(center, closestPoint) < radius*radius;
}

//------------------------------------------------------------
//AABB3::rayIntersect
//�Ͳ��������ཻ������ཻ�Ļ�����0��1֮��Ĳ���ֵ�����򷵻ش���1��ֵ
//�㷨����Woo�� ������������α߽���ཻ�Լ�ⷽ��
float AABB3::rayIntersect(
                          const Vector3 &rayOrg,        //�������
                          const Vector3 &rayDelta,      //���߳��Ⱥͷ���
                          Vector3 *returnNormal         //��ѡ�ģ��ཻ��
                          ) const
{
    //���δ�ཻ�򷵻��������
    const float kNoIntersection = 1e30f;
    //�����ھ��α߽���ڵ�����������㵽ÿ����ľ���
    bool inside = true;
    float xt, xn;
    if(rayOrg.x < min.x)
    {
        xt = min.x - rayOrg.x;
        if(xt > rayDelta.x)
            return kNoIntersection;
        xt /= rayDelta.x;
        inside = false;
        xn = -1.0f;
    }
    else if(rayOrg.x > max.x)
    {
        xt = max.x - rayOrg.x;
        if(xt < rayDelta.x)
            return kNoIntersection;
        xt /= rayDelta.x;
        inside = false;
        xn = 1.0f;
    }
    else
        xt = -1.0f;

    float yt, yn;
    if(rayOrg.y < min.y)
    {
        yt = min.y - rayOrg.y;
        if(yt > rayDelta.y)
            return kNoIntersection;
        yt /= rayDelta.y;
        inside = false;
        yn = -1.0f;
    }
    else if(rayOrg.y > max.y)
    {
        yt = max.y - rayOrg.y;
        if(yt < rayDelta.y)
            return kNoIntersection;
        yt /= rayDelta.y;
        inside = false;
        yn = 1.0f;
    }
    else
        yt = -1.0f;
    float zt, zn;
    if(rayOrg.z < min.z)
    {
        zt = min.z - rayOrg.z;
        if(zt > rayDelta.z)
            return kNoIntersection;
        zt /= rayDelta.z;
        inside = false;
        zn = -1.0f;
    }
    else if(rayOrg.z > max.z)
    {
        zt = max.z - rayOrg.z;
        if(zt < rayDelta.z)
            return kNoIntersection;
        zt /= rayDelta.z;
        inside = false;
        zn = 1.0f;
    }
    else
        zt = -1.0f;
    //�Ƿ��ھ��α߽���ڣ�
    if(inside)
    {
        if(returnNormal != nullptr)
        {
            *returnNormal = -rayDelta;
            returnNormal->normalize();
        }
        return 0.0f;
    }
    //ѡ����Զ��ƽ��-�����ཻ�ĵط�
    int which = 0;
    float t = xt;
    if(yt > t)
    {
        which = 1;
        t = yt;
    }
    if(zt > t)
    {
        which = 2;
        t = zt;
    }
    switch(which)
    {
    case 0: //��yzƽ���ཻ
        {
            float y = rayOrg.y + rayDelta.y*t;
            if(y < min.y || y > max.y)
                return kNoIntersection;
            float z = rayOrg.z + rayDelta.z*t;
            if(z < min.z || z > max.z)
                return kNoIntersection;
            if(returnNormal != nullptr)
            {
                returnNormal->x = xn;
                returnNormal->y = 0.0f;
                returnNormal->z = 0.0f;
            }
        }
        break;
    case 1: //��xzƽ���ཻ
        {
            float x = rayOrg.x + rayDelta.x*t;
            if(x < min.x || x > max.x)
                return kNoIntersection;
            float z = rayOrg.z + rayDelta.z*t;
            if(z < min.z || z > max.z)
                return kNoIntersection;
            if(returnNormal != nullptr)
            {
                returnNormal->x = 0.0f;
                returnNormal->y = yn;
                returnNormal->z = 0.0f;
            }
        }
        break;
    case 2: //��xyƽ���ཻ
        {
            float x = rayOrg.x + rayDelta.x*t;
            if(x < min.x || x > max.x)
                return kNoIntersection;
            float y = rayOrg.y + rayDelta.y*t;
            if(y < min.y || y > max.y)
                return kNoIntersection;
            if(returnNormal != nullptr)
            {
                returnNormal->x = 0.0f;
                returnNormal->y = 0.0f;
                returnNormal->z = zn;
            }
        }
        break;
    }
    //���ؽ���Ĳ���ֵ
    return t;
}
//------------------------------------------------------------
//AABB3::classifyPlane
//��ֹAABB��ƽ����ཻ�Լ��
//����ֵ��
//<0 ���α߽����ȫ��ƽ��ı���
//>0 ���α߽����ȫ��ƽ�������
//0 ���α߽���ƽ���ཻ
int AABB3::classifyPlane(const Vector3 &n, float d) const
{
    //��鷨������������С�����Dֵ��������
    float minD, maxD;
    if(n.x > 0.0f)
    {
        minD = n.x*min.x;
        maxD = n.x*max.x;
    }
    else
    {
        minD = n.x * max.x;
        maxD = n.x * min.x;
    }
    if(n.y > 0.0f)
    {
        minD += n.y * min.y;
        maxD += n.y * max.y;
    }
    else
    {
        minD += n.y * max.y;
        maxD += n.y * min.y;
    }
    if(n.z > 0.0f)
    {
        minD += n.z * min.z;
        maxD += n.z * max.z;
    }
    else
    {
        minD += n.z * max.z;
        maxD += n.z * min.z;
    }
    //��ȫ��ƽ���ǰ��
    if(minD >= d)
        return +1;
    //��ȫ��ƽ��ı���
    if(maxD <= d)
        return -1;
    //���ƽ��
    return 0;
}
//------------------------------------------------------------
//AABB3::intersectPlane
//��̬AABB��ƽ���ཻ�Լ��
//nΪƽ�淨����������Ϊ��׼��������
//planeD��ƽ�淽��p*n = d��Dֵ
//dir �� AABB �ƶ��ķ���
//
//����ƽ���Ǿ�ֹ��
//���ؽ���Ĳ���ֵ-�ཻʱAABB�ƶ��ľ��룬���δ�ཻ�򷵻�һ������
//
//ֻ̽���ƽ��������ཻ
//
float AABB3::intersectPlane(
                            const Vector3 &n,
                            float planeD,
                            const Vector3 &dir
                            ) const
{
    //��������Ƿ�Ϊ��������
    assert(fabs(n*n - 1.0f) < .01f);
    assert(fabs(dir*dir - 1.0f) < .01f);
    //���δ�ཻ�����������
    const float kNoIntersection = 1e30f;
    //����нǣ�ȷ������������ƽ��������ƶ�
    float dot = n * dir;
    if(dot >= 0.0f)
        return kNoIntersection;
    //��鷨������������С�����Dֵ��minD��������ǰ�涥���Dֵ
    float minD, maxD;
    if(n.x > 0.0f)
    {
        minD = n.x * min.x;
        maxD = n.x * max.x;
    }
    else
    {
        minD = n.x * max.x;
        maxD = n.x * min.x;
    }
    if(n.y > 0.0f)
    {
        minD += n.y * min.y;
        maxD += n.y * max.y;
    }
    else
    {
        minD += n.y * max.y;
        maxD += n.y * min.y;
    }
    if(n.z > 0.0f)
    {
        minD += n.z * min.z;
        maxD += n.z * max.z;
    }
    else
    {
        minD += n.z * max.z;
        maxD += n.z * min.z;
    }
    //����Ƿ��Ѿ�ȫ����ƽ�����һ��
    if(maxD <= planeD)
        return kNoIntersection;
    //����ǰ��������׼���߷���
    float t = (planeD - minD) / dot;
    //�Ѿ���������?
    if(t < 0.0f)
        return 0.0f;
    //�������������� > 1����δ�ܼ�ʱ����ƽ�棬������Ҫ�����߽��м��
    return t;
}
///////////////////////////////////////////////////////////////////////
//
//ȫ�ַǳ�Ա��������
//
///////////////////////////////////////////////////////////////////////
//------------------------------------------------------------
//intersectAABBs
//�������AABB�Ƿ��ཻ������ཻ�򷵻�true��Ҳ���Է����ཻ���ֵ�AABB
//
bool intersectAABBs(const AABB3 &box1,
                    const AABB3 &box2,
                    AABB3 *boxIntersect)
{
    //�ж��Ƿ����ص�
    if(box1.min.x > box2.max.x)
        return false;
    if(box1.max.x < box2.min.x)
        return false;
    if(box1.min.y > box2.max.y)
        return false;
    if(box1.max.y < box2.min.y)
        return false;
    if(box1.min.z > box2.max.z)
        return false;
    if(box1.max.z < box2.min.z)
        return false;
    //���ص��������ص����ֵ�AABB�������Ҫ�Ļ�
    if(boxIntersect != nullptr)
    {
        boxIntersect->min.x = max(box1.min.x, box2.min.x);
        boxIntersect->max.x = min(box1.max.x, box2.max.x);
        boxIntersect->min.y = max(box1.min.y, box2.min.y);
        boxIntersect->max.y = min(box1.max.y, box2.max.y);
        boxIntersect->min.z = max(box1.min.z, box2.min.z);
        boxIntersect->max.z = min(box1.max.z, box2.max.z);
    }
    //�����ཻ
    return true;
}
//------------------------------------------------------------
//intersectMovingAABB
//��̬AABB���ཻ�Բ��ԣ��������ֵ>1 ��δ�ཻ
//
float intersectMovingAABB(
                          const AABB3 &stationaryBox,
                          const AABB3 &movingBox,
                          const Vector3 &d
                          )
{
    //���δ�ཻ�����������
    const float kNoIntersection = 1e30f;
    //��ʼ��ʱ�����䣬�԰�����Ҫ���ǵ�ȫ��ʱ���
    float tEnter = 0.0f;
    float tLeave = 1.0f;
    //����ÿһά�ϵ��ص����֣��ٽ�����ص����ֺ�ǰ����ص��������ཻ
    //�����һά���ص�����Ϊ���򷵻أ������ཻ��
    //ÿһά�����뵱�����ص�
    //
    //���x��
    if(d.x == 0.0f)
    {
        //x�����ص�����Ϊ��?
        if(
           (stationaryBox.max.x <= movingBox.min.x) ||
           (stationaryBox.min.x >= movingBox.max.x)
           )
           //�����ཻ
            return kNoIntersection;
        //������ʱ�����䣬û�б�Ҫ�ĸ���
    }
    else
    {
        //ֻ��һ��
        float oneOverD = 1.0f / d.x;
        //���㿪ʼ�Ӵ�������Ӵ���ʱ��
        float xEnter = (stationaryBox.min.x - movingBox.max.x) * oneOverD;
        float xLeave = (stationaryBox.max.x - movingBox.min.x) * oneOverD;
        //���˳��
        if(xEnter > xLeave)
            swap(xEnter, xLeave);
        //��������
        if(xEnter > tEnter)
            tEnter = xEnter;
        if(xLeave < tLeave)
            tLeave = xLeave;
        //�Ƿ��¿��ص���
        if(tEnter > tLeave)
            return kNoIntersection;
    }
    //���y��
    if(d.y == 0.0f)
    {
        //y�����ص�����Ϊ��
        if(
           (stationaryBox.max.y <= movingBox.min.y) ||
           (stationaryBox.min.y >= movingBox.max.y)
           )
           //�����ཻ
            return kNoIntersection;
        //������ʱ�����䣬û�б�Ҫ�ĸ���
    }
    else
    {
        //ֻ��һ��
        float oneOverD = 1.0f / d.y;
        //���㿪ʼ�Ӵ�������Ӵ���ʱ��
        float yEnter = (stationaryBox.min.y - movingBox.max.y) * oneOverD;
        float yLeave = (stationaryBox.max.y - movingBox.min.y) * oneOverD;
        //���˳��
        if(yEnter > yLeave)
            swap(yEnter, yLeave);
        //��������
        if(yEnter > tEnter)
            tEnter = yEnter;
        if(yLeave < tLeave)
            tLeave = yLeave;
        //�Ƿ��¿��ص���
        if(tEnter > tLeave)
            return kNoIntersection;
    }
    //���z��
    if(d.z == 0.0f)
    {
        //z�����ص�����Ϊ��
        if(
           (stationaryBox.max.z <= movingBox.min.z) ||
           (stationaryBox.min.z >= movingBox.max.z)
           )
           //�����ཻ
            return kNoIntersection;
        //������ʱ�����䣬û�б�Ҫ�ĸ���
    }
    else
    {
        //ֻ��һ��
        float oneOverD = 1.0f / d.z;
        //���㿪ʼ�Ӵ�������Ӵ���ʱ��
        float zEnter = (stationaryBox.min.z - movingBox.max.z) * oneOverD;
        float zLeave = (stationaryBox.max.z - movingBox.min.z) * oneOverD;
        //���˳��
        if(zEnter > zLeave)
            swap(zEnter, zLeave);
        //��������
        if(zEnter > tEnter)
            tEnter = zEnter;
        if(zLeave < tLeave)
            tLeave = zLeave;
        //�Ƿ��¿��ص���
        if(tEnter > tLeave)
            return kNoIntersection;
    }
    //���ˣ����ཻ���������ؽ���Ĳ���ֵ
    return tEnter;
}
