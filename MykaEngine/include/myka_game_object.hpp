#pragma once

#include "myka_mesh.hpp"
#include "myka_material.hpp"
#include "myka_transform.hpp"

// std
#include <memory>
#include <string>

namespace MykaEngine
{
    class GameObject
    {
    public:
        GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const std::string &name = "GameObject");

    public:
        std::shared_ptr<Mesh> getMesh() const;
        std::shared_ptr<Material> getMaterial() const;
        Transform &getTransform();
        const Transform &getTransform() const;
        const std::string &getName() const;

    private:
        std::string m_Name;
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Material> m_Material;
        Transform m_Transform;
    };
} // namespace MykaEngine
