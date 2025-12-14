cmake_minimum_required(VERSION 3.23)
project(MykaEngine_Project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Vendor
add_subdirectory(Vendor/glm)
add_subdirectory(Vendor/glfw-3.4)
include_directories(Vendor/glm)
include_directories(SYSTEM Vendor/glad/include)
include_directories(SYSTEM Vendor/stb_image)

set(EXTERNAL_SRC
    Vendor/glad/src/glad.c
    Vendor/stb_image/stb_image.c
)

add_subdirectory(MykaEngine)

add_executable(MykaGame
    Game/src/main.cpp
    ${EXTERNAL_SRC}
)

target_link_libraries(MykaGame PRIVATE
    MykaEngine
    glfw
)