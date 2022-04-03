#include "shape.h"

void shape::Line::draw_line()
{
	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex3f(100.0, position, 0);
	glVertex3f(-100.0, position, 0);
	glEnd();
}

void shape::Line::setPosition(float new_position)
{
	position = new_position;
}

void shape::Rectangle::draw_rectangle()
{
	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	glRectf(coordinate2D.first, coordinate2D.second, coordinate2D.first + width, coordinate2D.second + height);
}

void shape::Semicircle::draw_semicircle()
{
	float theta;
	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	glBegin(GL_POLYGON);
	for (int i = 0; i < 180; i++) {
		theta = i * 3.142 / 180;
		glVertex3f(coordinate2D.first + radius * cos(theta), coordinate2D.second + radius * sin(theta), 0);
	}
	glEnd();
}

void shape::Circle::draw_circle()
{
	float theta;
	glColor3f(get<0>(colorRGB), get<1>(colorRGB), get<2>(colorRGB));
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.142 / 180;
		glVertex3f(coordinate2D.first + radius * cos(theta), coordinate2D.second + radius * sin(theta), 0);
	}
	glEnd();
}

void shape::Wheel::draw_wheel()
{
	body_large.radius = radius;
	body_large.coordinate2D = coordinate2D;
	body_large.colorRGB = colorRGB;
	body_large.draw_circle();

	body_background.radius = 0.9 * radius;
	body_background.coordinate2D = coordinate2D;
	body_background.colorRGB = make_tuple(0., 0., 0.);
	body_background.draw_circle();
	
	body_small.radius = 0.2 * radius;
	body_small.coordinate2D = coordinate2D;
	body_small.colorRGB = colorRGB;
	body_small.draw_circle();

	for (int i = 0; i < num_circles; i++)
	{
		Circle tmp;
		tmp.radius = 0.1 * radius;
		tmp.colorRGB = colorRGB;
		float coordY = coordinate2D.second + 0.6 * radius * cos(2 * 3.142 * i / num_circles);
		float coordX = coordinate2D.first + 0.6 * radius * sin(2 * 3.142 * i / num_circles);
		tmp.coordinate2D = make_pair(coordX, coordY);
		small_bolts.push_back(tmp);
		tmp.draw_circle();
	}
}

