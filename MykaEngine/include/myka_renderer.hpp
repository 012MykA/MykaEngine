#pragma once

#include <glad/glad.h>

#include "myka_mesh.hpp"
#include "myka_material.hpp"
#include "myka_game_object.hpp"
#include "myka_camera.hpp"

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
