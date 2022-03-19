#include "tank.h"

void Tank::draw_tank()
{
	for (int i = 0; i < 6; i++)
	{
		shape::Wheel tmp;
		tmp.radius = size / 12;
		tmp.num_circles = 5;
		float coordY = coordinate.second - 0.7 * tmp.radius;
		float coordX = coordinate.first + (1 + 2 * i) * tmp.radius;
		tmp.coordinate2D = make_pair(coordX, coordY);
		tmp.colorRGB = make_tuple(0.3, 0.3, 0.8);
		wheels.push_back(tmp);
		tmp.draw_wheel();
	}

	barrel.height = 0.05 * size;
	barrel.rotation_angle_radian = angle_radian;
	barrel.colorRGB = make_tuple(0.1, 0.5, 0.1);
	barrel.width = 0.8 * size;
	float coordY = coordinate.second + 0.26 * size * 0.95;
	float coordX = coordinate.first + 0.3 * size;
	barrel.coordinate2D = make_pair(coordX, coordY);
	barrel.draw_rectangle();

	turret.radius = 0.2 * size;
	turret.rotation_angle_radian = 0;
	turret.coordinate2D = make_pair(coordX, coordY);
	turret.colorRGB = make_tuple(0.1, 0.6, 0.1);
	turret.draw_semicircle();

	body.width = size;
	body.height = 0.26 * size;
	body.rotation_angle_radian = 0.;
	body.coordinate2D = coordinate;
	body.colorRGB = make_tuple(0.3, 0.7, 0.3);
	body.draw_rectangle();
}

void Tank::move(float dx, float dy) {
	coordinate.first += dx;
	coordinate.second += dy;
}

pair<float, float> Tank::getBarrelPosition() {
	return make_pair(barrel.coordinate2D.first + barrel.width * cos(angle_radian), barrel.coordinate2D.second + barrel.width * sin(angle_radian));
}

void Tank::setBarrel(float new_angle_radian)
{
	angle_radian = new_angle_radian;
}

float Tank::getBottom()
{
	return coordinate.second - 1.7 * size / 12;
}
