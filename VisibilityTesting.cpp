#include "VisibilityTesting.h"
#include "Vector3.h"
//计算裁剪空间中一个点的输出码
int computeOutCode(float x, float y, float z, float w)
{
    //从零开始，假设点在视锥中
    int code = 0;
    //依次检测六个面，开关相应的位
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
    //返回
    return code;
}


