//#pragma once
//
//#include "Mesh.h"
//
//class ResourceManager
//{
//public:
//	ResourceManager();
//
//	const Mesh& GetCubeMesh();
//
//private:
//	std::vector<Vertex> cubeVertices = {
//		Vertex{glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
//		Vertex{glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
//		Vertex{glm::vec3(0.5f / 2.0f, 0.0f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)}
//	};
//	std::vector<GLuint> cubeIndices = {0, 1, 2};
//	Texture brick = Texture("C:/Users/Vova/source/repos/MykaEngine 2.0/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
//
//	Mesh cubeMesh = Mesh(cubeVertices, cubeIndices, brick);
//};
//
