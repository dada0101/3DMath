#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//
//Vector3��---�򵥵�3D������
//
//////////////////////////////////////////////////////////////////////////////

class Vector3
{
public:
	float x, y, z;
	//���캯��
	//Ĭ�Ϲ��캯������ִ���κβ���
	Vector3() {}
	//���ƹ��캯��
	Vector3(const Vector3 &a) : x(a.x), y(a.y), z(a.z) {}
	//�������Ĺ��캯����������ֵ��ɳ�ʼ��
	Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

	//��׼�������
	//���ظ�ֵ����������������ã���ʵ����ֵ
	Vector3 &operator = (const Vector3 &a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}
	//���� == �����
	bool operator == (const Vector3 &a) const
	{
		return x == a.x && y == a.y && z == a.z;
	}

	bool operator != (const Vector3 &a) const
	{
		return x != a.x || y != a.y || z != a.z;
	}

	//��������
	//��Ϊ������
	void zero() { x = y = z = 0.0f; }
	//����һԪ ��-�� �����
	Vector3 operator - () const { return Vector3(-x, -y, -z); }
	//���ض�Ԫ ��-�� �͡�+�������
	Vector3 operator + (const Vector3 &a) const
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	Vector3 operator - (const Vector3 &a) const
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}
	//������ĳˣ�����
	Vector3 operator * (float a) const
	{
		return Vector3(a * x, a * y, a * z);
	}

	Vector3 operator / (float a) const
	{
		//ע�� ���ﲻ�Գ�����м��
		float oneOverA = 1.0 / a;
		return Vector3(oneOverA * x, oneOverA * y, oneOverA * z);
	}
	//�����Է������
	Vector3 &operator += (const Vector3 &a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	Vector3 &operator -= (const Vector3 &a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	Vector3 &operator *= (float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vector3 &operator /= (float a)
	{
		float oneOverA = 1.0 / a;
		x *= oneOverA;
		y *= oneOverA;
		z *= oneOverA;
		return *this;
	}
	//������׼��
	void normalize()
	{
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0)			//������
		{
			float oneOverMag = 1.0 / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
	}
	//������ˣ� ���ر�׼�ĳ˷������
	float operator * (const Vector3 &a) const
	{
		return x * a.x + y * a.y + z * a.z;
	}
};
//////////////////////////////////////////////////////////////////////////////
//
//�ǳ�Ա����
//
//////////////////////////////////////////////////////////////////////////////
//������ģ
inline float vectorMsg(const Vector3 &a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
//ʵ�ֱ������
inline Vector3 operator * (float k, const Vector3 &a)
{
	return Vector3(k * a.x, k * a.y, k * a.z);
}
//��������֮��ľ���
inline float distance(const Vector3 &a, const Vector3 &b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;

	return sqrt(dx*dx + dy * dy + dz * dz);
}
//�����������Ĳ��
inline Vector3 crossProduct(const Vector3 &a, const Vector3 &b)
{
	return Vector3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}

//////////////////////////////////////////////////////////////////////////////
//
//ȫ�ֱ���
//
//////////////////////////////////////////////////////////////////////////////
//�ṩһ��ȫ�������
extern const Vector3 kZeroVector;

#endif // VECTOR_H_INCLUDED
