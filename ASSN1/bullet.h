#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#include <utility>

#define GRAVITY 0.00002

class Bullet {
private:
	float x;
	float y;
	float radious = 0.05;
	float x_speed = 0.005;
	float y_speed = 0.001;
public:
	Bullet();
	Bullet(float init_x, float init_y);
	std::pair<float,float> position();
	void draw();
	void move();
	void changeSpeed();
	std::pair<float,float> getSpeed();
	bool isExplode(float bottom);
};

#endif