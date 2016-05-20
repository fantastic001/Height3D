
#ifndef HEIGHT3D_TEXTURES_GRADIENT_TEXTURE_FACTORY_HPP
#define HEIGHT3D_TEXTURES_GRADIENT_TEXTURE_FACTORY_HPP

#include <core/TextureFactory.hpp>
#include <core/Color.hpp>

class GradientTextureFactory : public TextureFactory
{

	Color m_from, m_to;
	int m_width, m_height; 
	bool m_vertical;

public:
	/*
	If vertical is false then horizontal linear gradient is applied

	Horizontal gradient is formed from left to right 
	Vertical gradient is formed top-down
	*/
	GradientTextureFactory(Color from, Color to, int width, int height, bool vertical = false);

protected:
	Texture load();

};

#endif // HEIGHT3D_TEXTURES_GRADIENT_TEXTURE_FACTORY_HPP
