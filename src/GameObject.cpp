#include "GameObject.hpp"

MykaEngine::GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const std::string &name)
    : m_Mesh(mesh), m_Material(material), m_Name(name) {}
