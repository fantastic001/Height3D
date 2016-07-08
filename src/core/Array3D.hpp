
#ifndef HEIGHT3D_ARRAY3D_HPP
#define HEIGHT3D_ARRAY3D_HPP

template <typename T> class Array3D
{
	T ***m_array;
	int m_a, m_b, m_c;

	void destroy() 
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

	void create(int a, int b, int c) 
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
public:

	Array3D() 
	{
	
	}

	Array3D(int a, int b, int c) 
	{
		create(a,b,c);
	}
	~Array3D() 
	{
		destroy();
	}

	T& value(int i, int j, int k) 
	{
		return m_array[i][j][k];
	}

	T& operator() (int i, int j, int k) 
	{
		return value(i,j,k);
	}
	
	Array3D& operator=(Array3D& a) 
	{
		destroy();
		create(a.getSizeX(), a.getSizeY(), a.getSizeZ());
		for (int i = 0; i<a.getSizeX(); i++) 
		{
			for (int j = 0; j<a.getSizeY(); j++) 
			{
				for (int k = 0; k<a.getSizeZ(); k++) 
				{
					m_array[i][j][k] = a(i,j,k);
				}
			}
		}
	}

	int getSizeX() {return m_a;}
	int getSizeY() {return m_b;}
	int getSizeZ() {return m_c;}
};

#endif // HEIGHT3D_ARRAY3D_HPP
