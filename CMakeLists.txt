cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "")

project(glfwTest)

find_package(OpenGL REQUIRED)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.cpp)

# copy all resources to build folder (optional)
# 
# file(GLOB RESOURCES resources/* )
# foreach(RESOURCE IN LISTS RESOURCES)
#     configure_file(
#         ${RESOURCE}
#         "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY
#       )
# endForeach()
# message("-- Resources is copied!")


# copy .conf file to build folder (optional)
#
# configure_file(
#         ./glfw.conf
#         "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY
#         )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

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

add_subdirectory(ThirdParty)