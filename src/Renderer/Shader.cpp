#include "Shader.hpp"

namespace MykaEngine
{
    Shader::Shader(const std::string &vertex, const std::string &fragment, bool usePath)
    {
        if (usePath)
        {
            this->m_VertexData = getFileContent(vertex);
            this->m_FragmentData = getFileContent(fragment);
        }
        else
        {
            this->m_VertexData = vertex;
            this->m_FragmentData = fragment;
        }
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

    void Shader::setUniform3f(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
    }

    void Shader::setUniform1i(const std::string &name, float value) const
    {
        glUniform1i(getUniformLocation(name), value);
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

    GLuint Shader::getUniformLocation(const std::string &name) const
    {
        return glGetUniformLocation(m_Program, name.c_str());
    }

    std::string Shader::getFileContent(const std::string &path)
    {
        std::string fileContent;
        std::ifstream fileStream;

        // Включаем возможность выбрасывать исключения для объектов потоков файлов
        fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // Открытие файла
            fileStream.open(path);
            std::stringstream fileStringStream;

            // Чтение содержимого файлового буфера в поток
            fileStringStream << fileStream.rdbuf();

            // Закрытие файлового обработчика
            fileStream.close();

            // Преобразование потока в строку и возврат
            fileContent = fileStringStream.str();
        }
        catch (std::ifstream::failure &e)
        {
            // Вывод ошибки и завершение работы, если не удалось прочитать файл
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ (" << path << "): " << e.what() << std::endl;
            // Можно выбросить исключение или вернуть пустую строку, в данном случае возвращаем пустую строку.
            return "";
        }
        return fileContent;
    }
} // namespace MykaEngine
