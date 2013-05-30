#include "Vector2.h"

#include <math.h>

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float initx, float inity)
{
	x = initx;
	y = inity;
}

Vector2::Vector2(const Vector2& vec)
{
	x = vec.x;
	y = vec.y;
}

Vector2::~Vector2()
{

}

float Vector2::Length()
{
	return float(sqrt(x*x + y*y));
}

Vector2 Vector2::Nomalize()
{
	float fLength = 0.0f;
	fLength = Length();
	return (Vector2(x/fLength, y/fLength));
}

//연산자오버로딩
//+,-
Vector2 Vector2::operator+(const Vector2& vec) const
{
	return Vector2(x+vec.x, y+vec.y);
}
Vector2 Vector2::operator-(const Vector2& vec) const
{
	return Vector2(x-vec.x, y-vec.y);
}
Vector2 Vector2::operator-(void) const //부호변경
{
	return Vector2(-x, -y);
}

//*,/
Vector2 Vector2::operator*(const float scalar) const
{
	return Vector2(scalar*x, scalar*y);
}
Vector2 Vector2::operator/(const float scalar) const
{
	return Vector2(x/scalar, y/scalar);
}
Vector2 operator*(const float scalar, const Vector2& vec)//전역연산자오버로딩
{
	return Vector2(scalar * vec.x, scalar * vec.y); 
}

//내적
float Vector2::operator*(const Vector2& vec) const
{
	return x*vec.x + y*vec.y;
}

//복합대입연산자
Vector2& Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}
Vector2& Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}
Vector2& Vector2::operator/=(const float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

//행렬곱셈
Vector2 Vector2::operator*(const Matrix2 m) const
{
	Vector2 temp;

	temp.x = x * m.a11 + y * m.a21; 
	temp.y = x * m.a12 + y * m.a22; 

	return temp; 
}