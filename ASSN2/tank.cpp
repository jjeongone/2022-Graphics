#include "tank.h"

Tank::Tank()
{
	bullet_speed = 0.006;
	angle_radian = 30 / 180 * 3.142;
	health = 3;
	color_weight = make_tuple(1.f, 1.f, 1.f);
}

Tank::Tank(float init_size, tuple<float, float, float> init_color_weight, float init_angle_radian, int init_health)
{
	size = init_size;
	color_weight = init_color_weight;
	angle_radian = init_angle_radian;
	health = init_health;
}

void Tank::draw_tank()
{
	body.width = size;
	body.height = 0.26 * size;
	body.rotation_angle_radian = 0.;
	body.coordinate2D = coordinate;
	body.colorRGB = make_tuple(0.3 * get<0>(color_weight), 0.7 * get<1>(color_weight), 0.3 * get<2>(color_weight));

	glPushMatrix();

	float coordY = coordinate.second + 0.26 * size * 0.95;
	float coordX = coordinate.first + 0.3 * size;
	glTranslatef(coordX, coordY, 0);
	turret.radius = 0.2 * size;
	turret.rotation_angle_radian = 0;
	turret.coordinate2D = make_pair(0, 0);
	turret.colorRGB = make_tuple(0.1 * get<0>(color_weight), 0.6 * get<1>(color_weight), 0.1 * get<2>(color_weight));

	glPushMatrix();
	barrel.height = 0.05 * size;
	barrel.width = 0.8 * size;

	glRotatef(angle_radian / (2 * 3.142) * 360, 0, 0, 1.);

	barrel.colorRGB = make_tuple(atan(bullet_speed * 20) / 3.142 * 2, atan(5 * bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2);
	barrel.coordinate2D = make_pair(0, 0);
	
	barrel.draw_rectangle();
	glPopMatrix();
	turret.draw_semicircle();
	glPopMatrix();


	for (int i = 0; i < 6; i++)
	{
		shape::Wheel tmp;
		
		tmp.radius = size / 12;
		tmp.num_circles = 5;
		tmp.rotation_angle_radian = -coordinate.first / tmp.radius * 50;

		glPushMatrix();
		if (i == 0)
		{
			glTranslatef(coordinate.first + tmp.radius, coordinate.second - 0.7 * tmp.radius, 0);
			glRotatef(tmp.rotation_angle_radian, 0, 0, 1);
		}
		else
		{
			glTranslatef(2 * tmp.radius, 0, 0);
			glRotatef(tmp.rotation_angle_radian, 0, 0, 1);

		}

		tmp.coordinate2D = make_pair(0, 0);
		tmp.colorRGB = make_tuple(0.3 * get<0>(color_weight), 0.3 * get<1>(color_weight), 0.8 * get<2>(color_weight));
		wheels.push_back(tmp);

		wheels[i].draw_wheel();
		glRotatef(-tmp.rotation_angle_radian, 0, 0, 1);
	}

	for (int i = 0; i < 6; i++)
		glPopMatrix();

	body.draw_rectangle();
}

void Tank::move(float dx, float dy) {
	coordinate.first += dx;
	coordinate.second += dy;
}

pair<float, float> Tank::getBarrelPosition() {
	return make_pair(coordinate.first + 0.3 * size + barrel.width * cos(angle_radian), coordinate.second + 0.26 * size * 0.95 + barrel.width * sin(angle_radian));
}

float Tank::getBarrelAngle()
{
	return angle_radian;
}

void Tank::setBarrel(float new_angle_radian)
{
	angle_radian = new_angle_radian;
}

void Tank::setBulletSpeed(float new_bullet_speed)
{
	bullet_speed = new_bullet_speed;
}

float Tank::getBulletSpeed()
{
	return bullet_speed;
}

float Tank::getBottom()
{
	return coordinate.second - 1.7 * size / 12;
}

int Tank::getHealth()
{
	return health;
}

void Tank::setHealth(int new_health)
{
	health = new_health;
}
