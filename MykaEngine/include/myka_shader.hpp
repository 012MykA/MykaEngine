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
#include <stdexcept>
#include <format>
#include <unordered_map>

namespace MykaEngine
{
    class Shader
    {
    public:
        Shader() = default;
        Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
        ~Shader();

        void loadFromFile(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath);
        void loadFromSource(const std::string& vertexData, const std::string& fragmentData);

        void use() const;
        void unuse() const;

    public:
        GLuint getID() const;

        void setUniformBool(const std::string &name, bool value) const;
        void setUniformInt(const std::string &name, int value) const;
        void setUniformFloat(const std::string &name, float value) const;
        void setUniformVec2(const std::string &name, const glm::vec2 &value) const;
        void setUniformVec3(const std::string &name, const glm::vec3 &value) const;
        void setUniformVec4(const std::string &name, const glm::vec4 &value) const;
        void setUniformMat3(const std::string &name, const glm::mat3 &matrix) const;
        void setUniformMat4(const std::string &name, const glm::mat4 &matrix) const;
        
        GLint getUniformLocation(const std::string &name) const;

    private:
        GLuint compileShader(unsigned int type, const std::string& source);
        void linkProgram();

    private:
        GLuint m_Program;
        mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
    };
} // namespace MykaEngine
