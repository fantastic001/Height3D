
#include "GradientTextureFactory.hpp"


GradientTextureFactory::GradientTextureFactory(Color from, Color to, int width, int height, bool vertical) 
{
	m_to = to; 
	m_from = from; 
	m_height = height; 
	m_width = width; 
	m_vertical = vertical;
}

Texture GradientTextureFactory::load() 
{
	unsigned char data[m_height][m_width][3];
	for (int i = 0; i<m_height; i++) 
	{
		for (int j = 0; j<m_width; j++) 
		{
			int l;
			if (m_vertical) 
			{
				l = m_height;
				data[i][j][0] = (unsigned char) 255*(m_from.red + i*(m_to.red - m_from.red) / l);
				data[i][j][1] = (unsigned char) 255*(m_from.green + i*(m_to.green - m_from.green) / l);
				data[i][j][2] = (unsigned char) 255*(m_from.blue + i*(m_to.blue - m_from.blue) / l);
			}
			else 
			{
				l = m_width;
				data[i][j][0] = (unsigned char) 255*(m_from.red + j*(m_to.red - m_from.red) / l);
				data[i][j][1] = (unsigned char) 255*(m_from.green + j*(m_to.green - m_from.green) / l);
				data[i][j][2] = (unsigned char) 255*(m_from.blue + j*(m_to.blue - m_from.blue) / l);
			}
		}
	}
	return Texture(GL_TEXTURE_2D, m_width, m_height, data);
}
