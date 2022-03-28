cmake_minimum_required(VERSION 3.10)

project(assn2)
add_executable(assn2 main.cpp shape.cpp tank.cpp bullet.cpp game.cpp)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


add_dependencies(assn2 OpenGL::OpenGL)
include_directories(${glm_INCLUDE_DIRS} )

target_link_libraries(assn2 OpenGL::OpenGL GLUT::GLUT GLEW::GLEW ${glm_LIBRARY} )