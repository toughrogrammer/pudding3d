#include "Matrix3.h"

Matrix3::Matrix3()
{
	a11 = 0.0f;
	a12 = 0.0f;
	a13 = 0.0f;

	a21 = 0.0f;
	a22 = 0.0f;
	a23 = 0.0f;

	a31 = 0.0f;
	a32 = 0.0f;
	a33 = 0.0f;
}	

Matrix3::Matrix3(float m11, float m12, float m13,
				 float m21, float m22, float m23,
				 float m31, float m32, float m33)
{
	a11 = m11;
	a12 = m12;
	a13 = m13;
		
	a21 = m21;
	a22 = m22;
	a23 = m23;

	a31 = m31;
	a32 = m32;
	a33 = m33;
}

void Matrix3::Identity()
{
	a11 = 1.0f;
	a12 = 0.0f;
	a13 = 0.0f;

	a21 = 0.0f;
	a22 = 1.0f;
	a23 = 0.0f;

	a31 = 0.0f;
	a32 = 0.0f;
	a33 = 1.0f;
}
void Matrix3::Transpose()
{
	float temp;
	
	temp = a21;
	a21 = a12;
	a12 = temp;

	temp = a31;
	a31 = a13;
	a13 = temp;

	temp = a23;
	a23 = a32;
	a32 = temp;
}
void Matrix3::Inverse()
{
	float det = a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31);
	det = 1.0f / det;

	Matrix3 temp;

	temp.a11 = (a22 * a33 - a23 * a32) * det; //여인자*역행렬식
	temp.a12 = (a13 * a32 - a12 * a33) * det; 
	temp.a13 = (a12 * a23 - a13 * a22) * det; 

	temp.a21 = (a23 * a31 - a21 * a33) * det; 
	temp.a22 = (a11 * a33 - a13 * a31) * det; 
	temp.a23 = (a13 * a21 - a11 * a23) * det; 

	temp.a31 = (a21 * a32 - a22 * a31) * det; 
	temp.a32 = (a12 * a31 - a11 * a32) * det; 
	temp.a33 = (a11 * a22 - a12 * a21) * det;

	*this = temp; 
}

Matrix3 Matrix3::operator+(const Matrix3 &m) const
{
	return Matrix3(a11+m.a11, a12+m.a12, a13+m.a13,
				   a21+m.a21, a22+m.a22, a23+m.a23,
				   a31+m.a31, a32+m.a32, a33+m.a33);
}
Matrix3 Matrix3::operator-(const Matrix3 &m) const
{
	return Matrix3(a11-m.a11, a12-m.a12, a13-m.a13,
				   a21-m.a21, a22-m.a22, a23-m.a23,
				   a31-m.a31, a32-m.a32, a33-m.a33);
}
Matrix3 Matrix3::operator*(const Matrix3 &m) const
{
	Matrix3 temp;

	temp.a11 = a11 * m.a11 + a12 * m.a21 + a13 * m.a31;
	temp.a12 = a11 * m.a12 + a12 * m.a22 + a13 * m.a32;
	temp.a13 = a11 * m.a13 + a12 * m.a23 + a13 * m.a33; 

	temp.a21 = a21 * m.a11 + a22 * m.a21 + a23 * m.a31;
	temp.a22 = a21 * m.a12 + a22 * m.a22 + a23 * m.a32;
	temp.a23 = a21 * m.a13 + a22 * m.a23 + a23 * m.a33;

	temp.a31 = a31 * m.a11 + a32 * m.a21 + a33 * m.a31;
	temp.a32 = a31 * m.a12 + a32 * m.a22 + a33 * m.a32;
	temp.a33 = a31 * m.a13 + a32 * m.a23 + a33 * m.a33;
	
	return temp;
}	

//스칼라*행렬
Matrix3 Matrix3::operator*(const float scalar) const
{
	return Matrix3(a11*scalar, a12*scalar, a13*scalar,
				   a21*scalar, a22*scalar, a23*scalar,
				   a31*scalar, a32*scalar, a33*scalar);	
}
Matrix3 operator*(const float scalar, const Matrix3 &m)
{
	return Matrix3(m.a11*scalar, m.a12*scalar, m.a13*scalar,
				   m.a21*scalar, m.a22*scalar, m.a23*scalar,
				   m.a31*scalar, m.a32*scalar, m.a33*scalar);	
}


//복합대입연산자
void Matrix3::operator+=(const Matrix3 &m)
{
	a11+=m.a11;
	a12+=m.a12;
	a13+=m.a13;
    
	a21+=m.a21;
	a22+=m.a22;
	a23+=m.a23;

	a31+=m.a31;
	a32+=m.a32;
	a33+=m.a33;
}

void Matrix3::operator-=(const Matrix3 &m)
{
	a11-=m.a11;
	a12-=m.a12;
	a13-=m.a13;
    
	a21-=m.a21;
	a22-=m.a22;
	a23-=m.a23;

	a31-=m.a31;
	a32-=m.a32;
	a33-=m.a33;
}

void Matrix3::operator*=(const Matrix3 &m)
{
	Matrix3 temp;
	
	temp.a11 = a11 * m.a11 + a12 * m.a21 + a13 * m.a31;
	temp.a12 = a11 * m.a12 + a12 * m.a22 + a13 * m.a32;
	temp.a13 = a11 * m.a13 + a12 * m.a23 + a13 * m.a33; 

	temp.a21 = a21 * m.a11 + a22 * m.a21 + a23 * m.a31;
	temp.a22 = a21 * m.a12 + a22 * m.a22 + a23 * m.a32;
	temp.a23 = a21 * m.a13 + a22 * m.a23 + a23 * m.a33;

	temp.a31 = a31 * m.a11 + a32 * m.a21 + a33 * m.a31;
	temp.a32 = a31 * m.a12 + a32 * m.a22 + a33 * m.a32;
	temp.a33 = a31 * m.a13 + a32 * m.a23 + a33 * m.a33;

	a11 = temp.a11;
	a12 = temp.a12;
	a13 = temp.a13;
	
	a21 = temp.a21;
	a22 = temp.a22;
	a23 = temp.a23;

	a31 = temp.a31;
	a32 = temp.a32;
	a33 = temp.a33;
}

void Matrix3::operator*=(const float scalar)
{
	a11 *= scalar;
	a12 *= scalar;
	a13 *= scalar;
	
	a21 *= scalar;
	a22 *= scalar;
	a23 *= scalar;

	a31 *= scalar;
	a32 *= scalar;
	a33 *= scalar;
}