#include <boost/test/unit_test.hpp>

#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <core/Vector.hpp>

#include <SDL2/SDL.h>

#include <image/PerlinImageAdapter.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE( noise )
{
	PerlinImageAdapter adapter(new Perlin(16));
	adapter.saveToFile("img.png", 512);
}


