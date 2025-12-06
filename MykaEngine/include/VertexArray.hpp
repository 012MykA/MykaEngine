#pragma once
#include <glad/glad.h>

namespace MykaEngine
{
    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;

    private:
        GLuint m_ID;
    };
} // namespace MykaEngine
