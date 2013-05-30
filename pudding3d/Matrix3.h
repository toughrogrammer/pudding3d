#pragma once

class Matrix3
{
public:
	float a11, a12, a13;
	float a21, a22, a23;
	float a31, a32, a33;

	Matrix3();
	Matrix3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33
	);
	~Matrix3(){};

	void Identity();  //단위행렬
	void Transpose(); //전치행렬
	void Inverse();   //역행렬

	Matrix3 operator+(const Matrix3 &m) const;
	Matrix3 operator-(const Matrix3 &m) const;
	Matrix3 operator*(const Matrix3 &m) const;	
	Matrix3 operator*(const float scalar) const;
	friend Matrix3 operator*(const float scalar, const Matrix3 &m);//전역연산자오버로딩

	void operator+=(const Matrix3 &m);
	void operator-=(const Matrix3 &m);
	void operator*=(const Matrix3 &m); //행렬요소 각각을 내적계산
	void operator*=(const float scalar);
};
