#pragma once
#include <tuple>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

extern glm::mat4 model_view_matrix;
extern unsigned int shader_program;

enum view_mode {
	THIRD = 0,
	FIRST = 1,
	TOP = 2,
};

using namespace std;
class Camera {
private:
	float left, right, front, back;
	tuple<float, float, float> eye;
	tuple<float, float, float> center;
	tuple<float, float, float> up;

	glm::vec3 eye_first;
	glm::vec3 center_first;

	glm::vec3 eye_third;
	glm::vec3 center_third;

	glm::mat4 transform_tank;
	glm::mat4 transform_barrel;
	
	view_mode mode;

public:
	Camera();
	Camera(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u);
	void look_at();
	void set_position(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u);
	glm::vec3 get_eye_first();
	void set_eye_first(glm::vec3 new_eye);
	glm::vec3 get_center_first();
	void set_center_first(glm::vec3 new_center);
	glm::vec3 get_eye_third();
	void set_eye_third(glm::vec3 new_eye);
	glm::vec3 get_center_third();
	void set_center_third(glm::vec3 new_center);
	void set_volume(float l, float r, float f, float b);
	void set_transform(glm::mat4 new_transform_tank, glm::mat4 new_transform_barrel);
	void change_mode();
};