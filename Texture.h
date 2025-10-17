#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Shader.h"

namespace GLClasses
{
	class Texture
	{
	public:
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
		~Texture();

		void Bind();

		void Unbind();

	private:
		GLuint ID;
		GLenum type;
	};
}