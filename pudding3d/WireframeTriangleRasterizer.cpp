
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

void WireframeTriangleRasterizer::drawLine(FrameBuffer* buffer, Vertex v1, Vertex v2 )
{
	if( ClipLine( buffer, v1.pos, v2.pos ) )
	{
		Color color1 = v1.color;
		float x1 = v1.pos.x;
		float y1 = v1.pos.y;
		float z1 = v1.pos.z;

		Color color2 = v2.color;
		float x2 = v2.pos.x;
		float y2 = v2.pos.y;
		float z2 = v2.pos.z;

		float xdiff = (x2 - x1);
		float ydiff = (y2 - y1);

		if(xdiff == 0.0f && ydiff == 0.0f) 
		{
			buffer->SetPixel( static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(z1), color1 );
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
			float x, y, z;
			Color color;
			for( x = xmin; x <= xmax; x += 1.0f ) 
			{
				y = y1 + ( (x - x1) * slope );
				z = z1 + ( (x - x1) * slope );
				color = color1 + ( ( color2 - color1 ) * ( ( x - x1 ) / xdiff) );
				buffer->SetPixel( static_cast<int>(x), static_cast<int>(y), static_cast<int>(z1), color );
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
			float x, y, z;
			Color color;
			for( y = ymin; y <= ymax; y += 1.0f ) 
			{
				x = x1 + ( (y - y1) * slope );
				z = z1 + ( (y - y1) * slope );
				color = color1 + ( ( color2 - color1 ) * ( ( y - y1 ) / ydiff) );
				buffer->SetPixel( static_cast<int>(x), static_cast<int>(y), static_cast<int>(z2), color );
			}
		}
	}
}

bool WireframeTriangleRasterizer::ClipLine(FrameBuffer* buffer, Vector4 &p1, Vector4 &p2)
{
	// internal clipping codes
	const int CLIP_CODE_C = 0x0000;
	const int CLIP_CODE_N = 0x0008;
	const int CLIP_CODE_S = 0x0004;
	const int CLIP_CODE_E = 0x0002;
	const int CLIP_CODE_W = 0x0001;

	const int CLIP_CODE_NE = 0x000a;
	const int CLIP_CODE_SE = 0x0006;
	const int CLIP_CODE_NW = 0x0009;
	const int CLIP_CODE_SW = 0x0005;

	int xc1 = static_cast<int>(p1.x),
		yc1 = static_cast<int>(p1.y),
		xc2 = static_cast<int>(p2.x),
		yc2 = static_cast<int>(p2.y);

	int p1_code = 0, p2_code = 0;

	int width = buffer->GetWidth();
	int height = buffer->GetHeight();

	// determine codes for p1 and p2
	if (p1.y < buffer->GetOriginY())
		p1_code |= CLIP_CODE_N;
	else
		if (p1.y > height)
			p1_code |= CLIP_CODE_S;

	if (p1.x < buffer->GetOriginX())
		p1_code |= CLIP_CODE_W;
	else
		if (p1.x > width)
			p1_code |= CLIP_CODE_E;

	if (p2.y < buffer->GetOriginY())
		p2_code |= CLIP_CODE_N;
	else
		if (p2.y > height)
			p2_code |= CLIP_CODE_S;

	if (p2.x < buffer->GetOriginX())
		p2_code |= CLIP_CODE_W;
	else
		if (p2.x > width)
			p2_code |= CLIP_CODE_E;

	// try and trivially reject
	if ((p1_code & p2_code))
		return false;

	// test for totally visible, if so leave points untouched
	if (p1_code == 0 && p2_code == 0)
		return true;

	// determine end clip point for p1
	switch(p1_code)
	{
	case CLIP_CODE_C:
		break;

	case CLIP_CODE_N:
		yc1 = buffer->GetOriginY();
		xc1 = p1.x + 0.5 + (buffer->GetOriginY() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
		break;

	case CLIP_CODE_S:
		yc1 = buffer->GetHeight();
		xc1 = p1.x + 0.5 + (buffer->GetHeight() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
		break;

	case CLIP_CODE_W:
		xc1 = buffer->GetOriginX();
		yc1 = p1.y + 0.5 + (buffer->GetOriginX() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		break;

	case CLIP_CODE_E:
		xc1 = buffer->GetWidth();
		yc1 = p1.y + 0.5 + (buffer->GetWidth() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		break;

		// these cases are more complex, must compute 2 intersections
	case CLIP_CODE_NE:
		// north hline intersection
		yc1 = buffer->GetOriginY();
		xc1 = p1.x + 0.5 + (buffer->GetOriginY() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < buffer->GetOriginX() || xc1 > buffer->GetWidth())
		{
			// east vline intersection
			xc1 = buffer->GetWidth();
			yc1 = p1.y + 0.5 + (buffer->GetWidth() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}
		break;

	case CLIP_CODE_SE:
		// south hline intersection
		yc1 = buffer->GetHeight();
		xc1 = p1.x + 0.5 + (buffer->GetHeight() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < buffer->GetOriginX() || xc1 > buffer->GetWidth())
		{
			// east vline intersection
			xc1 = buffer->GetWidth();
			yc1 = p1.y + 0.5 + (buffer->GetWidth() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}
		break;

	case CLIP_CODE_NW:
		// north hline intersection
		yc1 = buffer->GetOriginY();
		xc1 = p1.x + 0.5 + (buffer->GetOriginY() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < buffer->GetOriginX() || xc1 > buffer->GetWidth())
		{
			xc1 = buffer->GetOriginX();
			yc1 = p1.y + 0.5 + (buffer->GetOriginX() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}
		break;

	case CLIP_CODE_SW:
		// south hline intersection
		yc1 = buffer->GetHeight();
		xc1 = p1.x + 0.5 + (buffer->GetHeight() - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc1 < buffer->GetOriginX() || xc1 > buffer->GetWidth())
		{
			xc1 = buffer->GetOriginX();
			yc1 = p1.y + 0.5 + (buffer->GetOriginX() - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
		}
		break;

	default:
		break;
	}

	// determine clip point for p2
	switch(p2_code)
	{
	case CLIP_CODE_C:
		break;

	case CLIP_CODE_N:
		yc2 = buffer->GetOriginY();
		xc2 = p2.x + (buffer->GetOriginY() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);
		break;

	case CLIP_CODE_S:
		yc2 = buffer->GetHeight();
		xc2 = p2.x + (buffer->GetHeight() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);
		break;

	case CLIP_CODE_W:
		xc2 = buffer->GetOriginX();
		yc2 = p2.y + (buffer->GetOriginX() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
		break;

	case CLIP_CODE_E:
		xc2 = buffer->GetWidth();
		yc2 = p2.y + (buffer->GetWidth() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
		break;

		// these cases are more complex, must compute 2 intersections
	case CLIP_CODE_NE:
		// north hline intersection
		yc2 = buffer->GetOriginY();
		xc2 = p2.x + 0.5 + (buffer->GetOriginY() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < buffer->GetOriginX() || xc2 > buffer->GetWidth())
		{
			// east vline intersection
			xc2 = buffer->GetWidth();
			yc2 = p2.y + 0.5 + (buffer->GetWidth() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
		}
		break;

	case CLIP_CODE_SE:
		// south hline intersection
		yc2 = buffer->GetHeight();
		xc2 = p2.x + 0.5 + (buffer->GetHeight() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < buffer->GetOriginX() || xc2 > buffer->GetWidth())
		{
			// east vline intersection
			xc2 = buffer->GetWidth();
			yc2 = p2.y + 0.5 + (buffer->GetWidth() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
		}
		break;

	case CLIP_CODE_NW:
		// north hline intersection
		yc2 = buffer->GetOriginY();
		xc2 = p2.x + 0.5 + (buffer->GetOriginY() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < buffer->GetOriginX() || xc2 > buffer->GetWidth())
		{
			xc2 = buffer->GetOriginX();
			yc2 = p2.y + 0.5 + (buffer->GetOriginX() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
		}
		break;

	case CLIP_CODE_SW:
		// south hline intersection
		yc2 = buffer->GetHeight();
		xc2 = p2.x + 0.5 + (buffer->GetHeight() - p2.y) * (p1.x - p2.x) / (p1.y - p2.y);

		// test if intersection is valid, of so then done, else compute next
		if (xc2 < buffer->GetOriginX() || xc2 > buffer->GetWidth())
		{
			xc2 = buffer->GetOriginX();
			yc2 = p2.y + 0.5 + (buffer->GetOriginX() - p2.x) * (p1.y - p2.y) / (p1.x - p2.x);
		}
		break;

	default:
		break;
	}

	// do bounds check
	if ((xc1 < buffer->GetOriginX()) || (xc1 > buffer->GetWidth()) ||
		(yc1 < buffer->GetOriginY()) || (yc1 > buffer->GetHeight())||
		(xc2 < buffer->GetOriginX()) || (xc2 > buffer->GetWidth()) ||
		(yc2 < buffer->GetOriginY()) || (yc2 > buffer->GetHeight()))
	{
		return false;
	}

	// store vars back
	p1.x = xc1;
	p1.y = yc1;
	p2.x = xc2;
	p2.y = yc2;

	return true;
}