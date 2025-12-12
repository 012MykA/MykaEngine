#pragma once

#include <glad/glad.h>

#include "myka_mesh.hpp"
#include "myka_material.hpp"
#include "myka_game_object.hpp"
#include "myka_camera.hpp"
#include "myka_scene.hpp"

namespace MykaEngine
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void clear() const;
        
        void drawScene(const Scene& scene, const Camera camera) const;

    public:
        void drawObject(const GameObject& object, const Camera& camera, const Light &light, bool isLight) const;
    };
} // namespace MykaEngine
