#pragma once
#include <GL/freeglut.h>
#include <vector>
#include "shape.h"

class Tank {
private:
	shape::Rectangle barrel;
	shape::Rectangle body;
	vector<shape::Wheel> wheels;
	shape::Semicircle turret;
	float bullet_speed = 0.006;
	float angle_radian;

public: 
	float size;
	float speed;

	pair<float, float> coordinate;
	void draw_tank();
	void move(float dx, float dy);
	pair<float, float> getBarrelPosition();
	void setBarrel(float new_angle_radian);
	void setBulletSpeed(float new_bullet_speed);
	float getBulletSpeed();
	float getBottom();
};