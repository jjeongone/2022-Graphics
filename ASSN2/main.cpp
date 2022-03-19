#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <vector>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <vector>

#include "shape.h"
#include "bullet.h"
#include "tank.h"
#include "game.h"

// To recognize spacebar input
#define SPACEBAR 32
#define ENTER 13

// maybe custom
#define SPEED 0.01

GLfloat WidthFactor;
GLfloat HeightFactor;

bool isBegin = false;


static std::vector<Bullet> bulletList;

typedef struct world {
	float width;
	float height;
}world;

world gameWorld;

shape::Line ground;

Game* game = new Game();

void init(void) {
	gameWorld.width = 1000;
	gameWorld.height = 600;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);


	ground.width = 5;
	ground.setPosition(game->getPlayer()->getBottom());
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (game->getStatus()) {
	case MENU:
		game->printTitle();
		break;
	case PLAYING:
		game->display();

		// draw bullet
		for (auto &elem : bulletList) {
			elem.draw();
		}
		break;
	case WIN:
		game->printWin();
		break;
	case GAMEOVER:
		game->printGameOver();
		break;
	}

	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	WidthFactor = (GLfloat)w / (GLfloat)300; 
	HeightFactor = (GLfloat)h / (GLfloat)300;
	glLoadIdentity();
	glOrtho(-1.0*WidthFactor, 1.0*WidthFactor, -1.0*HeightFactor, 1.0*HeightFactor, -1.0, 1.0);
}

void moveBullets() {
	std::vector<Bullet>::iterator iter = bulletList.begin();
	while (iter != bulletList.end()) {
		(*iter).changeSpeed();
		/*if ((*iter).isExplode(game->getEnemy()->coordinate.first, game->getPlayer()->getBottom())) {
			iter = bulletList.erase(iter);
		}
		else {
			(*iter).move();
		*/
		(*iter).move();
		iter++;
	}
	glutPostRedisplay();
}

void timer(int value) {
	Bullet new_bullet(game->getEnemy()->getBarrelPosition().first, game->getEnemy()->getBarrelPosition().second, game->getEnemy()->getBulletSpeed(), game->getEnemy()->getBarrelAngle());
	bulletList.push_back(new_bullet);
	glutTimerFunc(1000, timer, 1);
}


void keyboard(unsigned char key, int x, int y) {
	float angle = game->getPlayer()->getBarrelAngle();
	float speed = game->getPlayer()->getBulletSpeed();
	switch (key) {
	case 'w': // barrel up
		if (angle + 0.03 <= 3.142 / 2 + 0.03)
			angle += 0.03;
		game->getPlayer()->setBarrel(angle);
		std::cout << "w\n";
		break;
	case 's': // barrel down
		if (angle - 0.03 >= 0)
			angle -= 0.03;
		game->getPlayer()->setBarrel(angle);
		std::cout << "s\n";
		break;
	case 'e': // bullet speed up
		if (speed + 0.0002 <= 0.01)
			speed += 0.0002;
		game->getPlayer()->setBulletSpeed(speed);
		std::cout << "e\n";
		break;
	case 'q': // bullet speed down
		if (speed - 0.0002 >= 0.003)
			speed -= 0.0002;
		game->getPlayer()->setBulletSpeed(speed);
		std::cout << "q\n";
		break;
	case 'c': // all pass mode
		game->changeMode(ALLPASS);
		break;
	case 'f': // all fail mode
		game->changeMode(ALLFAIL);
		break;
	case 'n': // normal mode
		game->changeMode(NORMAL);
		break;
	case ENTER:
		game->setStatus(PLAYING);
		break;
	case SPACEBAR:
		std::cout << game->getPlayer()->getShootability();
		if (game->getPlayer()->getShootability()) {
			Bullet new_bullet(game->getPlayer()->getBarrelPosition().first, game->getPlayer()->getBarrelPosition().second, game->getPlayer()->getBulletSpeed(), game->getPlayer()->getBarrelAngle());
			bulletList.push_back(new_bullet);
			break;
		}
	}
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT: (game->getPlayer()->coordinate.first + game->getPlayer()->size + SPEED < WidthFactor) ? game->getPlayer()->move(SPEED, 0.0) : game->getPlayer()->move(0.0, 0.0);
		break;
	case GLUT_KEY_LEFT: (game->getPlayer()->coordinate.first - SPEED > -WidthFactor) ? game->getPlayer()->move(-SPEED, 0.0) : game->getPlayer()->move(0.0, 0.0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(gameWorld.width, gameWorld.height);
	glutCreateWindow("DimSum");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(moveBullets);
	glutTimerFunc(1000, timer, 1);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}