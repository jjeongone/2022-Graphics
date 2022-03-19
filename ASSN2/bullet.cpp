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

bool Bullet::isExplode(float ground, Tank* player, Tank* enemy) {
	std::pair<std::pair<float, float>, std::pair<float, float>> player_body_hitbox;
	player_body_hitbox.first = make_pair(player->coordinate.first, player->coordinate.second - player->size / 12.);
	player_body_hitbox.second = make_pair(player->coordinate.first + player->size, player->coordinate.second + 0.26 * player->size);

	std::pair<std::pair<float, float>, std::pair<float, float>> player_turret_hitbox;
	player_turret_hitbox.first = make_pair(player->coordinate.first + player->size * 0.1, player->coordinate.second + player->size * 0.26 * 0.95);
	player_turret_hitbox.second = make_pair(player->coordinate.first + player->size * 0.5, player->coordinate.second + player->size * (0.26 * 0.95 + 0.2));

	std::pair<std::pair<float, float>, std::pair<float, float>> enemy_body_hitbox;
	enemy_body_hitbox.first = make_pair(enemy->coordinate.first, enemy->coordinate.second - enemy->size / 12.);
	enemy_body_hitbox.second = make_pair(enemy->coordinate.first - enemy->size, enemy->coordinate.second + 0.26 * enemy->size);

	std::pair<std::pair<float, float>, std::pair<float, float>> enemy_turret_hitbox;
	enemy_turret_hitbox.first = make_pair(enemy->coordinate.first - enemy->size * 0.1, enemy->coordinate.second + enemy->size * 0.26 * 0.95);
	enemy_turret_hitbox.second = make_pair(enemy->coordinate.first - enemy->size * 0.5, enemy->coordinate.second + enemy->size * (0.26 * 0.95 + 0.2));

	// player hitbox
	if (this->x > player_body_hitbox.first.first && this->x < player_body_hitbox.second.first && this->y > player_body_hitbox.first.second && this->y < player_body_hitbox.second.second)
	{
		player->setHealth(player->getHealth() - 1);
		return true;
	}
	else if (this->x > player_turret_hitbox.first.first && this->x < player_turret_hitbox.second.first && this->y > player_turret_hitbox.first.second && this->y < player_turret_hitbox.second.second)
	{
		player->setHealth(player->getHealth() - 1);
		return true;
	}
	// enemy hitbox
	else if (this->x < enemy_body_hitbox.first.first && this->x > enemy_body_hitbox.second.first && this->y > enemy_body_hitbox.first.second && this->y < enemy_body_hitbox.second.second)
	{
		enemy->setHealth(enemy->getHealth() - 1);
		return true;
	}
	else if (this->x < enemy_turret_hitbox.first.first && this->x > enemy_turret_hitbox.second.first && this->y > enemy_turret_hitbox.first.second && this->y < enemy_turret_hitbox.second.second)
	{
		enemy->setHealth(enemy->getHealth() - 1);
		return true;
	}
	else
		return this->y < ground;
}
