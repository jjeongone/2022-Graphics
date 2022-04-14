#ifndef GMAE_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <vector>
#include <cstdlib> 

#include "tank.h"

#define X_POSITION 3.0
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
	bool auto_mode;
	Tank* player = nullptr;
	Tank* enemy = nullptr;
	std::vector<Tank> enemyList;
	shape::Plane ground;
	shape::Plane boundary;
public:
	Game();
	enum mode getMode();
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
	void autoMode();
	bool isAuto();
	void checkStatus();
	bool checkRightCollision(float width, float height, float speed);
	bool checkLeftCollision(float width, float height, float speed);
	void enemyAction();
	void recoil(float speed);
};

#endif // !GMAE_H
