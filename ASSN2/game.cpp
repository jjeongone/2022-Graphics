#include "game.h"

void printText(float r, float g, float b, float x, float y, std::string text) {
	int i;
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

std::string getModeName(bool auto_mode, Mode m) {
	switch (m) {
	case NORMAL:
		return "NORMAL";
	case ALLPASS:
		return "ALL PASS";
	case ALLFAIL:
		return "ALL FAIL";
	}
}

Game::Game()
{
	mode = NORMAL;
	status = MENU;
	auto_mode = false;
	player = new Tank(make_pair(-X_POSITION, GROUND), 0.7f, make_tuple(1.f, 1.f, 1.f), 30. / 180 * 3.142, 3, 0.006, false);
	enemy = new Tank(make_pair(X_POSITION, GROUND), 0.7f, make_tuple(2.2f, 0.2f, 2.0f), 30. / 180 * 3.142, 3, -0.006, true);
	enemyList.push_back(*enemy);
	ground.width = 5;
	ground.setPosition(player->getBottom());
}

Mode Game::getMode()
{
	return mode;
}

void Game::changeMode(Mode m)
{
	mode = m;
	std::cout << getModeName(auto_mode, m) + " mode";

	switch (mode) {
	case NORMAL:
		player->setHealth(3);
		player->setShootability(true);
		enemy->setHealth(3);
		enemy->setShootability(true);
		break;
	case ALLPASS:
		player->setHealth(3);
		player->setShootability(true);
		enemy->setHealth(1);
		enemy->setShootability(false);
		break;
	case ALLFAIL:
		player->setHealth(1);
		player->setShootability(false);
		enemy->setHealth(3);
		enemy->setShootability(true);
		break;
	}
}

void Game::printTitle()
{
	float x = 0.0;
	float y = 0.1;

	printText(0.9, 0.9, 0.9, x-0.35, y, "<Fortress>");
	printText(0.9, 0.9, 0.9, x-0.6, y-= 0.1, "Press ENTER to play");
	printText(0.9, 0.9, 0.9, x-0.6, y -= 0.3, "developed by DimSum");
}

void Game::printGameOver()
{
	float x = -0.5;
	float y = 0.0;

	printText(0.9, 0.0, 0.0, x, y, "GAME OVER...");
}

void Game::printWin()
{
	float x = -0.1;
	float y = 0.0;

	printText(0.9, 0.9, 0.0, x, y, "WIN!!!");
}

void Game::printStatus()
{
	float x = -3.2;
	float y = 1.8;

	string player_mode = auto_mode ? "(AUTO)" : "";

	printText(0.9, 0.9, 0.9, x, y, "Player" + player_mode);
	printText(0.9, 0.9, 0.9, x, y-0.1, "HP: " + std::to_string(player->getHealth()));

	printText(0.9, 0.9, 0.9, 2.3, y, "Mode: " + getModeName(auto_mode, mode));
}

void Game::display()
{
	printStatus();
	ground.draw_line();
	player->draw_tank();
	glPushMatrix();
	glTranslatef(enemy->coordinate.first, enemy->coordinate.second, 0);
	glRotatef(180, 0, 1, 0);
	glTranslatef(-enemy->coordinate.first, -enemy->coordinate.second, 0);
	enemy->draw_tank();
	glPopMatrix();
}

Tank* Game::getPlayer()
{
	return this->player;
}

Tank * Game::getEnemy()
{
	return this->enemy;
}

Status Game::getStatus()
{
	return status;
}

void Game::setStatus(Status s)
{
	status = s;
}

void Game::autoMode()
{
	auto_mode = !auto_mode;
}

bool Game::isAuto()
{
	return auto_mode;
}

void Game::checkStatus()
{
	if (player->getHealth() <= 0) {
		status = GAMEOVER;
	}
	else if (enemy->getHealth() <= 0) {
		status = WIN;
	}
}

bool Game::checkRightCollision(float width, float height, float speed)
{
	if (player->getCoordinate().first + player->getSize() + speed > width) {
		return true;
	}
	else {
		return false;
	}
}

bool Game::checkLeftCollision(float width, float height, float speed)
{
	if (player->getCoordinate().first - speed < -width) {
		return true;
	}
	else {
		return false;
	}
}
