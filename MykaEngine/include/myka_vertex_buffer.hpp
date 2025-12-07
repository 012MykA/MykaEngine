#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

// std
#include <vector>

namespace MykaEngine
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec2 texCoord;
        glm::vec3 normal;
    };

    class VertexBuffer
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        void bufferData(const std::vector<Vertex>& vertices);
        void vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

        void bind() const;
        void unbind() const;

    private:
        GLuint m_ID;
    };
} // namespace MykaEngine