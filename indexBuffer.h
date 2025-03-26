#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

class indexBuffer {
public:
  indexBuffer(const unsigned int* data,unsigned int count);
  ~indexBuffer();
  
  void Bind()const;
  void UnBind()const;
  inline unsigned int GetCount() { return m_count;}

private:
  unsigned int m_rendererID; 
  unsigned int m_count;
};



#endif
