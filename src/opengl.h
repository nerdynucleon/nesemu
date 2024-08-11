#pragma once 
#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif


class OpenGL {
  public:
    OpenGL();
  
    void init();
    void render(const void *data, int width, int height);
  private:
    GLuint ppuTexture;
    GLuint programID;
    GLuint VAO;
};

#define DEBUG 1

#ifdef DEBUG

#define GL(glFunc) \
{ \
 glFunc; \
 GLenum err = glGetError(); \
 if (err != GL_NO_ERROR) { \
  std::cerr << "OpenGL error: 0x" << std::hex << err << std::dec << " - "<< __FILE__ << ":" <<__LINE__ << "  " << __FUNCTION__ << "()" << std::endl; \
  exit(-1); \
 } \
} \

#else 

#define GL(glFunc) \
  glFunc; \

#endif
