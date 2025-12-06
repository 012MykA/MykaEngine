cmake_minimum_required(VERSION 3.23)

project(MykaEngine)

# ИСПРАВЛЕНО
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_DIR "${CMAKE_SOURCE_DIR}/libs/glfw-3.4" CACHE PATH "Path to the GLFW installation.")

# glm
add_subdirectory(libs/glm)
include_directories(libs/glm)

add_subdirectory(libs/glfw-3.4) # glfw

# GLAD
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/libs/glad")
include_directories(SYSTEM "${GLAD_DIR}/include")

# stb_image
set(STB_IMAGE_DIR "${CMAKE_SOURCE_DIR}/libs/stb_image")
include_directories(SYSTEM "${STB_IMAGE_DIR}")

add_executable(MykaEngine
    "${GLAD_DIR}/src/glad.c"
    "${STB_IMAGE_DIR}/stb_image.c"
    "src/main.cpp"

    "src/Renderer/IndexBuffer.cpp"
    "src/Renderer/VertexArray.cpp"
    "src/Renderer/VertexBuffer.cpp"
    "src/Renderer/Mesh.cpp"
    
    "src/Renderer/Shader.cpp"
    "src/Renderer/Texture.cpp"
    "src/Renderer/Material.cpp"
    "src/Renderer/Renderer.cpp"

    "src/Transform.cpp"
    "src/GameObject.cpp"

    "src/myka_window.cpp"
    "src/Camera.cpp"
    "src/Timer.cpp"
    )

target_link_libraries(MykaEngine PRIVATE
    glfw
)