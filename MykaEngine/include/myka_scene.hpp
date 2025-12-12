#pragma once

#include "myka_game_object.hpp"
#include "myka_light.hpp"

// std
#include <vector>
#include <memory>

namespace MykaEngine
{
    class Scene
    {
    public:
        Scene() = default;
        ~Scene() = default;
        
        void addGameObject(std::shared_ptr<GameObject> object);
        void addLight(std::shared_ptr<Light> light);

        void clear();
    
    public:
        const std::vector<std::shared_ptr<GameObject>>& getGameObjects() const;
        const std::vector<std::shared_ptr<Light>>& getLights() const;

    private:
        std::vector<std::shared_ptr<GameObject>> m_GameObjects;
        std::vector<std::shared_ptr<Light>> m_Lights;
    };
} // namespace MykaEngine
