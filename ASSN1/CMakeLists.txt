cmake_minimum_required(VERSION 3.10)

project(assn1)
add_executable(assn1 main.cpp shape.cpp tank.cpp bullet.cpp)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)


add_dependencies(assn1 OpenGL::OpenGL)
include_directories(${glm_INCLUDE_DIRS} )

target_link_libraries(assn1 OpenGL::OpenGL GLUT::GLUT GLEW::GLEW ${glm_LIBRARY} )