
#include "Triangle.h"

Triangle::Triangle()
	:_clipped(false)
{

}

Triangle::Triangle( const Vertex* arr )
	:_clipped(false)
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
	:_clipped(false)
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
	Vector4 v1( ( _vertices[1].pos - _vertices[0].pos ).Normalize() );
	Vector4 v2( ( _vertices[2].pos - _vertices[0].pos ).Normalize() );

	_normal = cross( v1, v2 );
	_normal.Normalize();
}

void Triangle::Transform( Matrix4 mat )
{
	_vertices[0].pos *= mat;
	_vertices[1].pos *= mat;
	_vertices[2].pos *= mat;
}

bool Triangle::Clipping( float nearZ, float farZ )
{
	int i;
	for( i=0; i<3; i++ )
	{
		if( _vertices[i].pos.z <= nearZ || _vertices[i].pos.z >= farZ )
		{
			_clipped = true;
			break;
		}
	}

	return _clipped;
}