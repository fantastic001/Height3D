#include <boost/test/unit_test.hpp>

#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <core/Vector.hpp>

#include <SDL2/SDL.h>

#include <noise/perlin/PerlinImageAdapter.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE( noise_perlin_test )
{
	PerlinImageAdapter p;
	cout << "Adding frequency 4\n";
	p.addFrequency(2, 0.5);
	
	cout << "Adding frequency 16\n";
	p.addFrequency(16, 0.15);
	
	cout << "Adding frequency 32\n";
	p.addFrequency(32, 0.03);

	cout << "Adding frequency 64\n";
	p.addFrequency(64, 0.02);

	cout << "Sampling\n";
	p.saveToFile("img.png", 512);
}


