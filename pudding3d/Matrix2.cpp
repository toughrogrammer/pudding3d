#include "Matrix2.h"

Matrix2::Matrix2()
{
	a11 = 0.0f;
	a12 = 0.0f;

	a21 = 0.0f;
	a22 = 0.0f;
}	

Matrix2::Matrix2(float m11, float m12, float m21, float m22)
{
	a11 = m11;
	a12 = m12;
	
	a21 = m21;
	a22 = m22;
}


void Matrix2::Identity()
{
	a11 = 1.0f;
	a12 = 0.0f;

	a21 = 0.0f;
	a22 = 1.0f;
}
void Matrix2::Transpose()
{
	float temp;
	temp = a12;
	a12 = a21;
	a21 = temp;
}
void Matrix2::Inverse()
{
	float det = a11 * a22 - a12 * a21; //행렬식
	det = 1.0f/det;

	float temp11 = a11;
	
	a11 = a22 * det; //여인자 * 역행렬식
	a12 = -a12 * det;
	a21 = -a21 * det;
	a22 = temp11 * det;
}

Matrix2 Matrix2::operator+(const Matrix2 &m) const
{
	return Matrix2(a11+m.a11, a12+m.a12, a21+m.a21, a22+m.a22);
}
Matrix2 Matrix2::operator-(const Matrix2 &m) const
{
	return Matrix2(a11-m.a11, a12-m.a12, a21-m.a21, a22-m.a22);
}
Matrix2 Matrix2::operator*(const Matrix2 &m) const
{
	Matrix2 temp;

	temp.a11 = a11 * m.a11 + a12 * m.a21;
	temp.a12 = a11 * m.a12 + a12 * m.a22;

	temp.a21 = a21 * m.a11 + a22 * m.a21;
	temp.a22 = a21 * m.a12 + a22 * m.a22;
	
	return temp;
}	
Matrix2 Matrix2::operator*(const float scalar) const
{
	return Matrix2(a11*scalar, a12*scalar, a21*scalar, a22*scalar);
}
Matrix2 operator*(const float scalar, const Matrix2 &m)
{
	return Matrix2(m.a11*scalar, m.a12*scalar, m.a21*scalar, m.a22*scalar);
}

void Matrix2::operator+=(const Matrix2 &m)
{
	a11+=m.a11;
	a12+=m.a12;

	a21+=m.a21;
	a22+=m.a22;
}
void Matrix2::operator-=(const Matrix2 &m)
{
	a11-=m.a11;
	a12-=m.a12;

	a21-=m.a21;
	a22-=m.a22;
}
void Matrix2::operator*=(const Matrix2 &m)
{
	Matrix2 temp;
	
	temp.a11 = a11 * m.a11 + a12 * m.a21;
	temp.a12 = a11 * m.a12 + a12 * m.a22;

	temp.a21 = a21 * m.a11 + a22 * m.a21;
	temp.a22 = a21 * m.a12 + a22 * m.a22;

	a11 = temp.a11;
	a12 = temp.a12;
	
	a21 = temp.a21;
	a22 = temp.a22;
}
void Matrix2::operator*=(const float scalar)
{
	a11 *= scalar;
	a12 *= scalar;
	
	a21 *= scalar;
	a22 *= scalar;
}