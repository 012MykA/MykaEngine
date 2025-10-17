//#include "ResourceManager.h"
//
//ResourceManager::ResourceManager()
//{
//
//    cubeVertices = {
//        // front
//        Vertex{glm::vec3(-0.5f, -0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 0.0f)},
//        Vertex{glm::vec3(0.5f, -0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 0.0f)},
//        Vertex{glm::vec3(0.5f,  0.5f,  0.5f),   glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(1.0f, 1.0f)},
//        Vertex{glm::vec3(-0.5f,  0.5f,  0.5f),  glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec2(0.0f, 1.0f)},
//
//        // back
//        Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 0.0f)},
//        Vertex{glm::vec3(0.5f, -0.5f, -0.5f),   glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 0.0f)},
//        Vertex{glm::vec3(0.5f,  0.5f, -0.5f),   glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(0.0f, 1.0f)},
//        Vertex{glm::vec3(-0.5f,  0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec2(1.0f, 1.0f)}
//    };
//
//    cubeIndices = {
//        0, 1, 2, 2, 3, 0,       // front
//        4, 5, 6, 6, 7, 4,       // back
//        1, 5, 6, 6, 2, 1,       // right
//        0, 4, 7, 7, 3, 0,       // left
//        3, 2, 6, 6, 7, 3,       // top
//        0, 1, 5, 5, 4, 0        // bottom
//    };
//
//	cubeMesh = Mesh(cubeVertices, cubeIndices, brick);
//}
//
//const Mesh& ResourceManager::GetCubeMesh()
//{
//	return cubeMesh;
//}
//
