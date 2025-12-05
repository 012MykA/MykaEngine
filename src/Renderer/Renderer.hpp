#pragma once
#include <glad/glad.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

namespace MykaEngine
{
    class Renderer
    {
    public:
        Renderer() = default;

        void clear() const;

        void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
    };
} // namespace MykaEngine
