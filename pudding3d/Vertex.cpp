#include "Vertex.h"

Vertex Vertex::operator-(const Vertex& ver) const
{	
	static Vertex temp; //속도때문에 static
	temp.pos.x = pos.x - ver.pos.x; //마찬가지로 속도때문에 연산자오버로딩x
	temp.pos.y = pos.y - ver.pos.y;
	temp.pos.z = pos.z - ver.pos.z;
	temp.pos.w = pos.w - ver.pos.w;
	
	temp.u = u - ver.u;
	temp.v = v - ver.v;
	temp.proW = proW - ver.proW;

	return temp;
}
Vertex Vertex::operator+(const Vertex& ver) const
{		
	static Vertex temp;
	temp.pos.x = pos.x + ver.pos.x;
	temp.pos.y = pos.y + ver.pos.y;
	temp.pos.z = pos.z + ver.pos.z;
	temp.pos.w = pos.w + ver.pos.w;

	temp.u = u + ver.u;
	temp.v = v + ver.v;
	temp.proW = proW + ver.proW;

	return temp;
}	
Vertex Vertex::operator*(const float src) const
{		
	static Vertex temp;
	temp.pos.x = pos.x * src;
	temp.pos.y = pos.y * src;
	temp.pos.z = pos.z * src;
	temp.pos.w = pos.w * src;

	temp.u = u * src;
	temp.v = v * src;
	temp.proW = proW * src;

	return temp;
}
Vertex& Vertex::operator+=(const Vertex& ver)
{				
	pos.x +=ver.pos.x;
	pos.y +=ver.pos.y;
	pos.z +=ver.pos.z;
	pos.w +=ver.pos.w;

	u += ver.u;
	v += ver.v;
	proW += ver.proW;

	return *this;
}	