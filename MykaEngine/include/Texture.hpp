#pragma once
#include <glad/glad.h>
#include <stb_image.h>

// std
#include <string>

namespace MykaEngine
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        ~Texture();

        void bind(GLuint slot = 0) const;
        void unbind() const;

    private:
        GLuint m_RendererID = 0;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer = nullptr;
        int m_Width = 0;
        int m_Height = 0;
        int m_BPP = 0;
    };
} // namespace MykaEngine
