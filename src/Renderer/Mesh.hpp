#pragma once
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

// std
#include <vector>

namespace MykaEngine
{
    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
        
    public: // TODO: make private
        std::vector<Vertex> m_Vertices;
        std::vector<GLuint> m_Indices;

        VertexArray m_VAO;
        VertexBuffer m_VBO;
        IndexBuffer m_IBO;
    };
} // namespace MykaEngine
