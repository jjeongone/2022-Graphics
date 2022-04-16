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
	bool render_mode;
	Tank* player = nullptr;
	Tank* enemy = nullptr;

	tuple<float, float, float> player_translation = make_tuple(0, 0, 30);
	tuple<float, float, float, float> player_rotation = make_tuple(0, 0, 1, 0);
	tuple<float, float, float> enemy_translation = make_tuple(0, 0, -30);
	tuple<float, float, float, float> enemy_rotation = make_tuple(180, 0, 1, 0);

	std::vector<Tank> enemyList;
	shape::Plane ground;
	shape::Plane boundary;

	template<class T>
	struct treenode {
		tuple<float, float, float> translate = make_tuple(0., 0., 0.);
		tuple<float, float, float, float> rotate = make_tuple(0., 0., 0., 0.);
		T* part = nullptr;
		std::function<void(T&, bool)> draw;

		struct treenode* sibling = nullptr;
		struct treenode* child = nullptr;
	};

	treenode<shape::Plane> ground_node;

public:
	Game();
	enum mode getMode();
	void changeMode(enum mode m);
	void printTitle();
	void printGameOver();
	void printWin();
	void printStatus();
	void display(bool fill);

	void drawWorld(bool fill);
	template <class T>
	void display(treenode<T>* node, bool fill);

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
	void setRenderMode();
	bool getRenderMode();

	tuple<float, float, float> get_player_translation();
	tuple<float, float, float> get_enemy_translation();
	tuple<float, float, float, float> get_player_rotation();
	tuple<float, float, float, float> get_enemy_rotation();

	void set_player_translation(tuple<float, float, float>);
	void set_enemy_translation(tuple<float, float, float>);
	void set_player_rotation(tuple<float, float, float, float>);
	void set_enemy_rotation(tuple<float, float, float, float>);
};

#endif // !GAME_H
