
#ifndef HEIGHT3D_TEXTURE_ATLAS_HPP
#define HEIGHT3D_TEXTURE_ATLAS_HPP

#include "Texture.hpp"

#include <vector>

class TextureAtlas 
{
	int m_height, m_width; 
	std::vector<Texture> m_textures;

public:
	TextureAtlas();

	void addTexture(Texture t);
	Texture generateAtlas(); 
	float getTexturePosition(int index);
	float getX(int index, float x);
	float getY(int index, float y);
};

#endif // HEIGHT3D_TEXTURE_ATLAS_HPP
