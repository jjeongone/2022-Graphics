#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/string_cast.hpp>
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
unsigned int shader_program;

static std::vector<Bullet> bulletList;

typedef struct world {
	float width;
	float height;
}world;

world gameWorld;
Game* game = new Game();

void init(void) {
	gameWorld.width = 600;
	gameWorld.height = 600;
}

void initShader(void) {
	/*init shader*/
	std::ifstream vertex_shader_file("shader.vertex");
	std::ifstream fragment_shader_file("shader.fragment");
	std::stringstream raw_vertex_shader, raw_fragment_shader;
	std::string vertex_shader_string, fragment_shader_string;

	raw_vertex_shader << vertex_shader_file.rdbuf();
	vertex_shader_string = raw_vertex_shader.str();
	const char * vertex_shader_source = vertex_shader_string.c_str();

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	raw_fragment_shader << fragment_shader_file.rdbuf();
	fragment_shader_string = raw_fragment_shader.str();
	const char * fragment_shader_source = fragment_shader_string.c_str();

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINK::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//glUseProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void tempDisplay(void) {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(shader_program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (game->getStatus()) {
	case MENU:
		game->printTitle();
		break;
	case PLAYING:
		game->camera->look_at();
		game->display();

		// draw bullet
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT, GL_LINE);
		for (auto& elem : bulletList) {
			elem.draw_bullet(false);
		}

		if (game->getRenderMode()) {
			glPolygonMode(GL_FRONT, GL_FILL);
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 5.0);
			for (auto& elem : bulletList) {
				elem.draw_bullet(true);
			}
			glDisable(GL_POLYGON_OFFSET_FILL);
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

void idle() {
	std::vector<Bullet>::iterator iter = bulletList.begin();

	while (iter != bulletList.end()) {
		(*iter).changeSpeed();

		if ((*iter).isExplode(game->getPlayer(), game->getPlayerTankBound(game->get_player_translation()), game->getEnemy(), game->getEnemyTankBound(game->get_enemy_translation()))) {
			iter = bulletList.erase(iter);
		}

		else {
			(*iter).move();
			iter++;
		}
	}
	game->getPlayer()->recoil();
	game->getEnemy()->recoil();

	game->camera->set_transform(game->getPlayerTankPosition(), game->getPlayerTankBarrelPosition());
	game->checkStatus();

	glutPostRedisplay();
}

void actionTimer(int value) {
	if (game->getStatus() == PLAYING) {
		game->enemyAction();
	}

	glutTimerFunc(100, actionTimer, 1);
}

void shootTimer(int value) {
	if (game->getStatus() == PLAYING && game->getEnemy()->getShootability()) {
		game->getEnemy()->setRecoil();

		Bullet new_bullet(game->getEnemy()->getCoordinate(), game->get_enemy_translation(), game->get_enemy_rotation(), game->getEnemy()->getHeadAngle(), game->getEnemy()->getBarrelAngle(), -game->getEnemy()->getBulletSpeed());
		bulletList.push_back(new_bullet);
	}

	if (game->isAuto() && game->getPlayer()->getShootability()) {
		game->getPlayer()->setRecoil();

		Bullet new_bullet(game->getPlayer()->getCoordinate(), game->get_player_translation(), game->get_player_rotation(), game->getPlayer()->getHeadAngle(), game->getPlayer()->getBarrelAngle(), game->getPlayer()->getBulletSpeed());
		bulletList.push_back(new_bullet);
	}

	glutTimerFunc(3000, shootTimer, 1);
}


void keyboard(unsigned char key, int x, int y) {
	float barrel_angle = game->getPlayer()->getBarrelAngle();
	float head_angle = game->getPlayer()->getHeadAngle();
	float speed = game->getPlayer()->getBulletSpeed();

	switch (key) {
	case 'w': // barrel up
		if (barrel_angle - 0.5 >= -30.)
			barrel_angle -= 0.5;

		game->getPlayer()->setBarrel(barrel_angle);
		break;

	case 's': // barrel down
		if (barrel_angle + 0.5 <= 0)
			barrel_angle += 0.5;

		game->getPlayer()->setBarrel(barrel_angle);
		break;

	case 'a': // head left
		if (head_angle + 1. <= 90.)
			head_angle += 1.;

		game->getPlayer()->setHead(head_angle);
		break;

	case 'd': // head right
		if (head_angle - 1. >= -90.)
			head_angle -= 1.;

		game->getPlayer()->setHead(head_angle);
		break;

	case 'e': // bullet speed up
		if (speed + 0.2 <= 2)
			speed += 0.2;

		game->getPlayer()->setBulletSpeed(speed);
		break;

	case 'q': // bullet speed down
		if (speed - 0.2 >= 0.2)
			speed -= 0.2;

		game->getPlayer()->setBulletSpeed(speed);
		break;

	case 'v': // viewing mode(not yet)
		game->camera->change_mode();
		break;

	case 'r':
		game->setRenderMode();
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

	case 'A': // auto mode
		game->autoMode();
		break;

	case ENTER:
		game->setStatus(PLAYING);
		break;

	case SPACEBAR:
		if (game->getPlayer()->getShootability()) {
			game->getPlayer()->setRecoil();

			Bullet new_bullet(game->getPlayer()->getCoordinate(), game->get_player_translation(), game->get_player_rotation(), game->getPlayer()->getHeadAngle(), game->getPlayer()->getBarrelAngle(), game->getPlayer()->getBulletSpeed());
			bulletList.push_back(new_bullet);

			break;
		}
	}
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
	tuple<float, float, float> tmp_translation;
	tuple<float, float, float, float> tmp_rotation;
	float tmp_angle;
	pair<float, float> tmp_wheel_angle;

	switch (key) {
	case GLUT_KEY_UP:
		tmp_translation = game->get_player_translation();
		tmp_angle = get<0>(game->get_player_rotation());

		get<2>(tmp_translation) -= 0.2 * cos(tmp_angle / 180 * 3.142);
		get<0>(tmp_translation) -= 0.2 * sin(tmp_angle / 180 * 3.142);

		if (!game->checkBoundaryCollision(game->getPlayerTankBound(tmp_translation)) && !game->checkTankCollision(game->getPlayerTankBound(tmp_translation), game->getEnemyTankBound(game->get_enemy_translation())))
		{
			tmp_wheel_angle = game->getPlayer()->getWheelAngle();
			tmp_wheel_angle.first += 3;
			tmp_wheel_angle.second += 3;
			game->getPlayer()->setWheelAngle(tmp_wheel_angle);

			game->set_player_translation(tmp_translation);
		}
		break;

	case GLUT_KEY_DOWN:
		tmp_translation = game->get_player_translation();
		tmp_angle = get<0>(game->get_player_rotation());

		get<2>(tmp_translation) += 0.2 * cos(tmp_angle / 180 * 3.142);
		get<0>(tmp_translation) += 0.2 * sin(tmp_angle / 180 * 3.142);

		if (!game->checkBoundaryCollision(game->getPlayerTankBound(tmp_translation)) && !game->checkTankCollision(game->getPlayerTankBound(tmp_translation), game->getEnemyTankBound(game->get_enemy_translation())))
		{
			tmp_wheel_angle = game->getPlayer()->getWheelAngle();
			tmp_wheel_angle.first -= 3;
			tmp_wheel_angle.second -= 3;
			game->getPlayer()->setWheelAngle(tmp_wheel_angle);

			game->set_player_translation(tmp_translation);
		}
		break;

	case GLUT_KEY_LEFT:
		tmp_rotation = game->get_player_rotation();
		get<0>(tmp_rotation) += 0.5;

		tmp_wheel_angle = game->getPlayer()->getWheelAngle();
		tmp_wheel_angle.first -= 3;
		tmp_wheel_angle.second += 3;
		game->getPlayer()->setWheelAngle(tmp_wheel_angle);

		game->set_player_rotation(tmp_rotation);
		break;

	case GLUT_KEY_RIGHT:
		tmp_rotation = game->get_player_rotation();
		get<0>(tmp_rotation) -= 0.5;

		tmp_wheel_angle = game->getPlayer()->getWheelAngle();
		tmp_wheel_angle.first += 3;
		tmp_wheel_angle.second -= 3;
		game->getPlayer()->setWheelAngle(tmp_wheel_angle);

		game->set_player_rotation(tmp_rotation);
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
	glutDisplayFunc(tempDisplay);
	glutIdleFunc(idle);
	glutTimerFunc(1000, actionTimer, 1);
	glutTimerFunc(3000, shootTimer, 1);

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);

	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glewInit();

	initShader();

	glutMainLoop();
}