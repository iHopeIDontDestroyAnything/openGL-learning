#include "vertexArray.h"
#include "renderer.h"
#include "GL/glew.h"


vertexArray::vertexArray()
{
  GLCall(glGenVertexArrays(1,&m_rendererID));
}

vertexArray::~vertexArray()
{
  GLCall(__glewDeleteVertexArrays(1, &m_rendererID)); 
}

void vertexArray::addBuffer(const vertexBuffer &vb,const vertexBufferLayout &layout)
{
  vb.Bind();
  Bind();
  const auto& elements = layout.getElements();
  unsigned int offset = 0;
  static_assert(sizeof(unsigned int*) == sizeof(void*),"void not the same as uint");
  for(unsigned int i = 0; i < elements.size();i++) 
  {
    const auto &element = elements[i];
    GLCall(__glewEnableVertexAttribArray(i));
    GLCall(__glewVertexAttribPointer(i,element.count,element.type,element.normalized,layout.getStride(),(const void*)offset));
    offset += element.count * vertexBufferElement::getSizeOfType(element.type);
  }

}



void vertexArray::Bind() const 
{
  GLCall(__glewBindVertexArray(m_rendererID));
}

void vertexArray::Unbind() const 
{
  GLCall(__glewBindVertexArray(0));
}
