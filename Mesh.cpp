#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) : vertices(vertices), indices(indices)
{
	VAO.Bind();

	VBO.BufferData(vertices);

	IBO.Bind();
	IBO.BufferData(indices);

	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	VAO.Unbind();
	IBO.Unbind();
	VBO.Unbind();
}

Mesh::Mesh(const std::vector<Vertex>& vertices) : vertices(vertices)
{
	VAO.Bind();

	VBO.BufferData(vertices);

	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
}

void Mesh::Draw(Shader& shader, const glm::mat4& model, const glm::mat4& viewProjection)
{
	shader.SetMatrix4("model", model);

	glm::mat4 modelViewProj = viewProjection * model;
	shader.SetMatrix4("modelViewProj", modelViewProj);

	VAO.Bind();

	if (indices.size() == 0)
	{
		glDrawArrays(drawMode, 0, vertices.size());
	}
	else
	{
		glDrawElements(drawMode, indices.size(), GL_UNSIGNED_INT, 0);
	}

	VAO.Unbind();
}

void Mesh::SetGlobalColor(const glm::vec3& color)
{
	for (auto& vertex : vertices)
	{
		vertex.color = color;
	}
	VBO.Bind();
	VBO.BufferData(vertices);
	VBO.Unbind();
}

void Mesh::SetVertices(const std::vector<Vertex>& vertices) { this->vertices = vertices; }

void Mesh::SetIndices(const std::vector<GLuint>& indices) { this->indices = indices; }

void Mesh::SetDrawMode(GLenum mode) { this->drawMode = mode; }

std::vector<Vertex> Mesh::GetVertices() const { return vertices; }

std::vector<GLuint> Mesh::GetIndices() const { return indices; }
