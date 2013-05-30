#pragma once

class Matrix2
{
public:
	float a11, a12;
	float a21, a22;

	Matrix2();
	Matrix2(float m11, float m12, float m21, float m22);
	~Matrix2(){};

	void Identity();  //단위행렬
	void Transpose(); //전치행렬
	void Inverse();   //역행렬

	Matrix2 operator+(const Matrix2 &m) const;
	Matrix2 operator-(const Matrix2 &m) const;
	Matrix2 operator*(const Matrix2 &m) const;	
	Matrix2 operator*(const float scalar) const;
	friend Matrix2 operator*(const float scalar, const Matrix2 &m);//전역연산자오버로딩

	void operator+=(const Matrix2 &m);
	void operator-=(const Matrix2 &m);
	void operator*=(const Matrix2 &m); //행렬요소 각각을 내적계산
	void operator*=(const float scalar);
};
