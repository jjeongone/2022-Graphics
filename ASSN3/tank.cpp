#include "tank.h"

Tank::Tank()
{
	bullet_speed = 0.006;
	angle_radian = 30 / 180 * 3.142;
	health = 3;
	color_weight = make_tuple(1.f, 1.f, 1.f);

	body_node.part = &body;
	body_node.draw = &shape::Rectangle::draw_rectangle;

	body.width = size;
	body.height = 0.26 * size;
	body.coordinate2D = coordinate;
	body.colorRGB = make_tuple(0.3 * get<0>(color_weight), 0.7 * get<1>(color_weight), 0.3 * get<2>(color_weight));

	turret.radius = 0.2 * size;
	turret.coordinate2D = make_pair(0, 0);
	turret.colorRGB = make_tuple(0.1 * get<0>(color_weight), 0.6 * get<1>(color_weight), 0.1 * get<2>(color_weight));

	barrel.height = 0.05 * size;
	barrel.width = 0.8 * size;
	barrel.colorRGB = make_tuple(atan(bullet_speed * 20) / 3.142 * 2, atan(5 * bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2);
	barrel.coordinate2D = make_pair(0, 0);
}

Tank::Tank(pair<float, float> init_coordinate, float init_size, tuple<float, float, float> init_color_weight, float init_angle_radian = 30 / 180 * 3.142, int init_health = 3, float init_bullet_speed = 0.006, bool reflect = false)
{
	coordinate = init_coordinate;
	size = init_size;
	color_weight = init_color_weight;
	angle_radian = init_angle_radian;
	health = init_health;
	shootability = true;
	bullet_speed = init_bullet_speed;
	is_reflect = reflect;

	body_node.part = &body;
	body_node.draw = &shape::Rectangle::draw_rectangle;

	body.width = size;
	body.height = 0.26 * size;
	body.coordinate2D = coordinate;
	body.colorRGB = make_tuple(0.3 * get<0>(color_weight), 0.7 * get<1>(color_weight), 0.3 * get<2>(color_weight));

	turret.radius = 0.2 * size;
	turret.coordinate2D = make_pair(0, 0);
	turret.colorRGB = make_tuple(0.1 * get<0>(color_weight), 0.6 * get<1>(color_weight), 0.1 * get<2>(color_weight));

	barrel.height = 0.05 * size;
	barrel.width = 0.8 * size;
	barrel.colorRGB = make_tuple(atan(bullet_speed * 20) / 3.142 * 2, atan(5 * bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2);
	barrel.coordinate2D = make_pair(0, 0);
}

void Tank::draw_tank()
{
	body.coordinate2D = coordinate;
	barrel.colorRGB = make_tuple(atan(bullet_speed * 20) / 3.142 * 2, atan(5 * bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2);
	float coordY = coordinate.second + 0.26 * size * 0.95;
	float coordX = coordinate.first + 0.3 * size;

	treenode<shape::Rectangle> barrel_node;
	treenode<shape::Semicircle> turret_node;

	barrel_node.part = &barrel;
	barrel_node.translate = make_tuple(coordX, coordY, 0);
	barrel_node.rotate = make_tuple(angle_radian / (2 * 3.142) * 360, 0, 0, 1.);
	barrel_node.draw = &shape::Rectangle::draw_rectangle;
	body_node.child = &barrel_node;

	turret_node.part = &turret;
	turret_node.rotate = make_tuple(-angle_radian / (2 * 3.142) * 360, 0, 0, 1.);
	turret_node.draw = &shape::Semicircle::draw_semicircle;
	barrel_node.child = reinterpret_cast<treenode<shape::Rectangle>*>(&turret_node);

	vector<treenode<shape::Wheel>> wheel_nodes(6);

	for (int i = 0; i < 6; i++)
	{		
		wheels[i].radius = size / 12;
		wheels[i].num_circles = 5;
		wheels[i].rotation_angle_radian = -coordinate.first / wheels[i].radius * 50;
		wheels[i].colorRGB = make_tuple(0.3 * get<0>(color_weight), 0.3 * get<1>(color_weight), 0.8 * get<2>(color_weight));

		wheel_nodes[i].part = &wheels[i];
		wheel_nodes[i].draw = &shape::Wheel::draw_wheel;

		if (i == 0)
		{
			barrel_node.sibling = reinterpret_cast<treenode<shape::Rectangle>*>(&wheel_nodes[i]);
			wheel_nodes[i].translate = make_tuple(coordinate.first + wheels[i].radius, coordinate.second - 0.7 * wheels[i].radius, 0);
			wheel_nodes[i].rotate = make_tuple(wheels[i].rotation_angle_radian, 0, 0, 1);
		}
		else
		{
			wheel_nodes[i - 1].sibling = &wheel_nodes[i];
			wheel_nodes[i].translate = make_tuple(coordinate.first + wheels[i].radius * (2 * i + 1), coordinate.second - 0.7 * wheels[i].radius, 0);
			wheel_nodes[i].rotate = make_tuple(wheels[i].rotation_angle_radian, 0, 0, 1);
		}
	}
	
	display(&body_node);
}

template<class T>
void Tank::display(treenode<T>* node)
{
	if (node == nullptr)
	{
		return;
	}

	glPushMatrix();
	glTranslatef(get<0>(node->translate), get<1>(node->translate), get<2>(node->translate));
	glRotatef(get<0>(node->rotate), get<1>(node->rotate), get<2>(node->rotate), get<3>(node->rotate));
	node->draw(*(node->part));

	if (node->child != nullptr)
	{
		display(node->child);
	}

	glPopMatrix();

	if (node->sibling != nullptr)
	{
		display(node->sibling);
	}
}

void Tank::move(float dx, float dy) {
	coordinate.first += dx;
	coordinate.second += dy;
}

pair<float, float> Tank::getBarrelPosition() {
	if (is_reflect) {
		return make_pair(coordinate.first - 0.3 * size - barrel.width * cos(angle_radian), coordinate.second + 0.26 * size * 0.95 + barrel.width * sin(angle_radian));
	}
	else {
		return make_pair(coordinate.first + 0.3 * size + barrel.width * cos(angle_radian), coordinate.second + 0.26 * size * 0.95 + barrel.width * sin(angle_radian));
	}
}

float Tank::getBarrelAngle()
{
	return angle_radian;
}

void Tank::setBarrel(float new_angle_radian)
{
	angle_radian = new_angle_radian;
}

void Tank::setBulletSpeed(float new_bullet_speed)
{
	bullet_speed = new_bullet_speed;
}

float Tank::getBulletSpeed()
{
	return bullet_speed;
}

float Tank::getBottom()
{
	return coordinate.second - 1.7 * size / 12;
}

int Tank::getHealth()
{
	return health;
}

void Tank::setHealth(int new_health)
{
	health = new_health;
}

bool Tank::getShootability()
{
	return shootability;
}

void Tank::setShootability(bool shoot)
{
	shootability = shoot;
}

void Tank::setCoordinate(pair<float, float> new_coordinate)
{
	coordinate = new_coordinate;
}

pair<float, float> Tank::getCoordinate()
{
	return coordinate;
}

float Tank::getSize()
{
	return size;
}

