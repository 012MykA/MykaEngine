#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

using namespace GLClasses;

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture);
	Mesh(const std::vector<Vertex>& vertices, const Texture& texture);

	void Draw(Shader& shader, const glm::mat4& model, const glm::mat4& viewProjection);

private:
	Texture texture;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
};