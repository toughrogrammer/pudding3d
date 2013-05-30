
#ifndef _VECTOR_4_H_
#define _VECTOR_4_H_

#include "Vector3.h"
#include "Matrix.h"

class Vector4
{
public:
	float x, y, z, w;

	Vector4();
	Vector4(float initx, float inity, float initz, float initw=1);
	Vector4(const Vector3& vec);
	~Vector4();

	Vector4 Normalize();
	float Length();
	void Set(float sx, float sy, float sz, float sw);
	Vector4 operator+(const Vector4& vec) const;
	Vector4 operator-(const Vector4& vec) const;
	Vector4 operator-(void) const; //부호변경
	
	Vector4 operator*(const float scalar) const;
	friend Vector4 operator*(const float scalar, const Vector4& vec);
	Vector4 operator/(const float scalar) const;
	
	float operator*(const Vector4& vec) const; //내적	
	Vector4 operator^(const Vector4& vec) const; //외적

	Vector4& operator+=(const Vector4& vec);
	Vector4& operator-=(const Vector4& vec);
	Vector4& operator*=(const float scalar);
	Vector4& operator/=(const float scalar);
	Vector4& operator-=(const float scalar);

	//행렬곱셈
	Vector4 operator*(const Matrix4 m) const;
	Vector4 operator*=(const Matrix4 m);
};

#endif