#pragma once
#include <glad/glad.h>

#include "Mesh.hpp"
#include "Material.hpp"
#include "GameObject.hpp"
#include "Camera.hpp"

namespace MykaEngine
{
    class Renderer
    {
    public:
        Renderer() = default;

        void clear() const;

        void draw(const GameObject& object, const Camera& camera) const;
    };
} // namespace MykaEngine
