#include "bullet.h"

Bullet::Bullet() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Bullet::Bullet(float init_x, float init_y, float init_z, float init_speed, float init_angle) {
	x = init_x;
	y = init_y;
	z = init_z;
	x_speed = init_speed * std::cos(init_angle);
	y_speed = abs(init_speed * std::sin(init_angle));
	z_speed = init_speed * std::cos(init_angle);
}

std::tuple<float, float, float> Bullet::position() {
	return std::tuple<float, float, float>(x, y, z);
}

void Bullet::move() {
	x += x_speed;
	y += y_speed;
	z += z_speed;
}

void Bullet::draw_bullet(bool fill) {
	cout << fill << endl;
	glPushMatrix();
	glTranslatef(x, y, z);
	if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < bullet_vertices.size(); i++) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(bullet_vertices[i].x, bullet_vertices[i].y, bullet_vertices[i].z);
		i++;
		glVertex3f(bullet_vertices[i].x, bullet_vertices[i].y, bullet_vertices[i].z);
		i++;
		glVertex3f(bullet_vertices[i].x, bullet_vertices[i].y, bullet_vertices[i].z);
		glEnd();
	}
	glPopMatrix();
}

void Bullet::changeSpeed() {
	y_speed -= GRAVITY;
}

std::tuple<float, float, float> Bullet::getSpeed() {
	return std::make_tuple(x_speed, y_speed, z_speed);
}

bool Bullet::isExplode(Tank* player, Tank* enemy) {
	return false;
}
