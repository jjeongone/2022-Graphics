#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include <functional>
#include "shape.h"

class Tank {
private:
	shape::Barrel barrel;
	shape::Body body;
	vector<shape::Wheel> wheels = { shape::Wheel(), shape::Wheel(), shape::Wheel(), shape::Wheel() };
	vector<shape::WheelRight> right_wheels = { shape::WheelRight(), shape::WheelRight(), shape::WheelRight(), shape::WheelRight() };
	shape::Head head;

	template<class T>
	struct treenode {
		tuple<float, float, float> translate = make_tuple(0., 0., 0.);
		tuple<float, float, float, float> rotate = make_tuple(0., 0., 0., 0.);
		T* part = nullptr;
		std::function<void(T&)> draw;
		
		struct treenode* sibling = nullptr;
		struct treenode* child = nullptr;
	};

	treenode<shape::Body> body_node;

	float bullet_speed = 0.006;
	float angle_radian = 30 / 180 * 3.142;
	float head_angle = 0.;
	float barrel_angle = 0.;
	float wheel_angle_left = 0.;
	float wheel_angle_right = 0.;

	float recoil_theta = 0.;
	bool is_recoil;

	int health = 3;
	tuple<float, float, float> color_weight = make_tuple(1.f, 1.f, 1.f);
	bool shootability;
	bool is_reflect;

	tuple<float, float, float> barrelPosition = make_tuple(0.f, 0.f, 0.f);
	tuple<float, float, float, float> barrelOrientation = make_tuple(0., 0., 0., 0.);

public: 
	float size;
	float speed;
	bool fill;

	Tank();
	Tank(tuple<float, float, float> init_coordinate, float init_size, tuple<float, float, float> init_color_weight, float init_angle_radian, int init_health, float init_bullet_speed, bool reflect);

	tuple<float, float, float> coordinate;
	void draw_tank(bool fill);

	template<class T>
	void display(treenode<T>* node);
	
	tuple<float, float, float> getBarrelPosition();
	tuple<float, float, float, float> getBarrelOrientation();
	float getBarrelAngle();
	void setBarrel(float new_angle_radian);
	float getHeadAngle();
	void setHead(float new_angle_radian);
	void setBulletSpeed(float new_bullet_speed);
	float getBulletSpeed();
	int getHealth();
	void setHealth(int new_health);
	bool getShootability();
	void setShootability(bool shoot);
	void setCoordinate(tuple<float, float, float> new_coordinate);
	tuple<float, float, float> getCoordinate();
	float getSize();

	pair<float, float> getWheelAngle();
	void setWheelAngle(pair<float, float> new_angle);

	void setRecoil();
	void recoil();
};