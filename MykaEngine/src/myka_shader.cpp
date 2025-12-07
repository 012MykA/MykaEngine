#include "myka_shader.hpp"

namespace MykaEngine
{
    Shader::Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
    {
        this->m_VertexData = getFileContent(vertexPath);
        this->m_FragmentData = getFileContent(fragmentPath);
        compileShaders();
    }

    Shader::~Shader()
    {
        glUseProgram(0);
    }

    void Shader::use() const
    {
        glUseProgram(m_Program);
    }

    void Shader::setUniform3f(const std::string &name, const glm::vec3 &value)
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setUniform4f(const std::string &name, const glm::vec4 &value)
    {
        glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void Shader::setUniform1i(const std::string &name, int value)
    {
        glUniform1i(getUniformLocation(name), value);
    }

    void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::compileShaders()
    {
        GLuint vs;
        GLuint fs;
        GLint successful;
        GLchar GLInfoLog[512];

        vs = glCreateShader(GL_VERTEX_SHADER);
        fs = glCreateShader(GL_FRAGMENT_SHADER);

        const char *vs_char = m_VertexData.c_str();
        const char *fs_char = m_FragmentData.c_str();

        glShaderSource(vs, 1, &vs_char, 0);
        glShaderSource(fs, 1, &fs_char, 0);

        glCompileShader(vs);

        glGetShaderiv(vs, GL_COMPILE_STATUS, &successful);

        if (!successful)
        {
            glGetShaderInfoLog(vs, 512, NULL, GLInfoLog);
            std::cerr << "\nCOMPILATION ERROR IN VERTEX SHADER\n"
                      << GLInfoLog << std::endl;
        }

        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &successful);

        if (!successful)
        {
            glGetShaderInfoLog(fs, 512, NULL, GLInfoLog);
            std::cerr << "\nCOMPILATION ERROR IN FRAGMENT SHADER\n"
                      << GLInfoLog << std::endl;
        }

        m_Program = glCreateProgram();
        glAttachShader(m_Program, vs);
        glAttachShader(m_Program, fs);
        glLinkProgram(m_Program);

        glGetProgramiv(m_Program, GL_LINK_STATUS, &successful);

        if (!successful)
        {
            glGetProgramInfoLog(m_Program, 512, NULL, GLInfoLog);
            std::cerr << "ERROR: SHADER LINKING FAILED: \n"
                      << GLInfoLog << std::endl;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    GLint Shader::getUniformLocation(const std::string &name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        {
            return m_UniformLocationCache[name];
        }
        GLint location = glGetUniformLocation(m_Program, name.c_str());
        if (location == -1)
        {
            std::cerr << "failed to find uniform: '" << name << "'" << std::endl;
            return -1;
        }
        m_UniformLocationCache[name] = location;
        return location;
    }

    std::string Shader::getFileContent(const std::filesystem::path &path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            std::cerr << "failed to open file: " << path << std::endl;
            return "";
        }
        std::stringstream buffer;
        buffer << file.rdbuf();

        file.close();

        return buffer.str();
    }
} // namespace MykaEngine
