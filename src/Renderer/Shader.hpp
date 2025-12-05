#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

// std
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace MykaEngine
{
    class Shader
    {
    public:
        Shader(const std::string &vertex, const std::string &fragment);
        ~Shader();

        void use() const;

    public:
        void setUniform3f(const std::string &name, const glm::vec3 &value) const;
        void setUniform1i(const std::string &name, float value) const;

    private:
        void compileShaders();
        GLuint getUniformLocation(const std::string &name) const;
        std::string getFileContent(const std::string &path);

        GLuint m_Program;

        std::string m_VertexData;
        std::string m_FragmentData;
    };
} // namespace MykaEngine
