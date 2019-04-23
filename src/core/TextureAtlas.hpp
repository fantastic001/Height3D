
#ifndef HEIGHT3D_TEXTURE_ATLAS_HPP
#define HEIGHT3D_TEXTURE_ATLAS_HPP

#include "Texture.hpp"

#include <vector>

/// Class representing array of textures
class TextureAtlas 
{
	int m_height, m_width; 
	std::vector<Texture> m_textures;

public:
	TextureAtlas();

	void addTexture(Texture t);

	/// Generate big texture out of added textures to atlas. dimmensions of big texture are: max(width_i) x sum(height_i)
	Texture generateAtlas(); 
	float getTexturePosition(int index);
	float getX(int index, float x);
	float getY(int index, float y);
};

#endif // HEIGHT3D_TEXTURE_ATLAS_HPP
