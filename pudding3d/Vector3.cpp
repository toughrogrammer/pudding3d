#include "Vector3.h"

#include <math.h>

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float initx, float inity,float initz)
{
	x = initx;
	y = inity;
	z = initz;
}

Vector3::Vector3(const Vector2& vec)
{
	x = vec.x;
	y = vec.y;
	z = 1; 
}

Vector3::~Vector3()
{

}

float Vector3::Length()
{
	return float(sqrt(x*x + y*y + z*z));
}

void Vector3::Normalize()
{
	float fLength = Length();
	x /= fLength;
	y /= fLength;
	z /= fLength;
}
Vector3 Vector3::Normalize(Vector3 v)
{
	float fLength = 0.0f;
	fLength = sqrtf( v.x*v.x + v.y*v.y + v.z*v.z );

	Vector3 result;
	result.x = v.x/fLength;
	result.y = v.y/fLength;
	result.z = v.z/fLength;
	
	return result;
}

void Vector3::Init()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

void Vector3::Set(float sx, float sy, float sz)
{
	x = sx;
	y = sy;
	z = sz;
}

//연산자오버로딩
//+,-
Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3(x+vec.x, y+vec.y, z+vec.z);
}
Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3(x-vec.x, y-vec.y, z-vec.z);
}
Vector3 Vector3::operator-(void) const //부호변경
{
	return Vector3(-x, -y, -z);
}

//*,/
Vector3 Vector3::operator*(const float scalar) const
{
	return Vector3(scalar*x, scalar*y, scalar*z);
}
Vector3 Vector3::operator/(const float scalar) const
{
	return Vector3(x/scalar, y/scalar, z/scalar);
}
Vector3 operator*(const float scalar, const Vector3& vec)//전역연산자오버로딩
{
	return Vector3(scalar*vec.x, scalar*vec.y, scalar*vec.z); 
}

//내적
float Vector3::operator*(const Vector3& vec) const
{
	return (x*vec.x + y*vec.y + z*vec.z);
}
//외적
Vector3 Vector3::operator^(const Vector3& vec) const
{
	Vector3 temp;

	temp.x = y*vec.z - z*vec.y;
	temp.y = z*vec.x - x*vec.z;
	temp.z = x*vec.y - y*vec.x;

	return temp;
}

//복합대입연산자
Vector3& Vector3::operator+=(const Vector3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}
Vector3& Vector3::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}
Vector3& Vector3::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

//행렬곱셈
Vector3 Vector3::operator*(const Matrix3 m) const
{
	Vector3 temp;

	temp.x = x*m.a11 + y*m.a21 + z*m.a31;
	temp.y = x*m.a12 + y*m.a22 + z*m.a32;
	temp.z = x*m.a13 + y*m.a23 + z*m.a33;

	return temp;
}
