#pragma once

#include <glad/glad.h>

#include <vector>

namespace GLClasses
{
	class IndexBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		void BufferData(GLsizeiptr size, GLfloat* data);
		void BufferData(const std::vector<GLuint>& data);
		void Bind();
		void Unbind();

	private:
		GLuint ID;
	};
}