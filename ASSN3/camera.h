#pragma once
#include <tuple>
#include <GL/glew.h>

enum view_mode {
	THIRD = 0,
	FIRST = 1,
	TOP = 2,
};

using namespace std;
class Camera {
private:
	tuple<float, float, float> eye;
	tuple<float, float, float> center;
	tuple<float, float, float> up;
	view_mode mode;

public:
	Camera();
	Camera(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u);
	void look_at();
	void set_position(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u);
	void change_mode();
};