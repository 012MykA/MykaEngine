#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <vector>

namespace GLClasses
{
	using namespace std;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texUV;
	};

	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void BufferData(GLsizeiptr size, GLfloat* vertices);
		void BufferData(std::vector<Vertex> vertices);
		void Bind();
		void Unbind();
		void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

	private:
		GLuint ID;
	};
}