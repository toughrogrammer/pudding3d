
#ifndef _MESH_H_
#define _MESH_H_

#include "Vertex.h"
#include "Triangle.h"
#include "RenderList.h"
#include <vector>

class Mesh
{
private:
	Vector3 pos;
	Vertex* vertices;
	int* indices;
	int nPolygon;

public:
	Mesh();
	~Mesh();

	void create(char* filepath);
	void draw();
	RenderList::Triangles GetTriangles();

};

#endif