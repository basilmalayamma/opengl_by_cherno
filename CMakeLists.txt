cmake_minimum_required(VERSION 3.2)

project(opengl_by_cherno)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/test
    ${CMAKE_SOURCE_DIR}/res/imgui
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
    res/imgui/imgui.cpp
    res/imgui/imgui_demo.cpp
    res/imgui/imgui_draw.cpp
    res/imgui/imgui_impl_glfw_gl3.cpp
)

target_link_libraries(opengl_by_cherno
    ${CMAKE_SOURCE_DIR}/libs/libGLEW.so
    GL
    glfw
)

install(TARGETS opengl_by_cherno DESTINATION ${CMAKE_SOURCE_DIR}/bin)
