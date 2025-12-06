#include "Mesh.hpp"

namespace MykaEngine
{
    Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) : m_Vertices(vertices), m_Indices(indices)
    {
        m_VAO.bind();

        m_VBO.bind();
        m_VBO.bufferData(m_Vertices);

        m_IBO.bind();
        m_IBO.bufferData(m_Indices);

        m_VBO.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
        m_VBO.vertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));

        m_IBO.unbind();
        m_VBO.unbind();
        m_VAO.unbind();
    }

    void Mesh::bind() const
    {
        m_VAO.bind();
        m_IBO.bind();
    }
    void Mesh::unbind() const
    {
        m_VAO.unbind();
        m_IBO.unbind();
    }

    uint32_t Mesh::getIndexCount() const
    {
        return m_IBO.getCount();
    }
} // namespace MykaEngine
