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
    struct MykaDefaultShaderData
    {
        inline static const std::string vertexData =
            "#version 460 core\n"
            "layout(location = 0) in vec3 aPos;\n"
            "layout(location = 1) in vec2 texCoord;\n"
            "out vec2 v_TexCoord;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(aPos, 1.0);\n"
            "v_TexCoord = texCoord;\n"
            "}\n";

        inline static const std::string fragmentData =
            "#version 460 core\n"
            "out vec4 FragColor;\n"
            "in vec2 v_TexCoord;\n"
            "uniform sampler2D u_Texture;\n"
            "uniform vec3 u_Color;\n"
            "void main()\n"
            "{\n"
                "FragColor = texture(u_Texture, v_TexCoord);\n"
            "}\n";
    };

    class Shader
    {
    public:
        Shader(const std::string &vertex, const std::string &fragment, bool usePath);
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
