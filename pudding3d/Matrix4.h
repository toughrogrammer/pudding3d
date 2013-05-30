#pragma once

class Matrix4
{
public:
	float a11, a12, a13, a14;
	float a21, a22, a23, a24;
	float a31, a32, a33, a34;
	float a41, a42, a43, a44;

	Matrix4();
	Matrix4(float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44
	);
	~Matrix4(){};

	void Identity();  //단위행렬
	void Transpose(); //전치행렬
	void Inverse();   //역행렬

	Matrix4 operator+(const Matrix4 &m) const;
	Matrix4 operator-(const Matrix4 &m) const;
	Matrix4 operator*(const Matrix4 &m) const;	
	Matrix4 operator*(const float scalar) const;
	friend Matrix4 operator*(const float scalar, const Matrix4 &m);//전역연산자오버로딩

	void operator+=(const Matrix4 &m);
	void operator-=(const Matrix4 &m);
	void operator*=(const Matrix4 &m); //행렬요소 각각을 내적계산
	void operator*=(const float scalar);
};
