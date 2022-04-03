#pragma once
#include <GL/freeglut.h>
#include <cmath>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace shape {
	class Shape {
	public:
		tuple<float, float, float> colorRGB;
		float rotation_angle_radian;
		pair<float, float> translationXY;
		pair<float, float> coordinate2D;	// left-bottom point
	};

	class Line : public Shape {
	public:
		float width, length, position;
		pair<float, float> line_position;
		void draw_line();
		void setPosition(float new_position);
	};

	class Rectangle : public Shape {
	public:
		float width, height;
		void draw_rectangle();
	};

	class Semicircle : public Shape {
	public:
		float radius;
		void draw_semicircle();
	};

	class Circle : public Shape {
	public:
		float radius;
		void draw_circle();
	};

	class Wheel : public Shape {
	private:
		Circle body_large;
		Circle body_background;
		Circle body_small;
		vector<Circle> small_bolts;
	public:
		float radius;
		int num_circles;
		void draw_wheel();
	};
}