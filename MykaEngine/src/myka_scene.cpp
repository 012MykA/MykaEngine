#include "myka_scene.hpp"

namespace MykaEngine
{
    void Scene::addGameObject(std::shared_ptr<GameObject> object)
    {
        m_GameObjects.push_back(object);
    }

    void Scene::addLight(std::shared_ptr<Light> light)
    {
        m_Lights.push_back(light);
    }

    void Scene::clear()
    {
        m_GameObjects.clear();
        m_Lights.clear();
    }

    const std::vector<std::shared_ptr<GameObject>> &Scene::getGameObjects() const
    {
        return m_GameObjects;
    }

    const std::vector<std::shared_ptr<Light>> &Scene::getLights() const
    {
        return m_Lights;
    }
} // namespace MykaEngine
