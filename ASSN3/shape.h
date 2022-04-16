#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include <tuple>
#include <utility>
#include <vector>
#include "loader.h"

using namespace std;

namespace shape {
	class Shape {
	public:
		tuple<float, float, float> colorRGB;
		float rotation_angle_radian;
		pair<float, float> translationXY;
		tuple<float, float, float> coordinate3D;	// left-bottom point
		bool fill = false;
		void set_color(tuple<float, float, float> color);
	};
	
	class Body : public Shape {
	private:
		Loader* body = new Loader("./model/centauro/source/body.obj");
		vector<glm::vec3> body_vertices = body->get_vertex();
	public:
		void draw();
	};

	class Head : public Shape {
	private:
		Loader* head = new Loader("./model/centauro/source/head.obj");
		vector<glm::vec3> head_vertices = head->get_vertex();
	public:
		void draw();
	};

	class Wheel : public Shape {
	private: 
		Loader* wheel = new Loader("./model/centauro/source/wheel.obj");
		vector<glm::vec3> wheel_vertices = wheel->get_vertex();
	public:
		void draw();
	};

	class Barrel : public Shape {
	private:
		Loader* barrel = new Loader("./model/centauro/source/barrel.obj");
		vector<glm::vec3> barrel_vertices = barrel->get_vertex();
	public:
		void draw();
	};

	class Plane : public Shape {
	private: 
		float gap;
		float length;
		float depth;
	public:
		void set_condition(float l, float g, float d);
		void draw_plane();
	};
}