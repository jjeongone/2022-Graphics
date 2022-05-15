#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light {
private:

protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
public:
	Light();
	Light(glm::vec3 a, glm::vec3 d, glm::vec3 s);
	void setPosition(glm::vec3 pos);
};

class DirectionalLight : public Light {
private:
public:
	DirectionalLight(glm::vec3 a, glm::vec3 d, glm::vec3 s);
	void move();
};

class PointLight : public Light {
private:
public:
	PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s);
};
