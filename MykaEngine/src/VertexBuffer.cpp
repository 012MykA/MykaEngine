#include "VertexBuffer.hpp"

namespace MykaEngine
{
    VertexBuffer::VertexBuffer() : m_ID{}
    {
        glGenBuffers(1, &m_ID);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        this->unbind();
    }

    void VertexBuffer::bufferData(const std::vector<Vertex>& vertices)
    {
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    void VertexBuffer::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer)
    {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
} // namespace MykaEngine
