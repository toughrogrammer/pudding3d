
#ifndef _VERTEX_H_
#define _VERTEX_H_

#include "Matrix.h"
#include "Vector.h"
#include "Color.h"

class Vertex
{
public:
	Vector4 pos;		
	Vector4 Normal;
	Color color;
	
	float u;
	float v;
	float proW;

	Vertex(void){};
	~Vertex(void){};
	Vertex operator-(const Vertex& ver) const;
	Vertex operator+(const Vertex& ver) const;
	Vertex operator*(const float src) const;
	Vertex& operator+=(const Vertex& ver);
};

#endif