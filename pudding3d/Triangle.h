
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "util.h"
#include "Vertex.h"

class Triangle
{
public:
	Triangle();
	Triangle(const Vertex* arr);
	Triangle( const Triangle& t );
	~Triangle();

	const Vertex &v(int index) const { return _vertices[index]; }
	Vertex &v(int index) { return _vertices[index]; }

	void computeNormal();
	void Transform( Matrix4 mat );


private:
	Vertex _vertices[3];
	Vector4 _normal;
};

#endif