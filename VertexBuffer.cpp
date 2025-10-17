#include "VertexBuffer.h"

GLClasses::VertexBuffer::VertexBuffer() : ID(0)
{
	glGenBuffers(1, &ID);
	this->Bind();
}

GLClasses::VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &ID);
	this->Unbind();
}

void GLClasses::VertexBuffer::BufferData(GLsizeiptr size, GLfloat* vertices)
{
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void GLClasses::VertexBuffer::BufferData(std::vector<Vertex> vertices)
{
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

void GLClasses::VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GLClasses::VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLClasses::VertexBuffer::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	this->Bind();

	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);

	this->Unbind();
}
