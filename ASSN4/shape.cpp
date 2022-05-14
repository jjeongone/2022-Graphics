#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "shape.h"


void shape::Body::setShader()
{
	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * body_vertices_merge.size(), &body_vertices_merge[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void shape::Body::draw()
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	glBindVertexArray(0);
}

void shape::Head::draw()
{
	setShader();

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
	glBindVertexArray(0);
}

void shape::Barrel::draw()
{
	setShader();

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

	glBindVertexArray(0);
}

void shape::Wheel::draw()
{
	setShader();

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
	for (GLfloat i = -length; i <= length; i += gap) {
		vertices.push_back(i);
		vertices.push_back(depth);
		vertices.push_back(length);

		vertices.push_back(i);
		vertices.push_back(depth);
		vertices.push_back(-length);

		vertices.push_back(length);
		vertices.push_back(depth);
		vertices.push_back(i);

		vertices.push_back(-length);
		vertices.push_back(depth);
		vertices.push_back(i);

		vertices.push_back(i);
		vertices.push_back(depth);
		vertices.push_back(length);

		vertices.push_back(length);
		vertices.push_back(depth);
		vertices.push_back(i);

		vertices.push_back(i);
		vertices.push_back(depth);
		vertices.push_back(-length);

		vertices.push_back(-length);
		vertices.push_back(depth);
		vertices.push_back(i);
	}

	glUseProgram(shader_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void shape::Plane::draw_plane(bool fill)
{
	setShader();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
	glDrawArrays(GL_LINES, 0, vertices.size() / 3);
	glBindVertexArray(0);
}

void shape::Shape::set_color(tuple<float, float, float> color)
{
	colorRGB = color;
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
	glBindVertexArray(0);
}

void shape::WheelRight::draw()
{
	setShader();

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
