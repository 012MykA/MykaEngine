#pragma once

#include "myka_vertex_array.hpp"
#include "myka_vertex_buffer.hpp"
#include "myka_index_buffer.hpp"

// std
#include <vector>

namespace MykaEngine
{
    class Mesh
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

        void bind() const;
        void unbind() const;

        uint32_t getIndexCount() const;
        
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<GLuint> m_Indices;

        VertexArray m_VAO;
        VertexBuffer m_VBO;
        IndexBuffer m_IBO;
    };
} // namespace MykaEngine
