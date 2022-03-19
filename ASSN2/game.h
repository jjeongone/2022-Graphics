#ifndef GMAE_H
#define GAME_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

#include "tank.h"

enum mode {
	NORMAL = 0,
	ALLPASS = 1,
	ALLFAIL = 2,
};

class Game {
private:
	int mode;
	Tank playerTank;
	std::vector<Tank> enemyList;
public:
	Game();
	void changeMode(enum mode m);
	void printTitle();
	void printGameOver();
	void printStatus();
};

#endif // !GMAE_H
