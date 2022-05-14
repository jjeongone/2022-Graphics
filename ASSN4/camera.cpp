#include "camera.h"

Camera::Camera()
{
	eye = make_tuple(7.0, 9.0, 0.0); // need to edit as player position
	center = make_tuple(0.0, 9.0, 0.0);
	up = make_tuple(0.0, 1.0, 0.0);
	left = 1.5;
	right = 1.5;
	front = 1;
	back = 150;
	mode = THIRD;
}

Camera::Camera(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u)
{
	eye = e;
	center = c;
	up = u;
	mode = THIRD;
}

void Camera::look_at()
{
	GLint vertex_camera_location = glGetUniformLocation(shader_program, "Camera");
	GLint vertex_projection_location = glGetUniformLocation(shader_program, "Projection");

	glm::mat4 projection;
	glm::vec3 cameraPos = glm::vec3(get<0>(eye), get<1>(eye), get<2>(eye));
	glm::vec3 cameraFront = glm::vec3(get<0>(center), get<1>(center), get<2>(center));
	glm::vec3 cameraUp = glm::vec3(get<0>(up), get<1>(up), get<2>(up));
	glm::mat4 camera = glm::lookAt(cameraPos, cameraFront, cameraUp);

	if (mode == TOP)
		projection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, front, back);
	else
		projection = glm::frustum(-left, left, -right, right, front, back);

	glUniformMatrix4fv(vertex_projection_location, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(vertex_camera_location, 1, GL_FALSE, glm::value_ptr(camera));
}


void Camera::set_position(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u)
{
	eye = e;
	center = c;
	up = u;
}

glm::vec3 Camera::get_eye_first()
{
	return eye_first;
}

void Camera::set_eye_first(glm::vec3 new_eye)
{
	eye_first = new_eye;
}

glm::vec3 Camera::get_center_first()
{
	return center_first;
}

void Camera::set_center_first(glm::vec3 new_center)
{
	center_first = new_center;
}

glm::vec3 Camera::get_eye_third()
{
	return eye_third;
}

void Camera::set_eye_third(glm::vec3 new_eye)
{
	eye_third = new_eye;
}

glm::vec3 Camera::get_center_third()
{
	return center_third;
}

void Camera::set_center_third(glm::vec3 new_center)
{
	center_third = new_center;
}


void Camera::set_volume(float l, float r, float f, float b)
{
	left = l;
	right = r;
	front = f;
	back = b;
}

void Camera::set_transform(glm::mat4 new_transform_tank, glm::mat4 new_transform_barrel)
{
	transform_tank = new_transform_tank;
	transform_barrel = new_transform_barrel;

	eye_first = transform_barrel * glm::vec4(0, 5, 12, 1);
	center_first = transform_barrel * glm::vec4(0, 5, -1, 1);
	eye_third = transform_tank * glm::vec4(0, 14, 9, 1);
	center_third = transform_tank * glm::vec4(0, 12, 5, 1);

	switch (mode) {
	case FIRST:
		set_position(make_tuple(eye_first.x, eye_first.y, eye_first.z), make_tuple(center_first.x, center_first.y, center_first.z), make_tuple(0.0, 1.0, 0.0)); // need to edit as player position
		break;

	case TOP:
		set_position(make_tuple(0.0, 13.0, 0.0), make_tuple(0.0, 1.0, 0.0), make_tuple(0.0, 0.0, -1.0));
		break;

	case THIRD:
		set_position(make_tuple(eye_third.x, eye_third.y, eye_third.z), make_tuple(center_third.x, center_third.y, center_third.z), make_tuple(0.0, 1.0, 0.0)); // need to edit as player position
		break;
	}
}


void Camera::change_mode()
{
	switch (mode) {
	case THIRD:
		set_position(make_tuple(eye_first.x, eye_first.y, eye_first.z), make_tuple(center_first.x, center_first.y, center_first.z), make_tuple(0.0, 1.0, 0.0)); // need to edit as player position
		mode = FIRST;
		break;

	case FIRST:
		set_position(make_tuple(0.0, 13.0, 0.0), make_tuple(0.0, 1.0, 0.0), make_tuple(0.0, 0.0, -1.0));
		mode = TOP;
		break;

	case TOP: 
		set_position(make_tuple(eye_third.x, eye_third.y, eye_third.z), make_tuple(center_third.x, center_third.y, center_third.z), make_tuple(0.0, 1.0, 0.0)); // need to edit as player position
		mode = THIRD;
		break;
	}
}
