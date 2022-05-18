#include "bullet.h"

Bullet::Bullet() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;

	light = new light::PointLight(glm::vec3(x, y+2.0f, z), glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.9, 0.9, 0.9), glm::vec3(1.0, 1.0, 1.0), 8.0);
}


Bullet::Bullet(tuple<float, float, float> coordinate, tuple<float, float, float> translation, tuple<float, float, float, float> rotation, float head, float barrel, float s)
{
	tank_coordinate = coordinate;
	tank_translation = translation;
	tank_rotation = rotation;
	head_angle = head;
	barrel_angle = barrel;
	speed = s;
	y_speed = s * tan(-barrel / 180 * 3.142);

	glm::vec4 bullet_pos = cal_transformation() * glm::vec4(0, 0, 0, 1);
	x = bullet_pos.x;
	y = bullet_pos.y;
	z = bullet_pos.z;

	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * bullet_vertices.size(), &bullet_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	light = new light::PointLight(glm::vec3(x, y + 2.0f, z), glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.7, 0.7, 0.7), 16.0);
}

std::tuple<float, float, float> Bullet::position() {
	return std::tuple<float, float, float>(x, y, z);
}

glm::mat4 Bullet::cal_transformation()
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, glm::vec3(get<0>(tank_coordinate), get<1>(tank_coordinate), get<2>(tank_coordinate)));
	matrix = glm::translate(matrix, glm::vec3(get<0>(tank_translation), get<1>(tank_translation), get<2>(tank_translation)));
	matrix = glm::rotate(matrix, glm::radians(get<0>(tank_rotation)), glm::vec3(get<1>(tank_rotation), get<2>(tank_rotation), get<3>(tank_rotation)));
	matrix = glm::translate(matrix, glm::vec3(0., 2.5, -1.97));
	matrix = glm::translate(matrix, glm::vec3(0, 0, 4));
	matrix = glm::rotate(matrix, glm::radians(head_angle), glm::vec3(0., 1., 0.));
	matrix = glm::rotate(matrix, glm::radians(-barrel_angle), glm::vec3(1., 0., 0.));
	matrix = glm::translate(matrix, glm::vec3(0, 6., bullet_position));

	return matrix;
}

void Bullet::move() {
	bullet_position -= speed;
	y_speed -= 0.02;
	cout << y_speed << endl;

	glm::vec4 bullet_pos = cal_transformation() * glm::vec4(0, 0, 0, 1);

	x = bullet_pos.x;
	y += y_speed;
	z = bullet_pos.z;

	light->setPosition(glm::vec3(x, y + 2.0, z));
}

void Bullet::draw_bullet(bool fill, light::DirectionalLight* gameLight) {
	setShader();

	glm::vec3 light_position = light->getPosition();
	glm::vec3 ambiend = light->getAmbient();
	glm::vec3 diffuse = light->getDiffuse();
	glm::vec3 specular = light->getSpecular();
	float shininess = light->getShininess();

	glm::vec3 game_light_position = gameLight->getPosition();
	glm::vec3 game_ambiend = gameLight->getAmbient();
	glm::vec3 game_diffuse = gameLight->getDiffuse();
	glm::vec3 game_specular = gameLight->getSpecular();
	float game_shininess = gameLight->getShininess();

	model_view.push(model_view_matrix);
	model_view_matrix = glm::translate(model_view_matrix, glm::vec3(x, y, z));
	glUseProgram(shader_program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "Model"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));

	glUniform4f(glGetUniformLocation(shader_program, "LightPosition"), game_light_position.x, game_light_position.y, game_light_position.z, 1.0f);
	glUniform4f(glGetUniformLocation(shader_program, "AmbientProduct"), game_ambiend.x, game_ambiend.y, game_ambiend.z, 1.0f);
	glUniform4f(glGetUniformLocation(shader_program, "DiffuseProduct"), game_diffuse.x, game_diffuse.y, game_diffuse.z, 1.0f);
	glUniform4f(glGetUniformLocation(shader_program, "SpecularProduct"), game_specular.x, game_specular.y, game_specular.z, 1.0f);
	glUniform1f(glGetUniformLocation(shader_program, "Shininess"), game_shininess);

	glUniform4f(glGetUniformLocation(shader_program, "PointLightPosition"), light_position.x, light_position.y, light_position.z, 1.0f);
	glUniform4f(glGetUniformLocation(shader_program, "PointAmbientProduct"), ambiend.x, ambiend.y, ambiend.z, 1.0f);
	glUniform4f(glGetUniformLocation(shader_program, "PointDiffuseProduct"), diffuse.x, diffuse.y, diffuse.z, 1.0f);
	glUniform4f(glGetUniformLocation(shader_program, "PointSpecularProduct"), specular.x, specular.y, specular.z, 1.0f);
	glUniform1f(glGetUniformLocation(shader_program, "PointShininess"), shininess);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "Color"), 0.2f, 0.2f, 0.2f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, bullet_vertices.size()/3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "Color"), 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, bullet_vertices.size()/3);
		glBindVertexArray(0);
	}

	model_view_matrix = model_view.top();
	glUseProgram(shader_program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "Model"), 1, GL_FALSE, glm::value_ptr(model_view_matrix));
	model_view.pop();
}

void Bullet::changeSpeed() {
	y_speed -= GRAVITY;
}

bool Bullet::isExplode(Tank* player, pair<glm::vec3, glm::vec3> player_bound, Tank* enemy, pair<glm::vec3, glm::vec3> enemy_bound) {
	if (y < player_bound.second.y && (x > player_bound.first.x && x < player_bound.second.x) && (z > player_bound.first.z && z < player_bound.second.z))
	{
		player->setHealth(player->getHealth() - 1);
		return true;
	}
	else if (y < enemy_bound.second.y && (x > enemy_bound.first.x && x < enemy_bound.second.x) && (z > enemy_bound.first.z && z < enemy_bound.second.z))
	{
		enemy->setHealth(enemy->getHealth() - 1);
		return true;
	}
	else if (y < 0)
	{
		return true;
	}
	return false;
}

void Bullet::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bullet_vertices.size(), &bullet_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

glm::vec3 Bullet::getPosition()
{
	return glm::vec3(x, y, z);
}
