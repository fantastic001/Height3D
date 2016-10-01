
#include "Array3DLayeredHeightfieldAdapter.hpp"



bool Array3DLayeredHeightfieldAdapter::isActive(int i, int j, int k) 
{
	return (*m_arr)(i,j,k);
	
}

Array3DLayeredHeightfieldAdapter::Array3DLayeredHeightfieldAdapter(Array3D<bool> arr) 
{
	m_precision = arr.getSizeX() - 1;
	m_arr = new Array3D<bool>(m_precision, m_precision, m_precision);
	(*m_arr) = arr;
	m_h = new LayeredHeightfield(m_precision);
}

void Array3DLayeredHeightfieldAdapter::generate()
{

	m_h->addLevel();
	for (int i = 0; i<m_precision; i++)
	{
		for (int k = 0; k<= m_precision; k++) 
		{
			bool was_active = false;
			int level = 0;
			for (int j =0; j<= m_precision; j++)
			{
				float y = 2.0 * j / m_precision - 1.0;
				if (isActive(i,j,k) && !was_active) 
				{
					was_active = true;
					if (level+1 == m_h->levelCount()) 
					{
						level++;
						m_h->addLevel();
					}
					m_h->setBottom(level,i,k,y);
				}
				else if (isActive(i,j,k) && was_active) 
				{
					m_h->setTop(level, i,k,y);
				}
				else if (!isActive(i,j,k) && !was_active) 
				{
					// lol
				}
				else // !isActive and was_active
				{
					m_h->setTop(level,i,k,y);
					was_active = false; 
				}
			}
		}
	}
}

LayeredHeightfield* Array3DLayeredHeightfieldAdapter::getField() 
{
	return m_h; 
}
