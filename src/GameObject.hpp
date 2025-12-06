#pragma once

#include "Renderer/Mesh.hpp"
#include "Renderer/Material.hpp"
#include "Transform.hpp"

// std
#include <memory>
#include <string>

namespace MykaEngine
{
    class GameObject
    {
    public:
        GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const std::string& name = "GameObject");

    private:
        std::string m_Name;
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Material> m_Material;
        Transform m_Transform;
    };
} // namespace MykaEngine
