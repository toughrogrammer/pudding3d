#pragma once

#include "Matrix.h"

class Vector2
{
public:
	float x, y;
	Vector2();
	Vector2(float initx, float inity);
	Vector2(const Vector2& vec);
	~Vector2();

	Vector2 Nomalize(); //단위벡터리턴
	float Length();		//크기계산
		
	Vector2 operator+(const Vector2& vec) const;
	Vector2 operator-(const Vector2& vec) const;
	Vector2 operator-(void) const; //부호변경
	
	Vector2 operator*(const float scalar) const;
	friend Vector2 operator*(const float scalar, const Vector2& vec);
	Vector2 operator/(const float scalar) const;
	
	float operator*(const Vector2& vec) const; //내적	
		
	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const float scalar);
	Vector2& operator/=(const float scalar);

	//행렬곱셈
	Vector2 operator*(const Matrix2 m) const;
};

/*
빗변a
밑변 = a*cos세타 
벡터의 내적은 양수 음수로 두벡터가 같은 방향을 향하고 있는지 아닌지 알수있다.
*/