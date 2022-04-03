#ifndef GMAE_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

#include "tank.h"

#define X_POSITION 3.0
#define GROUND -1.0

enum Mode {
	NORMAL = 0,
	ALLPASS = 1,
	ALLFAIL = 2,
};

enum Status {
	MENU = 0,
	PLAYING = 1,
	WIN = 2,
	GAMEOVER = 3,
};

class Game {
private:
	Mode mode;
	Status status;
	bool auto_mode;
	Tank* player = nullptr;
	Tank* enemy = nullptr;
	std::vector<Tank> enemyList;
	shape::Line ground;
public:
	Game();
	Mode getMode();
	void changeMode(Mode m);
	void printTitle();
	void printGameOver();
	void printWin();
	void printStatus();
	void display();
	Tank* getPlayer();
	Tank* getEnemy();
	Status getStatus();
	void setStatus(Status s);
	void autoMode();
	bool isAuto();
	void checkStatus();
	bool checkRightCollision(float width, float height, float speed);
	bool checkLeftCollision(float width, float height, float speed);
};

#endif // !GMAE_H
