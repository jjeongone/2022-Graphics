#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace light {
	class Light {
	private:

	protected:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		glm::vec3 position;
		float shininess;
	public:
		Light();
		Light(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shine);
		void setPosition(glm::vec3 pos);
		glm::vec3 getPosition();
		glm::vec3 getAmbient();
		glm::vec3 getDiffuse();
		glm::vec3 getSpecular();
		float getShininess();
	};

	class DirectionalLight : public Light {
	private:
		float x_speed;
		float y_speed;
		float y_max;
	public:
		DirectionalLight(glm::vec3 a, glm::vec3 d, glm::vec3 s, float shine);
		void move();
	};

	class PointLight : public Light {
	private:
	public:
		PointLight(glm::vec3 p, glm::vec3 a, glm::vec3 d, glm::vec3 s, float shine);
		void move(glm::vec3 bullet_pos);
	};
}
