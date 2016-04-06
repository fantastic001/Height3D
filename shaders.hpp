#ifndef HEIGHT3D_SHADERS_HPP
#define HEIGHT3D_SHADERS_HPP

#include <GL/gl.h>
#include <GL/glew.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "core/Shader.hpp"
#include "core/Program.hpp"

using namespace std;

Program initProgram(void)
{

    glewInit();
    Program program;
    program.addShader(Shader(GL_VERTEX_SHADER, "shader.vp"));
    program.addShader(Shader(GL_FRAGMENT_SHADER, "shader.fp"));
    program.link();
    program.bind();
    return program;
}


#endif // HEIGHT3D_SHADERS_HPP
