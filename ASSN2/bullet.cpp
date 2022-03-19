#include "bullet.h"

Bullet::Bullet() {
	x = 0.0;
	y = 0.0;
}

Bullet::Bullet(float init_x, float init_y) {
	x = init_x;
	y = init_y;
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
	glVertex2f(x, y + radious);
	glVertex2f(x + radious, y + radious);
	glVertex2f(x + radious, y);
	glEnd();
}

void Bullet::changeSpeed() {
	y_speed -= GRAVITY;
}

std::pair<float, float> Bullet::getSpeed() {
	return std::make_pair(x_speed, y_speed);
}

bool Bullet::isExplode(float bottom) {
	return this->y < bottom;
}
