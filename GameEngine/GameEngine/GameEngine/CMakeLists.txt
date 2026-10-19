cmake_minimum_required(VERSION 3.20)
project(GameEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    main.cpp
    Camera/*.cpp
    Graphics/*.cpp
    Shaders/*.cpp
    "Model Loading/*.cpp"
    imgui/*.cpp)

add_executable(GameEngine ${SOURCES})

set(DEPS ${CMAKE_SOURCE_DIR}/../Dependencies)

target_include_directories(GameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}
    include
    imgui
    ${DEPS}/GLEW/include
    ${DEPS}/GLEW/include/GL     # por si glew.h está dentro de GL/
    ${DEPS}/GLFW/include
    ${DEPS}/glm)                # contiene glm.hpp

target_link_directories(GameEngine PRIVATE
    lib
    ${DEPS}/GLEW/libs
    ${DEPS}/GLFW/lib-vc2015)

target_compile_definitions(GameEngine PRIVATE GLEW_STATIC)

target_link_libraries(GameEngine PRIVATE
    glew32s
    glfw3
    glut32
    opengl32
    winmm)

add_custom_command(TARGET GameEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/glut32.dll
        $<TARGET_FILE_DIR:GameEngine>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Shaders $<TARGET_FILE_DIR:GameEngine>/Shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:GameEngine>/Resources)