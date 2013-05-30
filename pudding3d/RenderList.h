
#ifndef _RENDER_LIST_H_
#define _RENDER_LIST_H_

#include "Triangle.h"

#include <vector>

class RenderList
{
public:
	typedef std::vector<Triangle> Triangles;

private:
	Triangles _triangles;


public:
	RenderList();
	~RenderList();

	void append(Triangle t);

	const Triangles &triangles() const { return _triangles; }
    Triangles       &triangles() { return _triangles; }

};

#endif