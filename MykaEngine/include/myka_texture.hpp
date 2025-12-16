#pragma once

#include <glad/glad.h>
#include <stb_image.h>

// std
#include <string>
#include <filesystem>

namespace MykaEngine
{
    class Texture
    {
    public:
        Texture() = default;
        Texture(const std::filesystem::path &path);
        ~Texture();

        void loadFromFile(const std::filesystem::path &path);

        void bind(GLuint slot = 0) const;
        void unbind() const;

    private:
        GLuint m_RendererID = 0;
        unsigned char *m_LocalBuffer = nullptr;
        int m_Width = 0;
        int m_Height = 0;
        int m_BPP = 0;
    };
} // namespace MykaEngine
