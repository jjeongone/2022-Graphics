#include "Light.h"

Light::Light()
{
}

Light::Light(glm::vec3 a, glm::vec3 d, glm::vec3 s)
{
	ambient = a;
	diffuse = d;
	specular = s;
}

void Light::setPosition(glm::vec3 pos)
{
	position = pos;
}

DirectionalLight::DirectionalLight(glm::vec3 a, glm::vec3 d, glm::vec3 s)
{
	ambient = a;
}

void DirectionalLight::move()
{
}

PointLight::PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s)
{
	position = p;
	ambient = a;
	diffuse = d;
	specular = s;
}
