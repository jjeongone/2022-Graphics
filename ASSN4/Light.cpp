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
	ambient = a;
	diffuse = d;
	specular = s;
	shininess = shine;

	x_speed = 5.0;
	y_speed = 8.0;
	
	y_max = 80.0;
}

void light::DirectionalLight::move()
{
	position.x = position.x + x_speed;
	position.y = position.y + y_speed;
	if ((position.y >= 80 && x_speed > 0) || position.y >= 80 && x_speed < 0) {
		y_speed = -y_speed;
	}

	if ((position.y == 0 && x_speed > 0) || (position.y == 0 && x_speed < 0)) {
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
