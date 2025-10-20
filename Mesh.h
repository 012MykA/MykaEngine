#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"

using namespace GLClasses;

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
	Mesh(const std::vector<Vertex>& vertices);

	void Draw(Shader& shader, const glm::mat4& model, const glm::mat4& viewProjection);

	friend class ImGuiManager;

public:
	void SetVertices(const std::vector<Vertex>& vertices);
	void SetIndices(const std::vector<GLuint>& indices);
	void SetDrawMode(GLenum mode);

	std::vector<Vertex> GetVertices() const;
	std::vector<GLuint> GetIndices() const;

private:
	GLenum drawMode = GL_TRIANGLES;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	VertexArray VAO;
	VertexBuffer VBO;
	IndexBuffer IBO;
};