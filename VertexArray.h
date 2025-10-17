#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>

namespace GLClasses
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

	private:
		GLuint ID;
	};
}