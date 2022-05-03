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
	/*if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	
	for (int i = 0; i < body_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(body_vertices[i].x, body_vertices[i].y, body_vertices[i].z);
		glVertex3f(body_vertices[i + 1].x, body_vertices[i + 1].y, body_vertices[i + 1].z);
		glVertex3f(body_vertices[i + 2].x, body_vertices[i + 2].y, body_vertices[i + 2].z);
		glEnd();
	}*/
	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(body_vertices_merge), &body_vertices_merge.front(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//glUseProgram(shader_program);
	//glBindVertexArray(VAO);
	//if (fill)
	//	glDrawArrays(GL_TRIANGLES, 0, sizeof(body_vertices_merge));
	//else
	//	glDrawArrays(GL_LINE_LOOP, 0, sizeof(body_vertices_merge));

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//glBindVertexArray(0);
	setShader();

	if (fill) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0, 5.0);
		glDrawArrays(GL_TRIANGLES, 0, body_vertices_merge.size() / 3);
		glBindVertexArray(0);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUniform4f(glGetUniformLocation(shader_program, "color"), 0, 0, 0, 1.0f);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, body_vertices_merge.size() / 3);
	glBindVertexArray(0);

	glFlush();
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

	//if (fill)
	//	glColor3f(0.8f, 0.8f, 0.8f);
	//else
	//	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	//for (int i = 0; i < head_vertices.size(); i += 3) {
	//	glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
	//	glVertex3f(head_vertices[i].x, head_vertices[i].y, head_vertices[i].z);
	//	glVertex3f(head_vertices[i + 1].x, head_vertices[i + 1].y, head_vertices[i + 1].z);
	//	glVertex3f(head_vertices[i + 2].x, head_vertices[i + 2].y, head_vertices[i + 2].z);
	//	glEnd();
	//}

	//shader.use();
	/*if (fill)
		shader.setVec4("color", 0.8f, 0.8f, 0.8f, 1.0f);
	else
		shader.setVec4("color", get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);*/

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(head_vertices_merge), &head_vertices_merge.front(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//glUseProgram(shader_program);
	//glBindVertexArray(VAO);
	//if (fill)
	//	glDrawArrays(GL_TRIANGLES, 0, sizeof(head_vertices_merge));
	//else
	//	glDrawArrays(GL_LINE_LOOP, 0, sizeof(head_vertices_merge));

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//glBindVertexArray(0);
	
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
	//if (fill)
	//	glColor3f(0.8f, 0.8f, 0.8f);
	//else
	//	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	//for (int i = 0; i < barrel_vertices.size(); i += 3) {
	//	glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
	//	glVertex3f(barrel_vertices[i].x, barrel_vertices[i].y, barrel_vertices[i].z);
	//	glVertex3f(barrel_vertices[i + 1].x, barrel_vertices[i + 1].y, barrel_vertices[i + 1].z);
	//	glVertex3f(barrel_vertices[i + 2].x, barrel_vertices[i + 2].y, barrel_vertices[i + 2].z);
	//	glEnd();
	//}

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(barrel_vertices_merge), &barrel_vertices_merge.front(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//glUseProgram(shader_program);
	//glBindVertexArray(VAO);
	//if (fill)
	//	glDrawArrays(GL_TRIANGLES, 0, sizeof(barrel_vertices_merge));
	//else
	//	glDrawArrays(GL_LINE_LOOP, 0, sizeof(barrel_vertices_merge));

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//glBindVertexArray(0);

	//int vertex_color_location = glGetUniformLocation(shader_program, "color");
	//glUseProgram(shader_program);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(VAO);

	//if (fill) {
	//	glPolygonMode(GL_FRONT, GL_FILL);
	//	glUniform4f(vertex_color_location, 0.8f, 0.8f, 0.8f, 1.0f);
	//	glEnable(GL_POLYGON_OFFSET_FILL);
	//	glPolygonOffset(1.0, 5.0);
	//	glDrawArrays(GL_TRIANGLES, 0, bullet_vertices.size() / 3);
	//	glBindVertexArray(0);
	//	glDisable(GL_POLYGON_OFFSET_FILL);
	//}
	//else {
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	glUniform4f(vertex_color_location, 0.0f, 0.0f, 0.0f, 1.0f);
	//	glDrawArrays(GL_TRIANGLES, 0, bullet_vertices.size() / 3);
	//	glBindVertexArray(0);
	//}
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
	/*if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	for (int i = 0; i < wheel_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(wheel_vertices[i].x, wheel_vertices[i].y, wheel_vertices[i].z);
		glVertex3f(wheel_vertices[i + 1].x, wheel_vertices[i + 1].y, wheel_vertices[i + 1].z);
		glVertex3f(wheel_vertices[i + 2].x, wheel_vertices[i + 2].y, wheel_vertices[i + 2].z);
		glEnd();
	}*/
	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(wheel_vertices_merge), &wheel_vertices_merge.front(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//glUseProgram(shader_program);
	//glBindVertexArray(VAO);
	//if (fill)
	//	glDrawArrays(GL_TRIANGLES, 0, sizeof(wheel_vertices_merge));
	//else
	//	glDrawArrays(GL_LINE_LOOP, 0, sizeof(wheel_vertices_merge));

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//glBindVertexArray(0);
}

void shape::Plane::set_condition(float l, float g, float d)
{
	length = l;
	gap = g;
	depth = d;
}

void shape::Plane::draw_plane(bool fill)
{
	vector<float> vertices;
	/*glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	glBegin(GL_LINES);*/
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

		/*glVertex3f(i, depth, length);
		glVertex3f(i, depth, -length);
		glVertex3f(length, depth, i);
		glVertex3f(-length, depth, i);
		glVertex3f(i, depth, length);
		glVertex3f(length, depth, i);
		glVertex3f(i, depth, -length);
		glVertex3f(-length, depth, i);*/
	}
	//glEnd();

	

	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices.front(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//glUseProgram(shader_program);
	//glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_LINES, 0, sizeof(vertices));

	//glBindVertexArray(0);
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
	/*if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	for (int i = 0; i < wheel_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(wheel_vertices[i].x, wheel_vertices[i].y, wheel_vertices[i].z);
		glVertex3f(wheel_vertices[i + 1].x, wheel_vertices[i + 1].y, wheel_vertices[i + 1].z);
		glVertex3f(wheel_vertices[i + 2].x, wheel_vertices[i + 2].y, wheel_vertices[i + 2].z);
		glEnd();
	}*/


	//unsigned int VAO, VBO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(wheel_vertices_merge), &wheel_vertices_merge.front(), GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//glUseProgram(shader_program);
	//glBindVertexArray(VAO);
	//if (fill)
	//	glDrawArrays(GL_TRIANGLES, 0, sizeof(wheel_vertices_merge));
	//else
	//	glDrawArrays(GL_LINE_LOOP, 0, sizeof(wheel_vertices_merge));

	//if (fill)
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), 0.8f, 0.8f, 0.8f, 1.0f);
	//else
	//	glUniform4f(glGetUniformLocation(shader_program, "color"), get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB), 1.0f);

	//glBindVertexArray(0);
}
