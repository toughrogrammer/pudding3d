#include "Vector4.h"

#include <math.h>

Vector4::Vector4()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

Vector4::Vector4(float initx, float inity, float initz, float initw)
{
	x = initx;
	y = inity;
	z = initz;
	w = initw;
}

Vector4::Vector4(const Vector3& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = 1;
}

Vector4::~Vector4()
{

}

float Vector4::Length()
{
	return float(sqrt(x*x + y*y + z*z));
}

void Vector4::Set(float sx, float sy, float sz, float sw)
{
	x = sx;
	y = sy;
	z = sz;
	w = sw;
}

Vector4 Vector4::Normalize()
{
	//TODO : Check precision of float compute

    *this /= Length();
    w = 1.0f;
    return *this;
}

//+, -
Vector4 Vector4::operator+(const Vector4& vec) const
{
	static Vector4 temp;
	temp.x = x + vec.x;
	temp.y = y + vec.y;
	temp.z = z + vec.z;
	temp.w = w + vec.w;

	return temp;
	//return Vector4(x+vec.x, y+vec.y, z+vec.z, w+vec.w);
}
Vector4 Vector4::operator-(const Vector4& vec) const
{
	static Vector4 temp;
	temp.x = x - vec.x;
	temp.y = y - vec.y;
	temp.z = z - vec.z;
	temp.w = w - vec.w;

	return temp;
	//return Vector4(x-vec.x, y-vec.y, z-vec.z, w+vec.w);
}
Vector4 Vector4::operator-(void) const //부호변경
{
	return Vector4(-x, -y, -z, -w);
}

//*,/
Vector4 Vector4::operator*(const float scalar) const
{
	static Vector4 temp;
	temp.x = x * scalar;
	temp.y = y * scalar;
	temp.z = z * scalar;
	temp.w = w * scalar;

	return temp;
	//return Vector4(scalar*x, scalar*y, scalar*z, scalar*w);
}
Vector4 Vector4::operator/(const float scalar) const
{
	return Vector4(x/scalar, y/scalar, z/scalar, w/scalar);
}
Vector4 operator*(const float scalar, const Vector4& vec)//전역연산자오버로딩
{
	return Vector4(scalar*vec.x, scalar*vec.y, scalar*vec.z, scalar*vec.w); 
}

//내적
float Vector4::operator*(const Vector4& vec) const
{
	return (x*vec.x + y*vec.y + z*vec.z + w*vec.w);
}
//외적
Vector4 Vector4::operator^(const Vector4& vec) const
{
	Vector4 temp;
	temp.x = y*vec.z - z*vec.y;
	temp.y = z*vec.x - x*vec.z;
	temp.z = x*vec.y - y*vec.x;
	return temp;
}

//복합대입연산자
Vector4& Vector4::operator+=(const Vector4& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}
Vector4& Vector4::operator-=(const Vector4& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}
Vector4& Vector4::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}
Vector4& Vector4::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4& Vector4::operator-=(const float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	return *this;
}

//행렬곱셈
Vector4 Vector4::operator*(const Matrix4 m) const
{
	Vector4 temp;
	temp.x = x*m.a11 + y*m.a21 + z*m.a31 + w*m.a41;
	temp.y = x*m.a12 + y*m.a22 + z*m.a32 + w*m.a42;
	temp.z = x*m.a13 + y*m.a23 + z*m.a33 + w*m.a43;
	temp.w = x*m.a14 + y*m.a24 + z*m.a34 + w*m.a44;

	return temp;
}

Vector4 Vector4::operator*=(const Matrix4 m)
{
	Vector4 temp;
	temp.x = x*m.a11 + y*m.a21 + z*m.a31 + w*m.a41;
	temp.y = x*m.a12 + y*m.a22 + z*m.a32 + w*m.a42;
	temp.z = x*m.a13 + y*m.a23 + z*m.a33 + w*m.a43;
	temp.w = x*m.a14 + y*m.a24 + z*m.a34 + w*m.a44;

	*this = temp;
	return *this;
}
