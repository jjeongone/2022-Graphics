#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "shape.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int width, height, nrChannels;
unsigned char* texture_data = stbi_load("./model/centauro/textures/MaterialBaseColor.png", &width, &height, &nrChannels, 0);
int width_ground, height_ground, nrChannels_ground;
unsigned char* texture_ground = stbi_load("./model/Ground_Dirt_009_BaseColor.jpg", &width_ground, &height_ground, &nrChannels_ground, 0);

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

shape::Body::Body()
{
	Loader* body = new Loader("./model/centauro/source/body.obj");
	body_vertices_merge = body->merge();
	delete body;
}

void shape::Body::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * body_vertices_merge.size(), &body_vertices_merge[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	
	if (texture_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);
	
}

void shape::Body::draw()
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, body_vertices_merge.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, body_vertices_merge.size() / 3);
		glBindVertexArray(0);
	}
}

shape::Head::Head()
{
	Loader* head = new Loader("./model/centauro/source/head.obj");
	head_vertices_merge = head->merge();
	delete head;
}

void shape::Head::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * head_vertices_merge.size(), &head_vertices_merge[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	if (texture_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);
}

void shape::Head::draw()
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, head_vertices_merge.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, head_vertices_merge.size() / 3);
		glBindVertexArray(0);
	}
}

shape::Barrel::Barrel()
{
	Loader* barrel = new Loader("./model/centauro/source/barrel.obj");
	barrel_vertices_merge = barrel->merge();
	delete barrel;
}

void shape::Barrel::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * barrel_vertices_merge.size(), &barrel_vertices_merge[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	if (texture_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);
}

void shape::Barrel::draw()
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, barrel_vertices_merge.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, barrel_vertices_merge.size() / 3);
		glBindVertexArray(0);
	}
}

shape::Wheel::Wheel()
{
	Loader* wheel = new Loader("./model/centauro/source/wheel.obj");
	wheel_vertices_merge = wheel->merge();
	delete wheel;
}

void shape::Wheel::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * wheel_vertices_merge.size(), &wheel_vertices_merge[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//glBindVertexArray(0);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	if (texture_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);
}

void shape::Wheel::draw()
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, wheel_vertices_merge.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, wheel_vertices_merge.size() / 3);
		glBindVertexArray(0);
	}
}

void shape::Plane::set_condition(float l, float g, float d)
{
	length = l;
	gap = g;
	depth = d;
}

void shape::Plane::setShader()
{
	vertices.clear();
	for (GLfloat i = -length; i + gap <= length; i += gap) {
		for (GLfloat j = -length; j + gap <= length; j += gap)
		{
			vertices.push_back(i + gap);
			vertices.push_back(depth);
			vertices.push_back(j);
			vertices.push_back((i + gap + length) / (2 * length));
			vertices.push_back((j + length) / (2 * length));

			vertices.push_back(i);
			vertices.push_back(depth);
			vertices.push_back(j);
			vertices.push_back((i + length) / (2 * length));
			vertices.push_back((j + length) / (2 * length));

			vertices.push_back(i);
			vertices.push_back(depth);
			vertices.push_back(j + gap);
			vertices.push_back((i + length) / (2 * length));
			vertices.push_back((j + gap + length) / (2 * length));

			vertices.push_back(i + gap);
			vertices.push_back(depth);
			vertices.push_back(j);
			vertices.push_back((i + gap + length) / (2 * length));
			vertices.push_back((j + length) / (2 * length));

			vertices.push_back(i);
			vertices.push_back(depth);
			vertices.push_back(j + gap);
			vertices.push_back((i + length) / (2 * length));
			vertices.push_back((j + gap + length) / (2 * length));

			vertices.push_back(i + gap);
			vertices.push_back(depth);
			vertices.push_back(j + gap);
			vertices.push_back((i + gap + length) / (2 * length));
			vertices.push_back((j + gap + length) / (2 * length));
		}
	}

	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	if (texture_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_ground);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
}

void shape::Plane::draw_plane(bool fill)
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		glBindVertexArray(0);
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
	//glDrawArrays(GL_LINES, 0, vertices.size() / 3);
	//glBindVertexArray(0);
}

void shape::Shape::set_color(tuple<float, float, float> color)
{
	colorRGB = color;
}

shape::WheelRight::WheelRight()
{
	Loader* wheel_right = new Loader("./model/centauro/source/wheel_right.obj");
	wheel_vertices_merge = wheel_right->merge();
	delete wheel_right;
}

void shape::WheelRight::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * wheel_vertices_merge.size(), &wheel_vertices_merge[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//glBindVertexArray(0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture

	if (texture_data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_image_free(data);
}

void shape::WheelRight::draw()
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, wheel_vertices_merge.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, wheel_vertices_merge.size() / 3);
		glBindVertexArray(0);
	}
}
