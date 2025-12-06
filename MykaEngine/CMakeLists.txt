set(ENGINE_HEADERS
    "include/Camera.hpp"
    "include/GameObject.hpp"
    "include/IndexBuffer.hpp"
    "include/Material.hpp"
    "include/Mesh.hpp"
    "include/myka_window.hpp"
    "include/Renderer.hpp"
    "include/Shader.hpp"
    "include/Texture.hpp"
    "include/Timer.hpp"
    "include/Transform.hpp"
    "include/VertexArray.hpp"
    "include/VertexBuffer.hpp"
)

set(ENGINE_SOURCES
    "src/Camera.cpp"
    "src/GameObject.cpp"
    "src/IndexBuffer.cpp"
    "src/Material.cpp"
    "src/Mesh.cpp"
    "src/myka_window.cpp"
    "src/Renderer.cpp"
    "src/Shader.cpp"
    "src/Texture.cpp"
    "src/Timer.cpp"
    "src/Transform.cpp"
    "src/VertexArray.cpp"
    "src/VertexBuffer.cpp"
)

add_library(MykaEngine STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_HEADERS}
)

target_include_directories(MykaEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(MykaEngine PRIVATE
    glfw
)
