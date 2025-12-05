#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

// std
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace MykaEngine
{
    class Shader
    {
    public:
        Shader(const std::string &vertex, const std::string &fragment);
        ~Shader();

        void use() const;

    public:
        void setUniform3f(const std::string &name, const glm::vec3 &value);
        void setUniform1i(const std::string &name, float value);

    private:
        void compileShaders();
        GLint getUniformLocation(const std::string &name);
        std::string getFileContent(const std::string &path);

        GLuint m_Program;
        std::unordered_map<std::string, GLint> m_UniformLocationCache;

        std::string m_VertexData;
        std::string m_FragmentData;
    };
} // namespace MykaEngine
