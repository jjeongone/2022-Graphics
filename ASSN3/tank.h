#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include <functional>
#include "shape.h"

class Tank {
private:
	shape::Rectangle barrel;
	shape::Rectangle body;
	vector<shape::Wheel> wheels = { shape::Wheel(), shape::Wheel(), shape::Wheel(), shape::Wheel(), shape::Wheel(), shape::Wheel() };
	shape::Semicircle turret;

	template<class T>
	struct treenode {
		tuple<float, float, float> translate = make_tuple(0., 0., 0.);
		tuple<float, float, float, float> rotate = make_tuple(0., 0., 0., 0.);
		T* part;
		std::function<void(T&)> draw;
		
		struct treenode* sibling = nullptr;
		struct treenode* child = nullptr;
	};

	treenode<shape::Rectangle> body_node;

	float bullet_speed = 0.006;
	float angle_radian = 30 / 180 * 3.142;
	int health = 3;
	tuple<float, float, float> color_weight = make_tuple(1.f, 1.f, 1.f);
	bool shootability;
	bool is_reflect;

public: 
	float size;
	float speed;

	Tank();
	Tank(pair<float, float> init_coordinate, float init_size, tuple<float, float, float> init_color_weight, float init_angle_radian, int init_health, float init_bullet_speed, bool reflect);

	pair<float, float> coordinate;
	void draw_tank();

	template<class T>
	void display(treenode<T>* node);
	
	void move(float dx, float dy);
	pair<float, float> getBarrelPosition();
	float getBarrelAngle();
	void setBarrel(float new_angle_radian);
	void setBulletSpeed(float new_bullet_speed);
	float getBulletSpeed();
	float getBottom();
	int getHealth();
	void setHealth(int new_health);
	bool getShootability();
	void setShootability(bool shoot);
	void setCoordinate(pair<float, float> new_coordinate);
	pair<float, float> getCoordinate();
	float getSize();
};