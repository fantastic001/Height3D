
#ifndef HEIGHT3D_COLOR_HPP
#define HEIGHT3D_COLOR_HPP

typedef struct Color
{
	float red; 
	float green; 
	float blue;
	float alpha;
	Color(float r, float g, float b) 
	{
		red = r; 
		green = g; 
		blue = b;
		alpha = 1.0;
	}
	Color(float r, float g, float b, float a) 
	{
		red = r; 
		green = g; 
		blue = b;
		alpha = a;
	}
	Color() 
	{
		red = 0; 
		green = 0; 
		blue = 0;
	}

	/// Element-wise multiplication
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
