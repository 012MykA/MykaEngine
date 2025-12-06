#pragma once
#include <glad/glad.h>

// std
#include <vector>

namespace MykaEngine
{
    class IndexBuffer
    {
    public:
        IndexBuffer();
        ~IndexBuffer();

        void bufferData(const std::vector<GLuint>& indices);

        void bind() const;
        void unbind() const;

    public:
        uint32_t getCount() const;

    private:
        uint32_t m_Count;
        GLuint m_ID;
    };
} // namespace MykaEngine
