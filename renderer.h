#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <cstdlib>

#define ASSERT(x) if (!(x)) exit(0);

#ifdef B_DEBUG
#define GLCall(x) GLCleanErrors();\
  x;\
  ASSERT(GLPrintErrors(#x,__FILE__,__LINE__))
#else
#define GLCall(x) x 
#endif

void GLCleanErrors();
bool GLPrintErrors(const char* function, const char *file, int line);






#endif
