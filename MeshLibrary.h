#pragma once

#include "Mesh.h"

#include <unordered_map>

class MeshLibrary
{
public:
	static void Initialize();

	static std::shared_ptr<Mesh> GetMesh(const std::string& name);

	static std::shared_ptr<Mesh> AddMesh(const std::string& name, std::shared_ptr<Mesh> mesh);

	static std::unordered_map<std::string, std::shared_ptr<Mesh>> GetAllMeshes();

	static std::unordered_map<std::string, std::shared_ptr<Mesh>>& GetAllMeshesRef();

private:
	static std::unordered_map<std::string, std::shared_ptr<Mesh>> m_Meshes;
};