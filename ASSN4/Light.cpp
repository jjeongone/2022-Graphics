#include "Light.h"

light::Light::Light()
{

}

light::Light::Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shine)
{
	position = glm::vec3(0.0, 0.0, 0.0);
	ambient = a;
	diffuse = d;
	specular = s;
	shininess = shine;
}

void light::Light::setPosition(glm::vec3 pos)
{
	position = pos;
}

glm::vec3 light::Light::getPosition()
{
	return position;
}

glm::vec3 light::Light::getAmbient()
{
	return ambient;
}

glm::vec3 light::Light::getDiffuse()
{
	return diffuse;
}

glm::vec3 light::Light::getSpecular()
{
	return specular;
}

float light::Light::getShininess()
{
	return shininess;
}

light::DirectionalLight::DirectionalLight(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shine)
{
	position = glm::vec3(-180.0f, 0.0f, 90.0f);
	ambient = a;
	diffuse = d;
	specular = s;
	shininess = shine;

	x_speed = 10.0;
	y_speed = 15.0;
	
	y_max = 80.0;
}

void light::DirectionalLight::move()
{
	position.x = position.x + x_speed;
	position.y = position.y + y_speed;

	if (position.x == 0) {
		y_speed = -y_speed;
	}
	else if (position.x >= 180) {
		y_speed = -y_speed;
		x_speed = -x_speed;
	}
	else if (position.x <= -180) {
		y_speed = -y_speed;
		x_speed = -x_speed;
	}
}

light::PointLight::PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s, float shine)
{
	position = p;
	ambient = a;
	diffuse = d;
	specular = s;
	shininess = shine;
}

void light::PointLight::move(glm::vec3 bullet_pos)
{
	position = bullet_pos;
}
