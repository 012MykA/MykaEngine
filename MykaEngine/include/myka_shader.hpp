#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace MykaEngine
{
    class Shader
    {
    public:
        Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
        ~Shader();

        void use() const;

    public:
        void setUniform3f(const std::string &name, const glm::vec3 &value);
        void setUniform4f(const std::string &name, const glm::vec4 &value);
        void setUniform1i(const std::string &name, int value);
        void setUniform1f(const std::string &name, float value);
        void setUniformMat3f(const std::string &name, const glm::mat3 &matrix);
        void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

    private:
        void compileShaders();
        GLint getUniformLocation(const std::string &name);
        std::string getFileContent(const std::filesystem::path &path);

        GLuint m_Program;
        std::unordered_map<std::string, GLint> m_UniformLocationCache;

        std::string m_VertexData;
        std::string m_FragmentData;
    };
} // namespace MykaEngine
