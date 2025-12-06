#include "myka_vertex_array.hpp"

namespace MykaEngine
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_ID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
        this->unbind();
    }

    void VertexArray::bind() const
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }
} // namespace MykaEngine