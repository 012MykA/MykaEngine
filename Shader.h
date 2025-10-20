#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace GLClasses
{
	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);

		~Shader();

		void CompileShaders();
		void Use();

		GLuint getProgramID() const;

		void SetVector3f(const GLchar* name, const glm::vec3& value);
		void SetVector4f(const GLchar* name, const glm::vec4& value);
		void SetMatrix4(const GLchar* name, const glm::mat4& matrix);
		void SetInteger(const GLchar* name, GLuint value);

	private:
		GLuint m_Program;

		std::string m_VertexPath;
		std::string m_FragmentPath;
		std::string m_VertexData;
		std::string m_FragmentData;

		GLuint GetUniformLocation(const std::string name) const;
		std::string getFileContent(const std::string path);
	};
}