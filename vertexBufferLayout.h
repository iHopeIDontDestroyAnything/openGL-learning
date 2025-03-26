#ifndef VERTEX_BUFFER_LAYOUT_H_
#define VERTEX_BUFFER_LAYOUT_H_

#include <vector>
#include <GL/glew.h>
#include "renderer.h"
#include <iostream>

struct vertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int getSizeOfType(unsigned int type)
  {
    switch(type)
    {
      case GL_FLOAT:          return 4;
      case GL_UNSIGNED_INT:   return 4;
      case GL_UNSIGNED_BYTE:  return 1;
    }
  ASSERT(false);
  return 0;
  }
};


namespace layout
{
  template<typename T>
  unsigned int add(unsigned int count,std::vector<vertexBufferElement> &src);
  template<>
  unsigned int add<float>(unsigned int count,std::vector<vertexBufferElement> &src); 
  template<>
  unsigned int add<unsigned int>(unsigned int count,std::vector<vertexBufferElement> &src);
  template<>
  unsigned int add<unsigned char>(unsigned int count,std::vector<vertexBufferElement> &src);
};

class vertexBufferLayout 
{
private:
  std::vector<vertexBufferElement> m_Elements;
  unsigned int m_Stride;
public:
  friend unsigned int add(unsigned int count,std::vector<vertexBufferElement> &src);

  vertexBufferLayout()
    :m_Stride(0) {} 

  // ~vertexBufferLayout();

  template<typename T>
  void push(unsigned int count) 
  { 
    GLCall(int stride = layout::add<T>(count,m_Elements);) 
    if(stride <= 0)
    {
    std::cout <<"Attempted to add unsupported type\n";
    }
    m_Stride += stride;
  }


  inline const std::vector<vertexBufferElement> &getElements() const {return m_Elements;}
  inline unsigned int getStride() const { return m_Stride;}

  
};




#endif
