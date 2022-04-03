#include "camera.h"

Camera::Camera()
{
	eye = make_tuple(0.0, 10.0, 5.0); // need to edit as player position
	center = make_tuple(0.0, 0.0, 1.0);
	up = make_tuple(0.0, 1.0, 0.0);
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
	glFrustum(-2, 2, -1.5, 1.5, 1, 40);

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

void Camera::change_mode()
{
	switch (mode) {
	case THIRD:
		eye = make_tuple(0.0, 10.0, 5.0); // need to edit as player position
		center = make_tuple(0.0, 0.0, 1.0);
		up = make_tuple(0.0, 1.0, 0.0);
		mode = FIRST;
		break;
	case FIRST:
		eye = make_tuple(0.0, 10.0, 0.0);
		center = make_tuple(0.0, 1.0, 0.0);
		up = make_tuple(-1.0, 0.0, 0.0);
		mode = TOP;
		break;
	case TOP:
		eye = make_tuple(0.0, 10.0, 5.0); // need to edit as player position
		center = make_tuple(0.0, 0.0, 1.0);
		up = make_tuple(0.0, 1.0, 0.0);
		mode = THIRD;
		break;
	}
}
