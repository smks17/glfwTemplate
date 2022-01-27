cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(glfwTest)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp shader.h shader.cpp)


target_include_directories(${PROJECT_NAME}
    PUBLIC
        external
        ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${OPENGL_gl_LIBRARY}
        glfw
        glad
)

#include_directories(stb_image)
add_subdirectory(ThirdParty)
