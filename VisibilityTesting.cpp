#include "VisibilityTesting.h"
#include "Vector3.h"
//����ü��ռ���һ����������
int computeOutCode(float x, float y, float z, float w)
{
    //���㿪ʼ�����������׶��
    int code = 0;
    //���μ�������棬������Ӧ��λ
    if(x < -w)
        code |= 0x01;       //left
    else if(x > w)
        code |= 0x02;       //right
    if(y < -w)
        code |= 0x04;       //bottom
    else if(y > w)
        code |= 0x08;       //top
    if(z < -w)
        code |= 0x10;       //near
    else if(z > w)
        code |= 0x20;       //far
    //����
    return code;
}


