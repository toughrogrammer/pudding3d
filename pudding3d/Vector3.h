#pragma once

#include "Vector2.h"
#include "Matrix.h"

class Vector3
{
public:
	float x, y, z;
	Vector3();
	Vector3(float initx, float inity, float initz);
	Vector3(const Vector2& vec);
	~Vector3();

	void Normalize();
	static Vector3 Normalize(Vector3 v);
	float Length();
	void Init();
	void Set(float sx, float sy, float sz);
		
	Vector3 operator+(const Vector3& vec) const;
	Vector3 operator-(const Vector3& vec) const;
	Vector3 operator-(void) const; //부호변경
	
	Vector3 operator*(const float scalar) const;
	friend Vector3 operator*(const float scalar, const Vector3& vec);
	Vector3 operator/(const float scalar) const;
	
	float operator*(const Vector3& vec) const; //내적	
	Vector3 operator^(const Vector3& vec) const; //외적

	Vector3& operator+=(const Vector3& vec);
	Vector3& operator-=(const Vector3& vec);
	Vector3& operator*=(const float scalar);
	Vector3& operator/=(const float scalar);

	//행렬곱셈
	Vector3 operator*(const Matrix3 m) const;
};
