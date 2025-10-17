#include "VertexArray.h"

GLClasses::VertexArray::VertexArray() : ID(0)
{
	glGenVertexArrays(1, &ID);
}

GLClasses::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &ID);
	this->Unbind();
}

void GLClasses::VertexArray::Bind()
{
	glBindVertexArray(ID);
}

void GLClasses::VertexArray::Unbind()
{
	glBindVertexArray(0);
}