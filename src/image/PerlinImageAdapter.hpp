
#ifndef HEIGHT3D_IMAGE_PERLIN_IMAGE_ADAPTER_HPP
#define HEIGHT3D_IMAGE_PERLIN_IMAGE_ADAPTER_HPP


#include <noise/Perlin.hpp>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <fstream>

using namespace std;
using namespace cv;

class PerlinImageAdapter 
{
	Perlin *m_perlin;
public:
	PerlinImageAdapter(Perlin *p) 
	{
		m_perlin = p; 
	}
	
	void saveToFile(char* filename, int frequency)
	{
		Mat img(frequency, frequency, CV_8UC1);
		float t = 1.0 / frequency;
		ofstream f("output.csv");
		for (int i = 0; i< frequency; i++) 
		{
			for (int j = 0; j< frequency; j++) 
			{
				float v = m_perlin->getValue(j*t, i*t);
				f << v;
				img.at<char>(i,j) = (char) ((int) (127*v + 127));
				if (j == frequency - 1) f << "\n";
				else f << ",";
			}
		}
		f.close();
		imwrite(filename, img);
	}

};

#endif // HEIGHT3D_IMAGE_PERLIN_IMAGE_ADAPTER_HPP
