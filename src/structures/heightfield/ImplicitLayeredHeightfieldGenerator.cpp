
#include "ImplicitLayeredHeightfieldGenerator.hpp"

void ImplicitLayeredHeightfieldGenerator::generate(int precision) 
{
	m_h = new LayeredHeightfield(precision);
	for (float x = -1; x<=1; x += 2.0/precision) 
	{
		for (float z = -1; z<=1; z += 2.0/precision) 
		{
			bool was_active = false;
			int level = 0;
			m_h->addLevel();
			for (float y = -1; y<=1; y += 2.0/precision) 
			{
				if (isActive(x,y,z) && !was_active) 
				{
					level++;
					was_active = true;
					if (level == m_h->levelCount()) 
					{
						m_h->addLevel();
					}
					m_h->setBottom(level,x,z,y);
				}
				else if (isActive(x,y,z) && was_active) 
				{
					m_h->setTop(level, x,z,y);
				}
				else if (!isActive(x,y,z) && !was_active) 
				{
					// lol
				}
				else // !isActive and was_active
				{
					m_h->setTop(level,x,z,y);
					was_active = false; 
				}
			}
		}
	}
}

LayeredHeightfield* ImplicitLayeredHeightfieldGenerator::getField() 
{
	return m_h; 
}
