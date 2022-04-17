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
	float radius = 1.8f;
	float x_speed = 6 * std::cos(30. * 3.142 / 180);
	float y_speed = -GRAVITY;
	float z_speed = 6 * std::cos(30. * 3.142 / 180);
	tuple<float, float, float> tank_coordinate, tank_translation;
	tuple<float, float, float, float> tank_rotation;
	float head_angle, barrel_angle;
	float speed = 1;
	float bullet_position = -16;
	Loader* bullet = new Loader("./model/bullet.obj");
	std::vector < glm::vec3 > bullet_vertices = bullet->get_vertex();
public:
	Bullet();
	Bullet(float init_x, float init_y, float init_z, float init_speed, float init_angle);
	Bullet(tuple<float, float, float>, tuple<float, float, float>, tuple<float, float, float, float>, float, float, float);
	std::tuple<float,float, float> position();
	void draw_bullet(bool fill);
	void move();
	void changeSpeed();
	std::tuple<float,float, float> getSpeed();
	bool isExplode(Tank* player, Tank* enemy);
};

#endif
