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


static std::vector<Bullet> playerBullet;

typedef struct world {
	float width;
	float height;
}world;

world gameWorld;

shape::Line ground;

Tank playerTank;

Game game;

void init(void) {
	gameWorld.width = 1000;
	gameWorld.height = 600;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	playerTank.size = 0.5;
	playerTank.setBarrel(30. / 360 * 2 * 3.142);

	ground.width = 5;
	ground.setPosition(playerTank.getBottom());
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	if (!isBegin) {
		game.printTitle();
	}
	else {
		ground.draw_line();

		// draw tank
		playerTank.draw_tank();

		// draw bullet
		for (auto &elem : playerBullet) {
			elem.draw();
		}

		game.printStatus();
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
	std::vector<Bullet>::iterator iter = playerBullet.begin();
	while (iter != playerBullet.end()) {
		(*iter).changeSpeed();
		if ((*iter).isExplode(playerTank.getBottom())) {
			iter = playerBullet.erase(iter);
		}
		else {
			(*iter).move();
			iter++;
		}
	}
	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
	float angle = playerTank.getBarrelAngle();
	float speed = playerTank.getBulletSpeed();
	switch (key) {
	case 'w': // barrel up
		if (angle + 0.03 <= 3.142 / 2 + 0.03)
			angle += 0.03;
		playerTank.setBarrel(angle);
		std::cout << "w\n";
		break;
	case 's': // barrel down
		if (angle - 0.03 >= 0)
			angle -= 0.03;
		playerTank.setBarrel(angle);
		std::cout << "s\n";
		break;
	case 'e': // bullet speed up
		if (speed + 0.0002 <= 0.01)
			speed += 0.0002;
		playerTank.setBulletSpeed(speed);
		std::cout << "e\n";
		break;
	case 'q': // bullet speed down
		if (speed - 0.0002 >= 0.003)
			speed -= 0.0002;
		playerTank.setBulletSpeed(speed);
		std::cout << "q\n";
		break;
	case 'c': // all pass mode
		game.changeMode(ALLPASS);
		break;
	case 'f': // all fail mode
		game.changeMode(ALLFAIL);
		break;
	case 'n': // normal mode
		game.changeMode(NORMAL);
		break;
	case ENTER:
		isBegin = true;
		break;
	case SPACEBAR:
		Bullet new_bullet(playerTank.getBarrelPosition().first, playerTank.getBarrelPosition().second, playerTank.getBulletSpeed(), playerTank.getBarrelAngle());
		playerBullet.push_back(new_bullet);
		break;
	}
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
	switch (key) {
	/*case GLUT_KEY_UP: playerTank.move(0.0, SPEED);
		break;
	case GLUT_KEY_DOWN: playerTank.move(0.0, -SPEED);
		break;*/
	case GLUT_KEY_RIGHT: (playerTank.coordinate.first + playerTank.size + SPEED < WidthFactor) ? playerTank.move(SPEED, 0.0) : playerTank.move(0.0, 0.0);
		break;
	case GLUT_KEY_LEFT: (playerTank.coordinate.first - SPEED > -WidthFactor) ? playerTank.move(-SPEED, 0.0) : playerTank.move(0.0, 0.0);
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(gameWorld.width, gameWorld.height);
	glutCreateWindow("DimSum");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(moveBullets);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}