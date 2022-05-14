#include "game.h"

void printText(float r, float g, float b, float x, float y, std::string text) {
	int i;
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (i = 0; i < text.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
	}
}

std::string getModeName(bool auto_mode, enum mode m) {
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

	player = new Tank(make_tuple(0, 0, 0), 0.7f, make_tuple(1.f, 1.f, 1.f), 30. / 180 * 3.142, 3, 1, false);
	enemy = new Tank(make_tuple(0, 0, 0), 0.7f, make_tuple(2.2f, 0.2f, 2.0f), 30. / 180 * 3.142, 3, -1, true);
	enemyList.push_back(*enemy);

	ground.set_color(make_tuple(0.3f, 0.3f, 0.3f));
	ground.set_condition(180.0f, 10.0f, -0.0003f);
	ground_node.translate = make_tuple(0., 0., 0.);
	ground_node.rotate = make_tuple(0., 0., 0., 0.);
	ground_node.part = &ground;
	ground_node.draw = &shape::Plane::draw_plane;

	boundary.set_color(make_tuple(0.0f, 0.25f, 1.0f));
	boundary.set_condition(60.0f, 10.0f, 0.0f);
}

mode Game::getMode()
{
	return mode;
}

void Game::changeMode(enum mode m)
{
	mode = m;

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
		enemy->setHealth(3);
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

	printText(0.0, 0.0, 0.0, x - 0.17, y, "<Fortress>");
	printText(0.0, 0.0, 0.0, x - 0.3, y -= 0.1, "Press ENTER to play");
	printText(0.0, 0.0, 0.0, x - 0.3, y -= 0.3, "developed by DimSum");
}

void Game::printGameOver()
{
	float x = -0.2;
	float y = 0.0;

	printText(0.9, 0.0, 0.0, x, y, "GAME OVER...");
}

void Game::printWin()
{
	float x = -0.1;
	float y = 0.0;

	printText(0.0, 0.0, 0.9, x, y, "WIN!!!");
}

void Game::printStatus()
{
	float x = -3.2;
	float y = 35.0;

	string player_mode = auto_mode ? "(AUTO)" : "";

	printText(0.0, 0.0, 0.0, x, y, "Player" + player_mode);
	printText(0.0, 0.0, 0.0, x, y-0.1, "HP: " + std::to_string(player->getHealth()));

	printText(0.0, 0.0, 0.0, 2.3, y, "Mode: " + getModeName(auto_mode, mode));
}

void Game::display()
{
	camera->look_at();
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT, GL_LINE);
	drawWorld(false);

	if (render_mode) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		drawWorld(true);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
}

void Game::drawWorld(bool fill)
{
	treenode<shape::Plane> boundary_node;
	treenode<Tank> player_node;
	treenode<Tank> enemy_node;

	boundary_node.part = &boundary;
	boundary_node.draw = &shape::Plane::draw_plane;
	ground_node.child = &boundary_node;

	player_node.part = player;
	player_node.draw = &Tank::draw_tank;
	player_node.translate = player_translation;
	player_node.rotate = player_rotation;
	boundary_node.sibling = reinterpret_cast<treenode<shape::Plane>*>(&player_node);

	enemy_node.part = enemy;
	enemy_node.draw = &Tank::draw_tank;
	enemy_node.translate = enemy_translation;
	enemy_node.rotate = enemy_rotation;
	player_node.sibling = &enemy_node;

	model_view_matrix = glm::mat4(1.0f);
	display(&ground_node, fill);
}

template<class T>
void Game::display(treenode<T>* node, bool fill)
{
	if (node == nullptr)
	{
		return;
	}
	model_view.push(model_view_matrix);
	model_view_matrix = glm::translate(model_view_matrix, glm::vec3(get<0>(node->translate), get<1>(node->translate), get<2>(node->translate)));
	if (!(get<1>(node->rotate) == 0 && get<2>(node->rotate) == 0 && get<3>(node->rotate) == 0))
		model_view_matrix = glm::rotate(model_view_matrix, glm::radians(get<0>(node->rotate)), glm::vec3(get<1>(node->rotate), get<2>(node->rotate), get<3>(node->rotate)));
	glUseProgram(shader_program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "Model"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

	if (node->child != nullptr)
	{
		display(node->child, fill);
	}
	node->draw(*(node->part), fill);

	model_view_matrix = model_view.top();
	glUseProgram(shader_program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "Model"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));
	model_view.pop();

	if (node->sibling != nullptr)
	{
		display(node->sibling, fill);
	}
}

Tank* Game::getPlayer()
{
	return this->player;
}

Tank * Game::getEnemy()
{
	return this->enemy;
}

status Game::getStatus()
{
	return status;
}

void Game::setStatus(enum status s)
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

void Game::enemyAction()
{
	std::srand(time(NULL));
	float barrel_angle = enemy->getBarrelAngle();
	float head_angle = enemy->getHeadAngle();
	float speed = enemy->getBulletSpeed();

	tuple<float, float, float> tmp_translation;
	tuple<float, float, float, float> tmp_rotation;
	float tmp_angle;
	pair<float, float> tmp_wheel_angle;
	
	switch (std::rand() % 20) {
	case 0: // move forward
		tmp_translation = enemy_translation;
		tmp_angle = get<0>(enemy_rotation);
		get<2>(tmp_translation) -= 0.2 * cos(tmp_angle / 180 * 3.142);
		get<0>(tmp_translation) -= 0.2 * sin(tmp_angle / 180 * 3.142);

		if (!checkBoundaryCollision(getEnemyTankBound(tmp_translation)) && !checkTankCollision(getPlayerTankBound(get_player_translation()), getEnemyTankBound(tmp_translation)))
		{
			tmp_wheel_angle = enemy->getWheelAngle();
			tmp_wheel_angle.first += 3;
			tmp_wheel_angle.second += 3;
			enemy->setWheelAngle(tmp_wheel_angle);

			enemy_translation = tmp_translation;
		}
		break;

	case 1: // move backward
		tmp_translation = enemy_translation;
		tmp_angle = get<0>(enemy_rotation);
		get<2>(tmp_translation) += 0.2 * cos(tmp_angle / 180 * 3.142);
		get<0>(tmp_translation) += 0.2 * sin(tmp_angle / 180 * 3.142);

		if (!checkBoundaryCollision(getEnemyTankBound(tmp_translation)) && !checkTankCollision(getPlayerTankBound(get_player_translation()), getEnemyTankBound(tmp_translation)))
		{
			tmp_wheel_angle = enemy->getWheelAngle();
			tmp_wheel_angle.first -= 3;
			tmp_wheel_angle.second -= 3;
			enemy->setWheelAngle(tmp_wheel_angle);

			enemy_translation = tmp_translation;
		}
		break;

	case 2: // rotate right
		tmp_rotation = enemy_rotation;
		get<0>(tmp_rotation) += 0.5;

		tmp_wheel_angle = enemy->getWheelAngle();
		tmp_wheel_angle.first -= 3;
		tmp_wheel_angle.second += 3;
		enemy->setWheelAngle(tmp_wheel_angle);

		enemy_rotation = tmp_rotation;
		break;

	case 3: // rotate left
		tmp_rotation = enemy_rotation;
		get<0>(tmp_rotation) -= 0.5;

		tmp_wheel_angle = enemy->getWheelAngle();
		tmp_wheel_angle.first += 3;
		tmp_wheel_angle.second -= 3;
		enemy->setWheelAngle(tmp_wheel_angle);

		enemy_rotation = tmp_rotation;
		break;

	case 6: // barrel up
		if (barrel_angle - 0.5 >= -30.)
			barrel_angle -= 0.5;

		enemy->setBarrel(barrel_angle);
		break;

	case 7: // barrel down
		if (barrel_angle + 0.5 <= 0)
			barrel_angle += 0.5;

		enemy->setBarrel(barrel_angle);
		break;

	case 8: // head left
		if (head_angle + 1. <= 90.)
			head_angle += 1.;

		enemy->setHead(head_angle);
		break;

	case 9: // head right
		if (head_angle - 1. >= -90.)
			head_angle -= 1.;

		enemy->setHead(head_angle);
		break;

	case 10: // bullet speed up
		if (speed - 0.2 >= -2)
			speed -= 0.2;

		enemy->setBulletSpeed(speed);
		break;

	case 11: // bullet speed down
		if (speed + 0.2 <= -0.2)
			speed += 0.2;

		enemy->setBulletSpeed(speed);
		break;

	default: // do nothing
		break;
	}
}

void Game::recoil(float speed)
{
	float power = speed / 2;
}

void Game::setRenderMode()
{
	render_mode = !render_mode;
}

bool Game::getRenderMode()
{
	return render_mode;
}

tuple<float, float, float> Game::get_player_translation()
{
	return player_translation;
}

tuple<float, float, float> Game::get_enemy_translation()
{
	return enemy_translation;
}

tuple<float, float, float, float> Game::get_player_rotation()
{
	return player_rotation;
}

tuple<float, float, float, float> Game::get_enemy_rotation()
{
	return enemy_rotation;
}

void Game::set_player_translation(tuple<float, float, float> new_translation)
{
	player_translation = new_translation;
}

void Game::set_enemy_translation(tuple<float, float, float> new_translation)
{
	enemy_translation = new_translation;
}

void Game::set_player_rotation(tuple<float, float, float, float> new_rotation)
{
	player_rotation = new_rotation;
}

void Game::set_enemy_rotation(tuple<float, float, float, float> new_rotation)
{
	enemy_rotation = new_rotation;
}

glm::mat4 Game::getPlayerTankBarrelPosition()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(get<0>(player->getCoordinate()), get<1>(player->getCoordinate()), get<2>(player->getCoordinate())));
	matrix = glm::translate(matrix, glm::vec3(get<0>(player_translation), get<1>(player_translation), get<2>(player_translation)));
	matrix = glm::rotate(matrix, glm::radians(get<0>(player_rotation)), glm::vec3(get<1>(player_rotation), get<2>(player_rotation), get<3>(player_rotation)));
	matrix = glm::translate(matrix, glm::vec3(0.3, 2.5, -1.97));
	matrix = glm::translate(matrix, glm::vec3(0, 0, 4));
	matrix = glm::rotate(matrix, glm::radians(player->getHeadAngle()), glm::vec3(0., 1., 0.));
	matrix = glm::rotate(matrix, glm::radians(-player->getBarrelAngle()), glm::vec3(1., 0., 0.));
	matrix = glm::translate(matrix, glm::vec3(0, 6., -16.));

	return matrix;
}

glm::mat4 Game::getPlayerTankPosition()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(get<0>(player_translation), get<1>(player_translation), get<2>(player_translation)));
	matrix = glm::rotate(matrix, glm::radians(get<0>(player_rotation)), glm::vec3(get<1>(player_rotation), get<2>(player_rotation), get<3>(player_rotation)));
	matrix = glm::translate(matrix, glm::vec3(-0.3, 2.5, -1.97));

	return matrix;
}

glm::mat4 Game::getEnemyTankPosition()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(get<0>(enemy_translation), get<1>(enemy_translation), get<2>(enemy_translation)));
	matrix = glm::rotate(matrix, glm::radians(get<0>(enemy_rotation)), glm::vec3(get<1>(enemy_rotation), get<2>(enemy_rotation), get<3>(enemy_rotation)));
	matrix = glm::translate(matrix, glm::vec3(-0.3, 2.5, -1.97));

	return matrix;
}

pair<glm::vec3, glm::vec3> Game::getPlayerTankBound(tuple<float, float, float> t)
{
	glm::vec3 tank_coord(get<0>(t), get<1>(t), get<2>(t));

	return make_pair(glm::vec3(tank_coord.x - 9., tank_coord.y - 4., tank_coord.z - 9.), glm::vec3(tank_coord.x + 9., tank_coord.y + 4., tank_coord.z + 9.));
}

pair<glm::vec3, glm::vec3> Game::getEnemyTankBound(tuple<float, float, float> t)
{
	glm::vec3 tank_coord(get<0>(t), get<1>(t), get<2>(t));

	return make_pair(glm::vec3(tank_coord.x - 9., tank_coord.y - 4., tank_coord.z - 9.), glm::vec3(tank_coord.x + 9., tank_coord.y + 4., tank_coord.z + 9.));
}

bool Game::checkTankCollision(pair<glm::vec3, glm::vec3> playerBound, pair<glm::vec3, glm::vec3> enemyBound)
{
	// Tank-to-tank Collision Check
	if ((playerBound.first.x <= enemyBound.first.x && playerBound.second.x >= enemyBound.first.x) && (playerBound.first.z <= enemyBound.first.z && playerBound.second.z >= enemyBound.first.z))
		return true;
	else if ((playerBound.first.x <= enemyBound.first.x && playerBound.second.x >= enemyBound.first.x) && (playerBound.first.z <= enemyBound.second.z && playerBound.second.z >= enemyBound.second.z))
		return true;
	else if ((playerBound.first.x <= enemyBound.second.x && playerBound.second.x >= enemyBound.second.x) && (playerBound.first.z <= enemyBound.first.z && playerBound.second.z >= enemyBound.first.z))
		return true;
	else if ((playerBound.first.x <= enemyBound.second.x && playerBound.second.x >= enemyBound.second.x) && (playerBound.first.z <= enemyBound.second.z && playerBound.second.z >= enemyBound.second.z))
		return true;
	else
		return false;
}

bool Game::checkBoundaryCollision(pair<glm::vec3, glm::vec3> bound)
{
	// Tank-to-tank Collision Check
	if (bound.first.x <= -60.f)
		return true;
	else if (bound.second.x >= 60.f)
		return true;
	else if (bound.first.z <= -60.f)
		return true;
	else if (bound.second.z >= 60.f)
		return true;
	else
		return false;
}
