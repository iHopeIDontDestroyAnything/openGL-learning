#include "vertexBufferLayout.h"


namespace layout
{
  template<typename T>
  unsigned int add(unsigned int count,std::vector<vertexBufferElement> &src) 
  { 
    return 0;
  }

  template<>
  unsigned int add<float>(unsigned int count,std::vector<vertexBufferElement> &src) 
  {
    GLCall(src.push_back({ GL_FLOAT,count,GL_FALSE }));
    return vertexBufferElement::getSizeOfType(GL_FLOAT)* count; 
  }
  template<>
  unsigned int add<unsigned int>(unsigned int count,std::vector<vertexBufferElement> &src)
  {
    GLCall(src.push_back( {GL_UNSIGNED_INT,count,GL_FALSE} ));
    return vertexBufferElement::getSizeOfType(GL_UNSIGNED_INT)*count; 

  }
  template<>
  unsigned int add<unsigned char>(unsigned int count,std::vector<vertexBufferElement> &src)
  {
    GLCall(src.push_back( {GL_UNSIGNED_BYTE,count,GL_TRUE} ));
    return vertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE)*count; 

  }

};


