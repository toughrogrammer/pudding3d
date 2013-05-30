
#include "RenderList.h"

RenderList::RenderList()
{
	_triangles.clear();
}

RenderList::~RenderList()
{

}

void RenderList::append( Triangle t )
{
	_triangles.push_back( t );
}
