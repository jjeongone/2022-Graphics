#include "bullet.h"

Bullet::Bullet() {
	x = 0.0;
	y = 0.0;
}

Bullet::Bullet(float init_x, float init_y, float init_speed, float init_angle) {
	x = init_x;
	y = init_y;
	x_speed = init_speed * std::cos(init_angle);
	y_speed = abs(init_speed * std::sin(init_angle));
}

std::pair<float, float> Bullet::position() {
	return std::pair<float, float>(x, y);
}

void Bullet::move() {
	x += x_speed;
	y += y_speed;
}

void Bullet::draw() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x, y + radius);
	glVertex2f(x + radius, y + radius);
	glVertex2f(x + radius, y);
	glEnd();
}

void Bullet::changeSpeed() {
	y_speed -= GRAVITY;
}

std::pair<float, float> Bullet::getSpeed() {
	return std::make_pair(x_speed, y_speed);
}

bool Bullet::isExplode(float x, float y) {
	return (this->y < y || this->x > x);
}
