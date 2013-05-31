
#include "Mesh.h"
#include "Renderer.h"
#include "util.h"
#include "Triangle.h"

#include <Windows.h>
#include <stdio.h>

Mesh::Mesh()
{

}

Mesh::Mesh( char* filepath )
{
	create( filepath );
}

Mesh::~Mesh()
{
	if( vertices )
		delete[] vertices;

	if( indices )
		delete[] indices;
}

void Mesh::create(char* filepath)
{
	//File load
	char* path = makeAbsolutePath( filepath );
	
	FILE* fp;
	fopen_s( &fp, filepath, "r" );
	if( NULL == fp ) 
	{
		MessageBox( NULL, "Failed to create mesh", "Mesh", MB_ICONERROR );
		exit(1);
	}

	int nVertex,i;
	fscanf( fp, "%d", &nVertex );
	vertices = new Vertex[nVertex];

	float x, y, z;
	for( i=0; i<nVertex; i++ )
	{
		Vertex vtx;
		fscanf_s( fp, "%f %f %f", &x, &y, &z );
		x += pos.x;
		y += pos.y;
		z += pos.z;
		vtx.pos.Set( x, y, z, 1 );
		vtx.color.R = (float)(rand()%256) / 255;
		vtx.color.G = (float)(rand()%256) / 255;
		vtx.color.B = (float)(rand()%256) / 255;

		vertices[i] = vtx;
	}

	fscanf_s( fp, "%d", &nPolygon );
	indices = new int[nPolygon * 3];
	for( i=0; i<nPolygon; i++ )
	{
		fscanf_s( fp, "%d %d %d", &indices[i*3], &indices[i*3+1], &indices[i*3+2] );
	}

	fclose( fp );
}

void Mesh::draw()
{
	//Renderer::sharedDirector()->drawPolygon( vertices, indices, nPolygon );
}

RenderList::Triangles Mesh::GetTriangles()
{
	std::vector<Triangle> triangles;

	int i;
	for( i=0; i<nPolygon; i++ )
	{
		Vertex arr[3];
		arr[0] = vertices[ indices[ i*3 ] ];
		arr[1] = vertices[ indices[ i*3+1 ] ];
		arr[2] = vertices[ indices[ i*3+2 ] ];

		Triangle t( arr );
		triangles.push_back( t );
	}

	return triangles;
}