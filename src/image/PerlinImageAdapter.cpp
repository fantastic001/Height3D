#include "PerlinImageAdapter.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

#include <fstream>

using namespace std;
using namespace cv;

void PerlinImageAdapter::addFrequency(int frequency, float amplitude) 
{
	m_perlins.push_back(new Perlin(frequency));
	m_amplitudes.push_back(amplitude);
}
	
void PerlinImageAdapter::saveToFile(char* filename, int frequency)
{
	Mat img(frequency, frequency, CV_8UC1);
	float t = 1.0 / frequency;
	ofstream f("output.csv");
	for (int i = 0; i< frequency; i++) 
	{
		for (int j = 0; j< frequency; j++) 
		{
			float v = 0;
			for (int p = 0; p<m_perlins.size(); p++) 
			{
				v += m_amplitudes.at(p) * m_perlins.at(p)->getValue(j*t, i*t);
			}
			f << v;
			img.at<char>(i,j) = (char) ((int) (127*v + 127));
			if (j == frequency - 1) f << "\n";
			else f << ",";
		}
	}
	f.close();
	imwrite(filename, img);
}
