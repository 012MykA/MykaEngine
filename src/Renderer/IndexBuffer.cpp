#include "IndexBuffer.hpp"

namespace MykaEngine
{
    IndexBuffer::IndexBuffer() : m_Count{}
    {
        glGenBuffers(1, &m_ID);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void IndexBuffer::bufferData(const std::vector<GLuint> &indices)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        m_Count = indices.size();
    }

    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    }

    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    uint32_t IndexBuffer::getCount() const
    {
        return m_Count;
    }
} // namespace MykaEngine
