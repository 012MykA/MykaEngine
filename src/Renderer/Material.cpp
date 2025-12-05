#include "Material.hpp"

namespace MykaEngine
{
    Material::Material(std::shared_ptr<Shader> shader) : m_Shader(shader) {}

    void Material::SetColor(const glm::vec4 &color)
    {
        m_Color = color;
    }
} // namespace MykaEngine
