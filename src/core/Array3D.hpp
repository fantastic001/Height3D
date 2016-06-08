
#ifndef HEIGHT3D_ARRAY3D_HPP
#define HEIGHT3D_ARRAY3D_HPP

template <typename T> class Array3D
{
	T ***m_array;
	int m_a, m_b, m_c;
public:
	Array3D(int a, int b, int c) 
	{
		m_a = a;
		m_b = b; 
		m_c = c;
		m_array = new T** [a];
		for (int i = 0; i<a; i++) 
		{
			m_array[i] = new T* [b];
			for (int j = 0; j<b; j++) 
			{
				m_array[i][j] = new T[c];
			}
		}
	}
	~Array3D() 
	{
		for (int i = 0; i<m_a; i++) 
		{
			for (int j = 0; j<m_b; j++) 
			{
				delete m_array[i][j];
			}
			delete m_array[i];
		}
		delete m_array; 
	}

	T& operator() (int i, int j, int k) 
	{
		return m_array[i][j][k];
	}

	int getSizeX() {return m_a;}
	int getSizeY() {return m_b;}
	int getSizeZ() {return m_c;}
};

#endif // HEIGHT3D_ARRAY3D_HPP
