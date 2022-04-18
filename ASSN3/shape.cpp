#include "shape.h"


void shape::Body::draw()
{
	if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	
	for (int i = 0; i < body_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(body_vertices[i].x, body_vertices[i].y, body_vertices[i].z);
		glVertex3f(body_vertices[i + 1].x, body_vertices[i + 1].y, body_vertices[i + 1].z);
		glVertex3f(body_vertices[i + 2].x, body_vertices[i + 2].y, body_vertices[i + 2].z);
		glEnd();
	}
}

void shape::Head::draw()
{
	if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	for (int i = 0; i < head_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(head_vertices[i].x, head_vertices[i].y, head_vertices[i].z);
		glVertex3f(head_vertices[i + 1].x, head_vertices[i + 1].y, head_vertices[i + 1].z);
		glVertex3f(head_vertices[i + 2].x, head_vertices[i + 2].y, head_vertices[i + 2].z);
		glEnd();
	}
	
}

void shape::Barrel::draw()
{
	if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	for (int i = 0; i < barrel_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(barrel_vertices[i].x, barrel_vertices[i].y, barrel_vertices[i].z);
		glVertex3f(barrel_vertices[i + 1].x, barrel_vertices[i + 1].y, barrel_vertices[i + 1].z);
		glVertex3f(barrel_vertices[i + 2].x, barrel_vertices[i + 2].y, barrel_vertices[i + 2].z);
		glEnd();
	}
}

void shape::Wheel::draw()
{
	if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	for (int i = 0; i < wheel_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(wheel_vertices[i].x, wheel_vertices[i].y, wheel_vertices[i].z);
		glVertex3f(wheel_vertices[i + 1].x, wheel_vertices[i + 1].y, wheel_vertices[i + 1].z);
		glVertex3f(wheel_vertices[i + 2].x, wheel_vertices[i + 2].y, wheel_vertices[i + 2].z);
		glEnd();
	}
}

void shape::Plane::set_condition(float l, float g, float d)
{
	length = l;
	gap = g;
	depth = d;
}

void shape::Plane::draw_plane(bool fill)
{
	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	glBegin(GL_LINES);
	for (GLfloat i = -length; i <= length; i += gap) {
		glVertex3f(i, depth, length);
		glVertex3f(i, depth, -length);
		glVertex3f(length, depth, i);
		glVertex3f(-length, depth, i);
		glVertex3f(i, depth, length);
		glVertex3f(length, depth, i);
		glVertex3f(i, depth, -length);
		glVertex3f(-length, depth, i);
	}
	glEnd();
}

void shape::Shape::set_color(tuple<float, float, float> color)
{
	colorRGB = color;
}

void shape::WheelRight::draw()
{
	if (fill)
		glColor3f(0.8f, 0.8f, 0.8f);
	else
		glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));

	for (int i = 0; i < wheel_vertices.size(); i += 3) {
		glBegin(fill ? GL_TRIANGLES : GL_LINE_LOOP);
		glVertex3f(wheel_vertices[i].x, wheel_vertices[i].y, wheel_vertices[i].z);
		glVertex3f(wheel_vertices[i + 1].x, wheel_vertices[i + 1].y, wheel_vertices[i + 1].z);
		glVertex3f(wheel_vertices[i + 2].x, wheel_vertices[i + 2].y, wheel_vertices[i + 2].z);
		glEnd();
	}
}
