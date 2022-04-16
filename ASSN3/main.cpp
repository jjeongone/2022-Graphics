#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <GL/glut.h>
#include <vector>
#include <tuple>
#include "shape.h"
#include "bullet.h"
#include "tank.h"
#include "game.h"
#include "loader.h"
#include "camera.h"

// To recognize spacebar input
#define SPACEBAR 32
#define ENTER 13

// maybe custom
#define SPEED 0.01

float WidthFactor;
float HeightFactor;
bool isBegin = false;

static std::vector<Bullet> bulletList;

typedef struct world {
	float width;
	float height;
}world;

world gameWorld;

Game* game = new Game();
Camera* camera = new Camera();

Loader* wheel = new Loader("./model/centauro/source/wheel.obj");
Loader* body = new Loader("./model/centauro/source/body.obj");
Loader* barrel = new Loader("./model/centauro/source/barrel.obj");
Loader* head = new Loader("./model/centauro/source/head.obj");

void init(void) {
	gameWorld.width = 600;
	gameWorld.height = 600;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void temp_draw(bool fill) {
	std::vector < glm::vec3 > body_vertices = body->get_vertex();
	for (int i = 0; i < body_vertices.size(); i++) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(body_vertices[i].x, body_vertices[i].y, body_vertices[i].z);
		i++;
		glVertex3f(body_vertices[i].x, body_vertices[i].y, body_vertices[i].z);
		i++;
		glVertex3f(body_vertices[i].x, body_vertices[i].y, body_vertices[i].z);
		glEnd();
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->look_at();

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_LINE);
	game->display(false);

	glPolygonMode(GL_FRONT, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 5.0);
	game->display(true);
	glDisable(GL_POLYGON_OFFSET_FILL);
	/*switch (game->getStatus()) {
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
	}*/

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

void idle() {
	std::vector<Bullet>::iterator iter = bulletList.begin();
	while (iter != bulletList.end()) {
		(*iter).changeSpeed();
		if ((*iter).isExplode(game->getPlayer(), game->getEnemy())) {
			iter = bulletList.erase(iter);
		}
		else {
			(*iter).move();
			iter++;
		}
	}
	game->checkStatus();
	glutPostRedisplay();
}

void timer(int value) {
	/*if (game->getStatus() == PLAYING && game->getEnemy()->getShootability()) {
		Bullet new_bullet(game->getEnemy()->getBarrelPosition().first, game->getEnemy()->getBarrelPosition().second, game->getEnemy()->getBulletSpeed(), game->getEnemy()->getBarrelAngle());
		bulletList.push_back(new_bullet);
	}
	if (game->isAuto() && game->getPlayer()->getShootability()) {
		Bullet new_bullet(game->getPlayer()->getBarrelPosition().first, game->getPlayer()->getBarrelPosition().second, game->getPlayer()->getBulletSpeed(), game->getPlayer()->getBarrelAngle());
		bulletList.push_back(new_bullet);
	}
	glutTimerFunc(1000, timer, 1);*/
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
	case 'a': // head left
		if (angle + 0.03 <= 3.142 / 2 + 0.03)
			angle += 0.03;
		game->getPlayer()->setBarrel(angle);
		std::cout << "w\n";
		break;
	case 'd': // head right
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
	case 'v': // viewing mode(not yet)
		camera->change_mode();
		break;
	case 'r': // rendering mode(not yet)
		game->changeMode(ALLPASS);
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
	case 'R':
		//game->getPlayer()->setCoordinate(make_pair(-X_POSITION, GROUND));
		break;
	case 'A': // auto mode
		game->autoMode();
		break;
	case ENTER:
		game->setStatus(PLAYING);
		break;
	/*case SPACEBAR:
		if (game->getPlayer()->getShootability()) {
			Bullet new_bullet(game->getPlayer()->getBarrelPosition().first, game->getPlayer()->getBarrelPosition().second, game->getPlayer()->getBulletSpeed(), game->getPlayer()->getBarrelAngle());
			bulletList.push_back(new_bullet);
			break;
		}*/
	}
	glutPostRedisplay();
}

// not yet
void specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP: 
		/*if (!game->checkRightCollision(WidthFactor, HeightFactor, SPEED) && !game->checkRightCollision((game->getEnemy()->getCoordinate().first -game->getEnemy()->getSize()), HeightFactor, SPEED)) {
			game->getPlayer()->move(SPEED, 0.0);
		}*/
		break;
	case GLUT_KEY_DOWN:
		if (!game->checkLeftCollision(WidthFactor, HeightFactor, SPEED)) {
			game->getPlayer()->move(-SPEED, 0.0);
		}
		break;
	case GLUT_KEY_LEFT:
		/*if (!game->checkRightCollision(WidthFactor, HeightFactor, SPEED) && !game->checkRightCollision((game->getEnemy()->getCoordinate().first - game->getEnemy()->getSize()), HeightFactor, SPEED)) {
			game->getPlayer()->move(SPEED, 0.0);
		}*/
		break;
	case GLUT_KEY_RIGHT:
		if (!game->checkLeftCollision(WidthFactor, HeightFactor, SPEED)) {
			game->getPlayer()->move(-SPEED, 0.0);
		}
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
	//glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutTimerFunc(1000, timer, 1);


	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glewInit();
	glutMainLoop();
}