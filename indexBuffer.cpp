#include "indexBuffer.h"
#include "renderer.h"
#include <cstdlib>

indexBuffer::indexBuffer(const unsigned int *data,unsigned int count)
:m_count(count)
{
    ASSERT(sizeof(unsigned int)==sizeof(GLuint));
    GLCall(glGenBuffers(1,&m_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count *sizeof(unsigned int),data,GL_STATIC_DRAW));

}

indexBuffer::~indexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_rendererID));
}

void indexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_rendererID));
}

void indexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

