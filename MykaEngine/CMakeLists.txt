set(ENGINE_HEADERS
    "include/myka_camera.hpp"
    "include/myka_game_object.hpp"
    "include/myka_index_buffer.hpp"
    "include/myka_material.hpp"
    "include/myka_mesh.hpp"
    "include/myka_window.hpp"
    "include/myka_renderer.hpp"
    "include/myka_shader.hpp"
    "include/myka_texture.hpp"
    "include/myka_timer.hpp"
    "include/myka_transform.hpp"
    "include/myka_vertex_array.hpp"
    "include/myka_vertex_buffer.hpp"
)

set(ENGINE_SOURCES
    "src/myka_camera.cpp"
    "src/myka_game_object.cpp"
    "src/myka_index_buffer.cpp"
    "src/myka_material.cpp"
    "src/myka_mesh.cpp"
    "src/myka_window.cpp"
    "src/myka_renderer.cpp"
    "src/myka_shader.cpp"
    "src/myka_texture.cpp"
    "src/myka_timer.cpp"
    "src/myka_transform.cpp"
    "src/myka_vertex_array.cpp"
    "src/myka_vertex_buffer.cpp"
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
