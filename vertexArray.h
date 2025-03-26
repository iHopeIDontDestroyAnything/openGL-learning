#ifndef VERTEX_ARRAY_H_
#define VERTEX_ARRAY_H_

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"

class vertexArray {
public:
  vertexArray();
  ~vertexArray();
  void addBuffer(const vertexBuffer &vb,const vertexBufferLayout &layout);
  void Bind() const;
  void Unbind() const;

private:
  unsigned int m_rendererID; 
};


#endif
