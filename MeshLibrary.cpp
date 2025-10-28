#include "MeshLibrary.h"

std::unordered_map<std::string, std::shared_ptr<Mesh>> MeshLibrary::m_Meshes;

static std::shared_ptr<Mesh> CreateCubeMesh()
{
	std::vector<Vertex> vertices = {
		Vertex{glm::vec3(-0.5, -0.5f, 0.5), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5, 0.5f, 0.5), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5, 0.5f, 0.5), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5, -0.5f, 0.5), glm::vec3(1.0f, 1.0f, 0.0f)},

		Vertex{glm::vec3(-0.5, -0.5f, -0.5), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5, 0.5f, -0.5), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5, 0.5f, -0.5), glm::vec3(1.0f, 1.0f, 0.0f)},
		Vertex{glm::vec3(0.5, -0.5f, -0.5), glm::vec3(1.0f, 1.0f, 0.0f)}
	};

	std::vector<GLuint> indices = {
		0, 1, 2, 0, 2, 3,
		3, 2, 6, 3, 6, 7,
		7, 6, 5, 7, 5, 4,
		4, 5, 1, 4, 1, 0,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices);
	mesh->SetName("Cube");
	return mesh;
}

static std::shared_ptr<Mesh> CreateRedCubeMesh()
{
	std::vector<Vertex> vertices = {
		Vertex{glm::vec3(-0.5, -0.5f, 0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5, 0.5f, 0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5, 0.5f, 0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5, -0.5f, 0.5), glm::vec3(1.0f, 0.0f, 0.0f)},

		Vertex{glm::vec3(-0.5, -0.5f, -0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5, 0.5f, -0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5, 0.5f, -0.5), glm::vec3(1.0f, 0.0f, 0.0f)},
		Vertex{glm::vec3(0.5, -0.5f, -0.5), glm::vec3(1.0f, 0.0f, 0.0f)}
	};

	std::vector<GLuint> indices = {
		0, 1, 2, 0, 2, 3,
		3, 2, 6, 3, 6, 7,
		7, 6, 5, 7, 5, 4,
		4, 5, 1, 4, 1, 0,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(vertices, indices);
	mesh->SetName("Red Cube");
	return mesh;
}

void MeshLibrary::Initialize()
{
	m_Meshes["Cube"] = CreateCubeMesh();

	m_Meshes["Red Cube"] = CreateRedCubeMesh();
}

std::shared_ptr<Mesh> MeshLibrary::GetMesh(const std::string& name) { return m_Meshes[name]; }

std::shared_ptr<Mesh> MeshLibrary::AddMesh(const std::string& name, std::shared_ptr<Mesh> mesh)
{
	mesh->SetName(name);
	m_Meshes[name] = std::move(mesh);
	return m_Meshes[name];
}

std::unordered_map<std::string, std::shared_ptr<Mesh>> MeshLibrary::GetAllMeshes() { return m_Meshes; }

std::unordered_map<std::string, std::shared_ptr<Mesh>>& MeshLibrary::GetAllMeshesRef() { return m_Meshes; }
