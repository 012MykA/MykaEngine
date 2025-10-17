#include "IndexBuffer.h"

GLClasses::IndexBuffer::IndexBuffer() : ID(0)
{
	glGenBuffers(1, &ID);
	this->Bind();
}

GLClasses::IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ID);
	this->Unbind();
}

void GLClasses::IndexBuffer::BufferData(GLsizeiptr size, GLfloat* data)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void GLClasses::IndexBuffer::BufferData(const std::vector<GLuint>& data)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), data.data(), GL_STATIC_DRAW);
}

void GLClasses::IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GLClasses::IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}