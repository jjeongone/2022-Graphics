#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <cmath>
#include <vector>
#include <utility>

#define GRAVITY 0.00002

class Bullet {
private:
	float x;
	float y;
	float radius = 0.05;
	float x_speed = 0.006 * std::cos(30. * 3.142 / 180);
	float y_speed = 0.006 * std::sin(30. * 3.142 / 180);
public:
	Bullet();
	Bullet(float init_x, float init_y, float init_speed, float init_angle);
	std::pair<float,float> position();
	void draw();
	void move();
	void changeSpeed();
	std::pair<float,float> getSpeed();
	bool isExplode(float x, float y);
};

#endif