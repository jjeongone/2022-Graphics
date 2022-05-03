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
		void set_color(tuple<float, float, float> color);
	};
	
	class Body : public Shape {
	private:
		Loader* body = new Loader("./model/centauro/source/body.obj");
		vector<glm::vec3> body_vertices = body->get_vertex();
		vector<float> body_vertices_merge = body->merge();
	public:
		unsigned int VAO, VBO;

		void setShader();
		void draw();
	};

	class Head : public Shape {
	private:
		Loader* head = new Loader("./model/centauro/source/head.obj");
		vector<glm::vec3> head_vertices = head->get_vertex();
		vector<float> head_vertices_merge = head->merge();
		unsigned int VAO, VBO;

	public:
		void setShader();
		void draw();
	};

	class Wheel : public Shape {
	private: 
		Loader* wheel = new Loader("./model/centauro/source/wheel.obj");
		vector<glm::vec3> wheel_vertices = wheel->get_vertex();
		vector<float> wheel_vertices_merge = wheel->merge();

	public:
		unsigned int VAO, VBO;

		void setShader();
		void draw();
	};

	class WheelRight : public Shape {
	private:
		Loader* wheel_right = new Loader("./model/centauro/source/wheel_right.obj");
		vector<glm::vec3> wheel_vertices = wheel_right->get_vertex();
		vector<float> wheel_vertices_merge = wheel_right->merge();

	public:
		unsigned int VAO, VBO;

		void setShader();
		void draw();
	};

	class Barrel : public Shape {
	private:
		Loader* barrel = new Loader("./model/centauro/source/barrel.obj");
		vector<glm::vec3> barrel_vertices = barrel->get_vertex();
		vector<float> barrel_vertices_merge = barrel->merge();

	public:
		unsigned int VAO, VBO;
		void setShader();
		void draw();
	};

	class Plane : public Shape {
	private: 
		float gap;
		float length;
		float depth;
	public:
		void set_condition(float l, float g, float d);
		void draw_plane(bool fill);
	};
}