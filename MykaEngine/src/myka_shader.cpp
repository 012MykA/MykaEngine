#include "myka_shader.hpp"

namespace MykaEngine
{
    Shader::Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
    {
        loadFromFile(vertexPath, fragmentPath);
    }

    Shader::~Shader()
    {
        if (m_Program != 0)
        {
            glDeleteProgram(m_Program);
        }
    }

    void Shader::loadFromFile(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
    {
        // Vertex
        std::string vertexCode;
        std::ifstream vShaderFile(vertexPath);
        if (vShaderFile.is_open())
        {
            std::stringstream vShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            vertexCode = vShaderStream.str();
            vShaderFile.close();
        }
        else
        {
            std::cerr << "Failed to open vertex shader file: " << vertexPath << std::endl;
            return;
        }

        // Fragment
        std::string fragmentCode;
        std::ifstream fShaderFile(fragmentPath);
        if (fShaderFile.is_open())
        {
            std::stringstream fShaderStream;
            fShaderStream << fShaderFile.rdbuf();
            fragmentCode = fShaderStream.str();
            fShaderFile.close();
        }
        else
        {
            std::cerr << "Failed to open fragment shader file: " << fragmentPath << std::endl;
            return;
        }

        loadFromSource(vertexCode, fragmentCode);
    }

    void Shader::loadFromSource(const std::string &vertexData, const std::string &fragmentData)
    {
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexData);
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentData);

        m_Program = glCreateProgram();
        glAttachShader(m_Program, vertexShader);
        glAttachShader(m_Program, fragmentShader);
        linkProgram();

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    void Shader::use() const
    {
        glUseProgram(m_Program);
    }

    void Shader::unuse() const
    {
        glUseProgram(0);
    }

    GLuint Shader::getID() const
    {
        return m_Program;
    }

    void Shader::setUniformBool(const std::string &name, bool value) const
    {
        glUniform1i(getUniformLocation(name), (int)value);
    }
    
    void Shader::setUniformInt(const std::string &name, int value) const
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setUniformFloat(const std::string &name, float value) const
    {
        glUniform1f(getUniformLocation(name), value);
    }

    void Shader::setUniformVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2f(getUniformLocation(name), value.x, value.y);
    }

    void Shader::setUniformVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setUniformVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setUniformMat3(const std::string &name, const glm::mat3 &matrix) const
    {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setUniformMat4(const std::string &name, const glm::mat4 &matrix) const
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    GLint Shader::getUniformLocation(const std::string &name) const
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        {
            return m_UniformLocationCache[name];
        }
        GLint location = glGetUniformLocation(m_Program, name.c_str());
        if (location == -1)
        {
            Logger::logWarning("failed to find uniform: '" + name + "' in Shader::getUniformLocation method");
            return -1;
        }
        m_UniformLocationCache[name] = location;
        return location;
    }

    GLuint Shader::compileShader(unsigned int type, const std::string &source)
    {
        GLuint id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, nullptr, infoLog);

            Logger::logError("ERROR::SHADER::COMPILATION_FAILED\n" + (std::string)infoLog);
        }

        return id;
    }

    void Shader::linkProgram()
    {
        glLinkProgram(m_Program);

        int success;
        char infoLog[512];
        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);

            Logger::logError("ERROR::PROGRAM::LINKING_FAILED\n" + (std::string)infoLog);
        }
    }
} // namespace MykaEngine
