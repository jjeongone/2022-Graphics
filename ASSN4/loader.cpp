#include "loader.h"

vector<int> split(string s, char d) {
	istringstream iss(s);
	vector<int> result;
	string buffer;

	while (getline(iss, buffer, d)) {
		if (!buffer.empty()) {
			result.push_back(stoi(buffer));
		}	
	}
	return result;
}

Loader::Loader(const char * path)
{
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;
	ifstream file(path);
	if (file.is_open()) {
		string line_header;
		temp_vertices.clear();
		temp_uvs.clear();
		temp_normals.clear();
		vertexIndices.clear();
		uvIndices.clear();
		normalIndices.clear();

		while (!file.eof()) {
			file >> line_header;
			if (line_header.compare("v") == 0) {
				glm::vec3 vertex;
				file >> vertex.x >> vertex.y >> vertex.z;
				temp_vertices.push_back(vertex);
			}
			else if (line_header.compare("vt") == 0) {
				glm::vec2 uv;
				file >> uv.x >> uv.y;
				temp_uvs.push_back(uv);
			}
			else if (line_header.compare("vn") == 0) {
				glm::vec3 normal;
				file >> normal.x >> normal.y >> normal.z;
				temp_normals.push_back(normal);
			}
			else if (line_header.compare("f") == 0) {
				for (int i = 0; i < 3; i++) {
					string temp;
					vector<int> parsing;
					file >> temp;
					parsing = split(temp, '/');
					if (parsing.size() == 3) {
						vertexIndices.push_back(parsing[0]);
						uvIndices.push_back(parsing[1]);
						normalIndices.push_back(parsing[2]);
					}
				}
			}
		}
		file.close();
	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertex_index = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertex_index - 1];
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uv_index = uvIndices[i];
		glm::vec2 uv = temp_uvs[uv_index - 1];
		uvs.push_back(uv);
	}
	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normal_index = normalIndices[i];
		glm::vec3 normal = temp_normals[normal_index - 1];
		normals.push_back(normal);
	}
}

std::vector<glm::vec3> Loader::get_vertex()
{
	return vertices;
}

std::vector<glm::vec2> Loader::get_uv()
{
	return uvs;
}

std::vector<glm::vec3> Loader::get_normal()
{
	return normals;
}

std::vector<float> Loader::merge()
{
	vector<float> result;
	for (int i = 0; i < vertices.size(); i++) {
		result.push_back(vertices[i].x);
		result.push_back(vertices[i].y);
		result.push_back(vertices[i].z);

		result.push_back(normals[i].x);
		result.push_back(normals[i].y);
		result.push_back(normals[i].z);

		result.push_back(uvs[i].x);
		result.push_back(uvs[i].y);
	}
	return result;
}
