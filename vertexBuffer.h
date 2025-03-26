#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

class vertexBuffer {
public:
  vertexBuffer(const void * data,unsigned int size);
  ~vertexBuffer();
  
  void Bind()const;
  void UnBind()const;

private:
  unsigned int m_rendererID; 
};



#endif
