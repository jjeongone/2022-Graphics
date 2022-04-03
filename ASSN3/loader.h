#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class Loader{
private:
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	std::vector < glm::vec3 > vertices;
	std::vector < glm::vec2 > uvs;
	std::vector < glm::vec3 > normals;
public:
	Loader(const char * path);
	std::vector < glm::vec3 > get_vertex();
	std::vector < glm::vec2 > get_uv();
	std::vector < glm::vec3 > get_normal();
};