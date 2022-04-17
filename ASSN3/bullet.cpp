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

Bullet::Bullet(tuple<float, float, float> coordinate, tuple<float, float, float> translation, tuple<float, float, float, float> rotation, float head, float barrel, float s)
{
	tank_coordinate = coordinate;
	tank_translation = translation;
	tank_rotation = rotation;
	head_angle = head;
	barrel_angle = barrel;
	speed = s;

	glm::vec4 bullet_pos = cal_transformation() * glm::vec4(0, 0, 0, 1);
	x = bullet_pos.x;
	y = bullet_pos.y;
	z = bullet_pos.z;
}

std::tuple<float, float, float> Bullet::position() {
	return std::tuple<float, float, float>(x, y, z);
}

glm::mat4 Bullet::cal_transformation()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(get<0>(tank_coordinate), get<1>(tank_coordinate), get<2>(tank_coordinate)));
	matrix = glm::translate(matrix, glm::vec3(get<0>(tank_translation), get<1>(tank_translation), get<2>(tank_translation)));
	matrix = glm::rotate(matrix, glm::radians(get<0>(tank_rotation)), glm::vec3(get<1>(tank_rotation), get<2>(tank_rotation), get<3>(tank_rotation)));
	matrix = glm::translate(matrix, glm::vec3(0., 2.5, -1.97));
	matrix = glm::translate(matrix, glm::vec3(0, 0, 4));
	matrix = glm::rotate(matrix, glm::radians(head_angle), glm::vec3(0., 1., 0.));
	matrix = glm::rotate(matrix, glm::radians(-barrel_angle), glm::vec3(1., 0., 0.));
	matrix = glm::translate(matrix, glm::vec3(0, 6., bullet_position));

	return matrix;
}

void Bullet::move() {
	bullet_position -= speed;

	glm::vec4 bullet_pos = cal_transformation() * glm::vec4(0, 0, 0, 1);

	x = bullet_pos.x;
	y += y_speed;
	z = bullet_pos.z;
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

bool Bullet::isExplode(Tank* player, pair<glm::vec3, glm::vec3> player_bound, Tank* enemy, pair<glm::vec3, glm::vec3> enemy_bound) {
	if (y < player_bound.second.y && (x > player_bound.first.x && x < player_bound.second.x) && (z > player_bound.first.z && z < player_bound.second.z))
	{
		player->setHealth(player->getHealth() - 1);
		return true;
	}
	else if (y < enemy_bound.second.y && (x > enemy_bound.first.x && x < enemy_bound.second.x) && (z > enemy_bound.first.z && z < enemy_bound.second.z))
	{
		enemy->setHealth(enemy->getHealth() - 1);
		return true;
	}
	else if (y < 0)
	{
		return true;
	}
	return false;
}
