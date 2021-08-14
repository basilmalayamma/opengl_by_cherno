cmake_minimum_required(VERSION 3.2)

project(opengl_by_cherno)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
)

add_executable(opengl_by_cherno
    test/application.cpp
    src/vertexBuffer.cpp
    src/GLDebug.cpp
    src/vertexArray.cpp
    src/indexBuffer.cpp
    src/shader.cpp
    src/renderer.cpp
    src/texture.cpp
)

target_link_libraries(opengl_by_cherno
    ${CMAKE_SOURCE_DIR}/libs/libGLEW.so
    GL
    glfw
)

install(TARGETS opengl_by_cherno DESTINATION ${CMAKE_SOURCE_DIR}/bin)
