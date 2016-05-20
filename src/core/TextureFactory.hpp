
#ifndef HEIGHT3D_TEXTURE_FACTORY_HPP
#define HEIGHT3D_TEXTURE_FACTORY_HPP

#include "Texture.hpp"

class TextureFactory
{

public:
	Texture getTexture();

protected:
	virtual Texture load() = 0;
};

#endif // HEIGHT3D_TEXTURE_FACTORY_HPP
