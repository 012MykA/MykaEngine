#pragma once
#include <glad/glad.h>

#include "Mesh.hpp"
#include "Material.hpp"

namespace MykaEngine
{
    class Renderer
    {
    public:
        Renderer() = default;

        void clear() const;

        void draw(const Mesh& mesh, const Material& material) const;
    };
} // namespace MykaEngine
