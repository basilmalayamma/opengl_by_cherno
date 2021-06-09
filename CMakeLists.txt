cmake_minimum_required(VERSION 3.2)

project(opengl_by_cherno)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(opengl_by_cherno
    src/Source.cpp    
)

target_link_libraries(opengl_by_cherno
    ${CMAKE_SOURCE_DIR}/libs/libGLEW.so
    GL
    glfw
)

install(TARGETS opengl_by_cherno DESTINATION ${CMAKE_SOURCE_DIR}/bin)
