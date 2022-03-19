#ifndef GMAE_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

#include "tank.h"

#define GROUND -1.0

enum mode {
	NORMAL = 0,
	ALLPASS = 1,
	ALLFAIL = 2,
};

enum status {
	MENU = 0,
	PLAYING = 1,
	WIN = 2,
	GAMEOVER = 3,
};

class Game {
private:
	mode mode;
	status status;
	Tank* player = nullptr;
	Tank* enemy = nullptr;
	std::vector<Tank> enemyList;
	shape::Line ground;
public:
	Game();
	void changeMode(enum mode m);
	void printTitle();
	void printGameOver();
	void printWin();
	void printStatus();
	void display();
	Tank* getPlayer();
	Tank* getEnemy();
	enum status getStatus();
	void setStatus(enum status s);
};

#endif // !GMAE_H
