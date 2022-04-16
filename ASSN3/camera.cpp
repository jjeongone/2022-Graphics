#include "camera.h"

Camera::Camera()
{
	eye = make_tuple(-7.0, 7.0, 0.0); // need to edit as player position
	center = make_tuple(-1.0, 7.0, 0.0);
	up = make_tuple(0.0, 1.0, 0.0);
	left = 4;
	right = 4;
	front = 1;
	back = 70;
	mode = THIRD;
}

Camera::Camera(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u)
{
	eye = e;
	center = c;
	up = u;
	mode = THIRD;
}

void Camera::look_at()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (mode == TOP)
		glOrtho(-30, 30, -30, 30, front, back);
	else
		glFrustum(-left, left, -right, right, front, back);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(get<0>(eye), get<1>(eye), get<2>(eye), get<0>(center), get<1>(center), get<2>(center), get<0>(up), get<1>(up), get<2>(up));
}


void Camera::set_position(tuple<float, float, float> e, tuple<float, float, float> c, tuple<float, float, float> u)
{
	eye = e;
	center = c;
	up = u;
}

void Camera::set_volume(float l, float r, float f, float b)
{
	left = l;
	right = r;
	front = f;
	back = b;
}


void Camera::change_mode()
{
	switch (mode) {
	case THIRD:
		set_position(make_tuple(0.0, 20.0, 5.0), make_tuple(0.0, 0.0, 1.0), make_tuple(0.0, 1.0, 0.0)); // need to edit as player position
		mode = FIRST;
		break;
	case FIRST:
		set_position(make_tuple(0.0, 13.0, 0.0), make_tuple(0.0, 1.0, 0.0), make_tuple(0.0, 0.0, -1.0));
		mode = TOP;
		break;
	case TOP:
		set_position(make_tuple(0.0, 20.0, 5.0), make_tuple(0.0, 0.0, 1.0), make_tuple(0.0, 1.0, 0.0)); // need to edit as player position
		mode = THIRD;
		break;
	}
}
