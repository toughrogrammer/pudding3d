
#include "WireframeTriangleRasterizer.h"
#include "FrameBuffer.h"

#include <stdio.h>

WireframeTriangleRasterizer::WireframeTriangleRasterizer()
{

}

WireframeTriangleRasterizer::~WireframeTriangleRasterizer()
{

}

// t : transformed triangle, so that vertex's z coordinate is 0 )
void WireframeTriangleRasterizer::drawTriangle( FrameBuffer* buffer, const Triangle& t )
{
	Vertex v1 = t.v(0);
	Vertex v2 = t.v(1);
	Vertex v3 = t.v(2);
	
	drawLine( buffer, v1, v2 );
	drawLine( buffer, v2, v3 );
	drawLine( buffer, v3, v1 );
}

void WireframeTriangleRasterizer::drawLine( FrameBuffer* buffer, Vertex v1, Vertex v2 )
{
	Color c1, c2;
	float x1, y1, x2, y2;

	c1 = v1.color;
	x1 = v1.pos.x;
	y1 = v1.pos.y;

	c2 = v2.color;
	x2 = v2.pos.x;
	y2 = v2.pos.y;

	drawLine( buffer, c1, x1, y1, c2, x2, y2 );

}

void WireframeTriangleRasterizer::drawLine( FrameBuffer* buffer, const Color &color1, float x1, float y1, const Color &color2, float x2, float y2 )
{
	ClipLine( buffer, x1, y1, x2, y2 );

	float xdiff = (x2 - x1);
	float ydiff = (y2 - y1);

	if(xdiff == 0.0f && ydiff == 0.0f) 
	{
		buffer->SetPixel( static_cast<int>(x1), static_cast<int>(y1), color1 );
		return;
	}

	if(fabs(xdiff) > fabs(ydiff)) 
	{
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if( x1 < x2 ) 
		{
			xmin = x1;
			xmax = x2;
		} 
		else 
		{
			xmin = x2;
			xmax = x1;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		float x, y;
		Color color;
		for( x = xmin; x <= xmax; x += 1.0f ) 
		{
			y = y1 + ( (x - x1) * slope );
			color = color1 + ( ( color2 - color1 ) * ( ( x - x1 ) / xdiff) );
			buffer->SetPixel( static_cast<int>(x), static_cast<int>(y), color );
		}
	}
	else
	{
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if( y1 < y2 ) 
		{
			ymin = y1;
			ymax = y2;
		} 
		else 
		{
			ymin = y2;
			ymax = y1;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		float x, y;
		Color color;
		for( y = ymin; y <= ymax; y += 1.0f ) 
		{
			x = x1 + ( (y - y1) * slope );
			color = color1 + ( ( color2 - color1 ) * ( ( y - y1 ) / ydiff) );
			buffer->SetPixel( static_cast<int>(x), static_cast<int>(y), color );
		}
	}
}

typedef int OutCode;
bool WireframeTriangleRasterizer::ClipLine( FrameBuffer* buffer, float& x1, float& y1, float& x2, float& y2 )
{
	const int INSIDE = 0; // 0000
	const int LEFT = 1;   // 0001
	const int RIGHT = 2;  // 0010
	const int BOTTOM = 4; // 0100
	const int TOP = 8;    // 1000

	float width = (float)buffer->getWidth();
	float height = (float)buffer->getHeight();

	// Outcode compute
	OutCode r1 = 0, r2=0;
	{
		if( y1 < 0 )
			r1 |= TOP;
		if( y1 > height )
			r1 |= BOTTOM;

		if( x1 < 0 )
			r1 |= LEFT;
		if( x1 > width )
			r1 |= RIGHT;

		if( y2 < 0 )
			r2 |= TOP;
		if( y2 > height )
			r2 |= BOTTOM;

		if( x2 < 0 )
			r2 |= LEFT;
		if( x2 > width )
			r2 |= RIGHT;

		if( !(r1 || r2) )
			return true;

		if( r1 & r2 )
			return false;
	}

	// Line clip
	pdPoint pTemp1, pTemp2;
	pTemp1.x = x1;
	pTemp1.y = y1;
	pTemp2.x = x2;
	pTemp2.y = y2;
	{
		switch( r1 )
		{
		case 0:
			break;
		case LEFT:
			pTemp1.x = 0;
			pTemp1.y = y1 + ((-x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			break;
		case RIGHT:
			pTemp1.x = width;
			pTemp1.y = y1 + ((pTemp1.x - x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			break;

		case BOTTOM:
			pTemp1.y = height;
			pTemp1.x = x1 + ((pTemp1.y - y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			break;
		case BOTTOM | LEFT:
			pTemp1.y = height;
			pTemp1.x = x1 + ((pTemp1.y - y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp1.x < 0 )
			{
				pTemp1.x = 0;
				pTemp1.y = y1 + ((-x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;
		case BOTTOM | RIGHT:
			pTemp1.y = height;
			pTemp1.x = x1 + ((pTemp1.y - y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp1.x > width )
			{
				pTemp1.x = width;
				pTemp1.y = y1 + ((pTemp1.x - x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;

		case TOP:
			pTemp1.y = 0;
			pTemp1.x = x1 + ((-y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			break;
		case TOP | LEFT:
			pTemp1.y = 0;
			pTemp1.x = x1 + ((-y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp1.x < 0 )
			{
				pTemp1.x = 0;
				pTemp1.y = y1 + ((-x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;
		case TOP | RIGHT:
			pTemp1.y = 0;
			pTemp1.x = x1 + ((-y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp1.x > width )
			{
				pTemp1.x = width;
				pTemp1.y = y1 + ((pTemp1.x - x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;
		}

		switch( r1 )
		{
		case 0:
			break;
		case LEFT:
			pTemp2.x = 0;
			pTemp2.y = y1 + ((-x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			break;
		case RIGHT:
			pTemp2.x = width;
			pTemp2.y = y1 + ((pTemp2.x - x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			break;

		case BOTTOM:
			pTemp2.y = height;
			pTemp2.x = x1 + ((pTemp2.y - y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			break;
		case BOTTOM | LEFT:
			pTemp2.y = height;
			pTemp2.x = x1 + ((pTemp2.y - y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp2.x < 0 )
			{
				pTemp2.x = 0;
				pTemp2.y = y1 + ((-x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;
		case BOTTOM | RIGHT:
			pTemp2.y = height;
			pTemp2.x = x1 + ((pTemp2.y - y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp2.x > width )
			{
				pTemp2.x = width;
				pTemp2.y = y1 + ((pTemp2.x - x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;

		case TOP:
			pTemp2.y = 0;
			pTemp2.x = x1 + ((-y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			break;
		case TOP | LEFT:
			pTemp2.y = 0;
			pTemp2.x = x1 + ((-y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp2.x < 0 )
			{
				pTemp2.x = 0;
				pTemp2.y = y1 + ((-x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;
		case TOP | RIGHT:
			pTemp2.y = 0;
			pTemp2.x = x1 + ((-y1) * (x2 - x1) / (y2 - y1) + 0.5f);
			if( pTemp2.x > width )
			{
				pTemp2.x = width;
				pTemp2.y = y1 + ((pTemp2.x - x1) * (y2 - y1) / (x2 - x1) + 0.5f);
			}
			break;
		}
	}
	

	if( (pTemp1.x < 0 || pTemp1.x >= width) && (pTemp1.y < 0 || pTemp1.y >= height) ||
		(pTemp2.x < 0 || pTemp2.x >= width) && (pTemp2.y < 0 || pTemp2.y >= height) )
		return false;

	x1 = pTemp1.x;
	y1 = pTemp1.y;
	x2 = pTemp2.x;
	y2 = pTemp2.y;
	return true;
}