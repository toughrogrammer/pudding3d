
#include "Triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle( const Vertex* arr )
{
	if( !arr )
	{
		// Vertex* arr doesn't have data
		return;
	}

	_vertices[0] = arr[0];
	_vertices[1] = arr[1];
	_vertices[2] = arr[2];

	computeNormal();

}

Triangle::Triangle( const Triangle& t )
{
	_vertices[0] = Vertex(t.v(0));
	_vertices[1] = Vertex(t.v(1));
	_vertices[2] = Vertex(t.v(2));

	computeNormal();
}

Triangle::~Triangle()
{

}

void Triangle::computeNormal()
{
	Vector4 v0( ( _vertices[1].pos - _vertices[0].pos ).Normalize() );
	Vector4 v1( ( _vertices[2].pos - _vertices[0].pos ).Normalize() );

	_normal = cross( v0, v1 );
	_normal.Normalize();
}

void Triangle::Transform( Matrix4 mat )
{
	_vertices[0].pos *= mat;
	_vertices[1].pos *= mat;
	_vertices[2].pos *= mat;
}