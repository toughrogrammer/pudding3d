#include "Matrix4.h"

Matrix4::Matrix4()
{
	a11 = 0.0f;
	a12 = 0.0f;
	a13 = 0.0f;
	a14 = 0.0f;

	a21 = 0.0f;
	a22 = 0.0f;
	a23 = 0.0f;
	a24 = 0.0f;

	a31 = 0.0f;
	a32 = 0.0f;
	a33 = 0.0f;
	a34 = 0.0f;

	a41 = 0.0f;
	a42 = 0.0f;
	a43 = 0.0f;
	a44 = 0.0f;
}	

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
{
	a11 = m11;
	a12 = m12;
	a13 = m13;
	a14 = m14;
		
	a21 = m21;
	a22 = m22;
	a23 = m23;
	a24 = m24;

	a31 = m31;
	a32 = m32;
	a33 = m33;
	a34 = m34;

	a41 = m41;
	a42 = m42;
	a43 = m43;
	a44 = m44;
}

void Matrix4::Identity()
{
	a11 = 1.0f;
	a12 = 0.0f;
	a13 = 0.0f;
	a14 = 0.0f;
    
	a21 = 0.0f;
	a22 = 1.0f;
	a23 = 0.0f;
	a24 = 0.0f;

	a31 = 0.0f;
	a32 = 0.0f;
	a33 = 1.0f;
	a34 = 0.0f;

	a41 = 0.0f;
	a42 = 0.0f;
	a43 = 0.0f;
	a44 = 1.0f;	
}
void Matrix4::Transpose()
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

	temp = a41;
	a41 = a14;
	a14 = temp;

	temp = a34;
	a34 = a43;
	a43 = temp;

	temp = a24;
	a24 = a42;
	a42 = temp;	
}
void Matrix4::Inverse()
{
	/*float det = a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31);
	det = 1.0f / det;

	Matrix4 temp;
	

	*this = temp; */
}

Matrix4 Matrix4::operator+(const Matrix4 &m) const
{
	return Matrix4(a11+m.a11, a12+m.a12, a13+m.a13, a14+m.a14,
				   a21+m.a21, a22+m.a22, a23+m.a23, a24+m.a24,
				   a31+m.a31, a32+m.a32, a33+m.a33, a34+m.a34,
				   a41+m.a41, a42+m.a42, a34+m.a43, a44+m.a44);
}
Matrix4 Matrix4::operator-(const Matrix4 &m) const
{
	return Matrix4(a11-m.a11, a12-m.a12, a13-m.a13, a14-m.a14,
				   a21-m.a21, a22-m.a22, a23-m.a23, a24-m.a24,
				   a31-m.a31, a32-m.a32, a33-m.a33, a34-m.a34,
				   a41-m.a41, a42-m.a42, a34-m.a43, a44-m.a44);
}
Matrix4 Matrix4::operator*(const Matrix4 &m) const
{
	Matrix4 temp;

	temp.a11 = a11 * m.a11 + a12 * m.a21 + a13 * m.a31 + a14 * m.a41;
	temp.a12 = a11 * m.a12 + a12 * m.a22 + a13 * m.a32 + a14 * m.a42;
	temp.a13 = a11 * m.a13 + a12 * m.a23 + a13 * m.a33 + a14 * m.a43;
	temp.a14 = a11 * m.a14 + a12 * m.a24 + a13 * m.a34 + a14 * m.a44;


	temp.a21 = a21 * m.a11 + a22 * m.a21 + a23 * m.a31 + a24 * m.a41;
	temp.a22 = a21 * m.a12 + a22 * m.a22 + a23 * m.a32 + a24 * m.a42;
	temp.a23 = a21 * m.a13 + a22 * m.a23 + a23 * m.a33 + a24 * m.a43;
	temp.a24 = a21 * m.a14 + a22 * m.a24 + a23 * m.a34 + a24 * m.a44;

	temp.a31 = a31 * m.a11 + a32 * m.a21 + a33 * m.a31 + a34 * m.a41;
	temp.a32 = a31 * m.a12 + a32 * m.a22 + a33 * m.a32 + a34 * m.a42;
	temp.a33 = a31 * m.a13 + a32 * m.a23 + a33 * m.a33 + a34 * m.a43;
	temp.a34 = a31 * m.a14 + a32 * m.a24 + a33 * m.a34 + a34 * m.a44;
	
	temp.a41 = a41 * m.a11 + a42 * m.a21 + a43 * m.a31 + a44 * m.a41;
	temp.a42 = a41 * m.a12 + a42 * m.a22 + a43 * m.a32 + a44 * m.a42;
	temp.a43 = a41 * m.a13 + a42 * m.a23 + a43 * m.a33 + a44 * m.a43;
	temp.a44 = a41 * m.a14 + a42 * m.a24 + a43 * m.a34 + a44 * m.a44;

	return temp;
}	

//스칼라*행렬
Matrix4 Matrix4::operator*(const float scalar) const
{
	return Matrix4(a11*scalar, a12*scalar, a13*scalar, a14*scalar,
				   a21*scalar, a22*scalar, a23*scalar, a24*scalar,
				   a31*scalar, a32*scalar, a33*scalar, a34*scalar,
				   a41*scalar, a42*scalar, a43*scalar, a44*scalar);	
}
Matrix4 operator*(const float scalar, const Matrix4 &m)
{
	return Matrix4(m.a11*scalar, m.a12*scalar, m.a13*scalar, m.a14*scalar,
				   m.a21*scalar, m.a22*scalar, m.a23*scalar, m.a24*scalar,
				   m.a31*scalar, m.a32*scalar, m.a33*scalar, m.a34*scalar,
				   m.a41*scalar, m.a42*scalar, m.a43*scalar, m.a44*scalar);			   
}


//복합대입연산자
void Matrix4::operator+=(const Matrix4 &m)
{
	a11+=m.a11;
	a12+=m.a12;
	a13+=m.a13;
    a14+=m.a14;

	a21+=m.a21;
	a22+=m.a22;
	a23+=m.a23;
	a24+=m.a24;

	a31+=m.a31;
	a32+=m.a32;
	a33+=m.a33;
	a34+=m.a34;

	a41+=m.a41;
	a42+=m.a42;
	a43+=m.a43;
	a44+=m.a44;
}

void Matrix4::operator-=(const Matrix4 &m)
{
	a11-=m.a11;
	a12-=m.a12;
	a13-=m.a13;
    a14-=m.a14;

	a21-=m.a21;
	a22-=m.a22;
	a23-=m.a23;
	a24-=m.a24;

	a31-=m.a31;
	a32-=m.a32;
	a33-=m.a33;
	a34-=m.a34;

	a41-=m.a41;
	a42-=m.a42;
	a43-=m.a43;
	a44-=m.a44;
}

void Matrix4::operator*=(const Matrix4 &m)
{
	Matrix4 temp;

	temp.a11 = a11 * m.a11 + a12 * m.a21 + a13 * m.a31 + a14 * m.a41;
	temp.a12 = a11 * m.a12 + a12 * m.a22 + a13 * m.a32 + a14 * m.a42;
	temp.a13 = a11 * m.a13 + a12 * m.a23 + a13 * m.a33 + a14 * m.a43;
	temp.a14 = a11 * m.a14 + a12 * m.a24 + a13 * m.a34 + a14 * m.a44;

	temp.a21 = a21 * m.a11 + a22 * m.a21 + a23 * m.a31 + a24 * m.a41;
	temp.a22 = a21 * m.a12 + a22 * m.a22 + a23 * m.a32 + a24 * m.a42;
	temp.a23 = a21 * m.a13 + a22 * m.a23 + a23 * m.a33 + a24 * m.a43;
	temp.a24 = a21 * m.a14 + a22 * m.a24 + a23 * m.a34 + a24 * m.a44;

	temp.a31 = a31 * m.a11 + a32 * m.a21 + a33 * m.a31 + a34 * m.a41;
	temp.a32 = a31 * m.a12 + a32 * m.a22 + a33 * m.a32 + a34 * m.a42;
	temp.a33 = a31 * m.a13 + a32 * m.a23 + a33 * m.a33 + a34 * m.a43;
	temp.a34 = a31 * m.a14 + a32 * m.a24 + a33 * m.a34 + a34 * m.a44;
	
	temp.a41 = a41 * m.a11 + a42 * m.a21 + a43 * m.a31 + a44 * m.a41;
	temp.a42 = a41 * m.a12 + a42 * m.a22 + a43 * m.a32 + a44 * m.a42;
	temp.a43 = a41 * m.a13 + a42 * m.a23 + a43 * m.a33 + a44 * m.a43;
	temp.a44 = a41 * m.a14 + a42 * m.a24 + a43 * m.a34 + a44 * m.a44;

	a11 = temp.a11;
	a12 = temp.a12;
	a13 = temp.a13;
	a14 = temp.a14;
	
	a21 = temp.a21;
	a22 = temp.a22;
	a23 = temp.a23;
	a24 = temp.a24;

	a31 = temp.a31;
	a32 = temp.a32;
	a33 = temp.a33;
	a34 = temp.a34;

	a41 = temp.a41;
	a42 = temp.a42;
	a43 = temp.a43;
	a44 = temp.a44;
}

void Matrix4::operator*=(const float scalar)
{
	a11 *= scalar;
	a12 *= scalar;
	a13 *= scalar;
	a14 *= scalar;
	
	a21 *= scalar;
	a22 *= scalar;
	a23 *= scalar;
	a24 *= scalar;

	a31 *= scalar;
	a32 *= scalar;
	a33 *= scalar;
	a34 *= scalar;
}