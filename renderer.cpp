#include "renderer.h"
#include <iostream>



void GLCleanErrors()
{
  while(glGetError());
}

bool GLPrintErrors(const char* function, const char *file, int line)
{
  if(GLenum error = glGetError())
  {
    std::cout <<"Error on "<<function
      <<"\nError code : 0x0" << std::hex <<error 
      << "\npath: "<<file
      << "\non line "<<std::dec <<line
      << '\n';
    return false;
  }
  return true;
}
