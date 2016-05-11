
#ifndef HEIGHT3D_COLOR_HPP
#define HEIGHT3D_COLOR_HPP

typedef struct Color
{
	float red; 
	float green; 
	float blue;
	Color(float r, float g, float b) 
	{
		red = r; 
		green = g; 
		blue = b;
	}
	Color() 
	{
		red = 0; 
		green = 0; 
		blue = 0;
	}
	Color operator*(Color c)
	{
		return Color(red * c.red, green * c.green, blue * c.blue);
	}
	Color operator*(float a) 
	{
		return Color(red * a, green * a, blue * a);
	}
} Color;

#endif // HEIGHT3D_COLOR_HPP
