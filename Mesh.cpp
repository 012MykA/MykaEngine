#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const Texture& texture) : vertices(vertices), indices(indices), texture(texture)
{
	VAO.Bind();

	VBO.BufferData(vertices);

	IBO.Bind();
	IBO.BufferData(indices);

	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VBO.VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	IBO.Unbind();
	VBO.Unbind();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const Texture& texture) : vertices(vertices), texture(texture)
{
	VAO.Bind();

	VBO.BufferData(vertices);

	VBO.VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VBO.VertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VBO.VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
}

void Mesh::Draw(Shader& shader, const glm::mat4& model, const glm::mat4& viewProjection)
{
	shader.CompileShaders();
	shader.Use();

	// Set model matrix (keep if shader uses it)
	shader.SetMatrix4("model", model);

	// IMPORTANT: correct order is viewProjection * model
	// and uniform name must match shader (modelViewProj)
	glm::mat4 modelViewProj = viewProjection * model;
	shader.SetMatrix4("modelViewProj", modelViewProj);

	shader.SetInteger("tex0", 0);

	texture.Bind();

	VAO.Bind();

	if (indices.size() == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}

	VAO.Unbind();
}