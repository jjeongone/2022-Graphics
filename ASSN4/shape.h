#pragma once

#include <GL/freeglut.h>
#include <cmath>
#include <tuple>
#include <utility>
#include <vector>
//#include "shader.h"
#include "loader.h"


using namespace std;
extern unsigned int shader_program;


namespace shape {
	class Shape {
	public:
		//Shader shader = Shader("shader.vertex", "shader.fragment");
		tuple<float, float, float> colorRGB;
		float rotation_angle_radian;
		pair<float, float> translationXY;
		tuple<float, float, float> coordinate3D;	// left-bottom point
		bool fill = false;


		unsigned int texture;
		void set_color(tuple<float, float, float> color);
	};
	
	class Body : public Shape {
	private:
		vector<float> body_vertices_merge;

	public:
		Body();
		unsigned int VAO, VBO;

		void setShader();
		void draw();
	};

	class Head : public Shape {
	private:
		vector<float> head_vertices_merge;
		unsigned int VAO, VBO;

	public:
		Head();
		void setShader();
		void draw();
	};

	class Wheel : public Shape {
	private: 
		vector<float> wheel_vertices_merge;


	public:
		unsigned int VAO, VBO;
		Wheel();
		void setShader();
		void draw();
	};

	class WheelRight : public Shape {
	private:
		vector<float> wheel_vertices_merge;


	public:
		unsigned int VAO, VBO;
		WheelRight();
		void setShader();
		void draw();
	};

	class Barrel : public Shape {
	private:
		vector<float> barrel_vertices_merge;

	public:
		Barrel();
		unsigned int VAO, VBO;
		void setShader();
		void draw();
	};

	class Plane : public Shape {
	private: 
		float gap;
		float length;
		float depth;
		vector<float> vertices;
	public:
		unsigned int VAO, VBO;
		void set_condition(float l, float g, float d);
		void setShader();
		void draw_plane(bool fill);
	};
}