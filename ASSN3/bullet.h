#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <vector>
#include <utility>
#include <tuple>

#include "tank.h"

#define GRAVITY 0.02


class Bullet {
private:
	float x, y, z;
	float y_speed = -GRAVITY;

	tuple<float, float, float> tank_coordinate, tank_translation;
	tuple<float, float, float, float> tank_rotation;
	float head_angle, barrel_angle;
	float speed = 1;
	float bullet_position = -16;
	Loader* bullet = new Loader("./model/bullet.obj");
	std::vector < glm::vec3 > bullet_vertices = bullet->get_vertex();
public:
	Bullet();
	Bullet(tuple<float, float, float>, tuple<float, float, float>, tuple<float, float, float, float>, float, float, float);
	std::tuple<float,float, float> position();
	glm::mat4 cal_transformation();
	void draw_bullet(bool fill);
	void move();
	void changeSpeed();
	bool isExplode(Tank* player, pair<glm::vec3, glm::vec3>, Tank* enemy, pair<glm::vec3, glm::vec3>);
};

#endif
