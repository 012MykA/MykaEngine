#include "GameObject.hpp"

namespace MykaEngine
{
    GameObject::GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const std::string &name)
        : m_Mesh(mesh), m_Material(material), m_Name(name) {}

    std::shared_ptr<Mesh> GameObject::getMesh() const
    {
        return m_Mesh;
    }

    std::shared_ptr<Material> GameObject::getMaterial() const
    {
        return m_Material;
    }

    Transform &GameObject::getTransform()
    {
        return m_Transform;
    }

    const Transform &GameObject::getTransform() const
    {
        return m_Transform;
    }

    const std::string &GameObject::getName() const
    {
        return m_Name;
    }
} // namespace MykaEngine
