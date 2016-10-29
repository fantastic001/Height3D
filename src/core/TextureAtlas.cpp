
#include "TextureAtlas.hpp"

using namespace std; 

TextureAtlas::TextureAtlas() 
{
	m_width = 0;
	m_height = 0;
}

void TextureAtlas::addTexture(Texture t) 
{
	m_textures.push_back(t);
}

Texture TextureAtlas::generateAtlas() 
{
	m_width = 0; 
	m_height = 0;
	int i; 
	for (i=0; i<m_textures.size(); i++) 
	{
		if (m_width < m_textures[i].getWidth()) m_width = m_textures[i].getWidth();
		m_height += m_textures[i].getHeight();
	}
	int w,h;
	w = h = 1;
	while (w<m_width) w *= 2;
	while (h<m_height) h *= 2;
	m_width = w; 
	m_height = h;
	int c = 0; 
	float data[m_height][m_width][3];
	for (i=0; i<m_height; i++) for (int j = 0; j<m_width; j++) for (int k = 0; k<3; k++) data[i][j][k] =0;
	for (i=0; i<m_textures.size(); i++) 
	{
		for (int y = 0; y<m_textures[i].getHeight(); y++) 
		{
			for (int x = 0; x<m_textures[i].getWidth(); x++) 
			{
				for (int k = 0; k<3; k++) data[c + y][x][k] = 
					(float) (* ((float*) (
						m_textures[i].getData() 
						+ sizeof(float) * (y*m_textures[i].getWidth() * 3 + x*3 + k)
					)));
			}
		}
		c += m_textures[i].getHeight(); 
	}
	return Texture(GL_TEXTURE_2D, m_width, m_height, data);
}

float TextureAtlas::getTexturePosition(int index) 
{
	int c = 0;
	for (int i = 0; i<index; i++) c += m_textures[i].getHeight();
	return c / float(m_height);
}

float TextureAtlas::getX(int index, float x) 
{
	return 0.0 + x*m_textures[index].getWidth() / (1.0 * m_width);
}

float TextureAtlas::getY(int index, float y) 
{
	return getTexturePosition(index) + y*m_textures[index].getHeight() / (1.0 * m_height);
}
