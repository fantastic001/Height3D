#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>

#include <SDL2/SDL.h>

#include "debug.hpp"
#include "shaders.hpp"
#include "sdl_init.hpp"

using namespace std; 

int main(int argc, char *argv[])
{
    SDL_Window *mainwindow = sdl_init("tutorial");
    
    /* Clear our buffer with a red background */
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    /* Swap our back buffer to the front */
    SDL_GL_SwapWindow(mainwindow);
    /* Wait 2 seconds */
    SDL_Delay(2000);

    /* Same as above, but green */
    glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);

    /* Same as above, but blue */
    glClearColor ( 0.0, 0.0, 1.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);
    cout << "Compiling...\n";

    // draw red triangle 
    Program program = initProgram();

    cout << "Drawing triangle\n";

    GLuint VertexArrayID;

    glGenVertexArrays(1, &VertexArrayID);

    glBindVertexArray(VertexArrayID);
    
 static const GLfloat g_vertex_buffer_data[] = {

    -1.0f, -1.0f, 0.0f,

    1.0f, -1.0f, 0.0f,

    0.0f,  1.0f, 0.0f,

 }; 



 // This will identify our vertex buffer

 GLuint vertexbuffer;

 // Generate 1 buffer, put the resulting identifier in vertexbuffer

 glGenBuffers(1, &vertexbuffer);

 // The following commands will talk about our 'vertexbuffer' buffer

 glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

 // Give our vertices to OpenGL.

 glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
   

 // 1rst attribute buffer : vertices

 glEnableVertexAttribArray(0);

 glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

 glVertexAttribPointer(

    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.

    3,                  // size

    GL_FLOAT,           // type

    GL_FALSE,           // normalized?

    0,                  // stride

    (void*)0            // array buffer offset

 );

 // Draw the triangle !
 cout << "Drawing primitives\n";

 glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle


    // --------------------------------------------------------------------------------------
    
    
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);
    
    cout << "Exiting...\n";
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    //SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    return 0;
}
