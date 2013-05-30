
#include "Color.h"

Color::Color(float r, float g, float b, float a)
	:R(r), G(g), B(b), A(a)
{
	
}

uint32_t Color::ToUInt32() const
{
	// 0xRRGGBBAA like opengl
	uint32_t color = 0;

	// mapping 0 to 255. 8-bit each color
	int r = R * 255;
	int g = G * 255;
	int b = B * 255;
	int a = A * 255;
	
	color += r << 24;
	color += g << 16;
	color += b << 8;
	color += a << 0;

	return color;
}

Color Color::operator + (const Color& c) const
{
	return Color( this->R + c.R, 
				this->G + c.G, 
				this->B + c.B, 
				this->A + c.A );
}

Color Color::operator - (const Color& c) const
{
	return Color( this->R - c.R, 
				this->G - c.G, 
				this->B - c.B, 
				this->A - c.A );
}

Color Color::operator * ( float f ) const
{
	return Color( this->R * f, 
				this->G * f, 
				this->B * f, 
				this->A * f );
}
