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

public: 
	float size;
	float speed;
	float bullet_speed;
	pair<float, float> coordinate;
	void draw_tank();
};