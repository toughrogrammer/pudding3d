
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
	bool IsClipped() { return _clipped; }

	void computeNormal();
	void Transform( Matrix4 mat );
	bool Clipping( float nearZ, float farZ );


private:
	Vertex _vertices[3];
	Vector4 _normal;
	bool _clipped;
};

#endif