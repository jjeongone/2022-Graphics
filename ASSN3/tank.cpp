#include "tank.h"

Tank::Tank()
{
	bullet_speed = 0.006;
	angle_radian = 30 / 180 * 3.142;
	health = 3;
	color_weight = make_tuple(1.f, 1.f, 1.f);

	body_node.part = &body;
	body_node.rotate = make_tuple(180, 1, 0, 0);
	body_node.draw = &shape::Body::draw;

	body.colorRGB = make_tuple(0.3 * get<0>(color_weight), 0.7 * get<1>(color_weight), 0.3 * get<2>(color_weight));

	head.colorRGB = make_tuple(0.1 * get<0>(color_weight), 0.6 * get<1>(color_weight), 0.1 * get<2>(color_weight));

	barrel.colorRGB = make_tuple(atan(bullet_speed * 20) / 3.142 * 2, atan(5 * bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2);
}

Tank::Tank(tuple<float, float, float> init_coordinate, float init_size, tuple<float, float, float> init_color_weight, float init_angle_radian = 30 / 180 * 3.142, int init_health = 3, float init_bullet_speed = 0.006, bool reflect = false)
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
	body_node.rotate = make_tuple(180, 0, 1, 0);
	body_node.translate = make_tuple(0, 6, 0);
	body_node.draw = &shape::Body::draw;

	body.colorRGB = make_tuple(0.0 * get<0>(color_weight), 0.0 * get<1>(color_weight), 0.3 * get<2>(color_weight));
	head.colorRGB = make_tuple(0.3 * get<0>(color_weight), 0. * get<1>(color_weight), 0. * get<2>(color_weight));
	barrel.colorRGB = make_tuple(atan(5 * bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2, atan(bullet_speed * 20) / 3.142 * 2);
}

void Tank::draw_tank(bool fill)
{
	body.coordinate3D = coordinate;

	body.fill = fill;
	barrel.fill = fill;
	head.fill = fill;
	
	barrel.colorRGB = make_tuple(atan(bullet_speed * 0.1) / 3.142 * 2, atan(5 * bullet_speed * 0.1) / 3.142 * 2, atan(bullet_speed * 0.1) / 3.142 * 2);


	treenode<shape::Barrel> barrel_node;
	treenode<shape::Head> turret_node;

	turret_node.part = &head;
	turret_node.translate = make_tuple(-0.3, 2.5, -1.97);
	turret_node.rotate = make_tuple(head_angle, 0, 1, 0);

	//turret_node.rotate = make_tuple(-angle_radian / (2 * 3.142) * 360, 0, 1., 0);
	turret_node.draw = &shape::Head::draw;
	body_node.child = reinterpret_cast<treenode<shape::Body>*>(&turret_node);

	barrel_node.part = &barrel;
	barrel_node.translate = make_tuple(0, 0, 4);
	barrel_node.rotate = make_tuple(barrel_angle, 1, 0, 0);
	barrel_node.draw = &shape::Barrel::draw;
	turret_node.child = reinterpret_cast<treenode<shape::Head>*>(&barrel_node);
	

	vector<treenode<shape::Wheel>> wheel_nodes(4);

	for (int i = 0; i < 4; i++)
	{		
		wheels[i].rotation_angle_radian = 0;
		wheels[i].fill = fill;
		wheels[i].colorRGB = make_tuple(0. * get<0>(color_weight), 0. * get<1>(color_weight), 0 * get<2>(color_weight));

		wheel_nodes[i].part = &wheels[i];
		wheel_nodes[i].draw = &shape::Wheel::draw;

		if (i == 0)
		{
			turret_node.sibling = reinterpret_cast<treenode<shape::Head>*>(&wheel_nodes[i]);
			wheel_nodes[i].translate = make_tuple(2.5, -1.4, 5.15);
			wheel_nodes[i].rotate = make_tuple(wheel_angle_left, 1, 0, 0);
		}
		else
		{
			wheel_nodes[i - 1].sibling = &wheel_nodes[i];
			wheel_nodes[i].translate = make_tuple(2.5, -1.4, 1.55 - 3.22 * (i - 1));
			wheel_nodes[i].rotate = make_tuple(wheel_angle_left, 1, 0, 0);
		}
	}

	vector<treenode<shape::WheelRight>> wheel_right_nodes(4);

	for (int i = 0; i < 4; i++)
	{
		right_wheels[i].rotation_angle_radian = 0;
		right_wheels[i].fill = fill;
		right_wheels[i].colorRGB = make_tuple(0. * get<0>(color_weight), 0. * get<1>(color_weight), 0. * get<2>(color_weight));

		wheel_right_nodes[i].part = &right_wheels[i];
		wheel_right_nodes[i].draw = &shape::WheelRight::draw;

		if (i == 0)
		{
			wheel_nodes[3].sibling = reinterpret_cast<treenode<shape::Wheel>*>(&wheel_right_nodes[i]);
			wheel_right_nodes[i].translate = make_tuple(-2.5, -1.4, 5.15);
			wheel_right_nodes[i].rotate = make_tuple(wheel_angle_right, 1, 0, 0);
		}
		else
		{
			wheel_right_nodes[i - 1].sibling = &wheel_right_nodes[i];
			wheel_right_nodes[i].translate = make_tuple(-2.5, -1.4, 1.55 - 3.22 * (i - 1));
			wheel_right_nodes[i].rotate = make_tuple(wheel_angle_right, 1, 0, 0);
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
	

	if (node->child != nullptr)
	{
		display(node->child);
	}
	node->draw(*(node->part));
	glPopMatrix();

	if (node->sibling != nullptr)
	{
		display(node->sibling);
	}
}

tuple<float, float, float, float> Tank::getBarrelOrientation()
{
	return make_tuple(0., 0., 0., 0.);
}

float Tank::getBarrelAngle()
{
	return barrel_angle;
}

void Tank::setBarrel(float new_angle)
{
	barrel_angle = new_angle;
}

float Tank::getHeadAngle()
{
	return head_angle;
}

void Tank::setHead(float new_angle)
{
	head_angle = new_angle;
}

void Tank::setBulletSpeed(float new_bullet_speed)
{
	bullet_speed = new_bullet_speed;
}

float Tank::getBulletSpeed()
{
	return bullet_speed;
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

void Tank::setCoordinate(tuple<float, float, float> new_coordinate)
{
	coordinate = new_coordinate;
}

tuple<float, float, float> Tank::getCoordinate()
{
	return coordinate;
}

float Tank::getSize()
{
	return size;
}

pair<float, float> Tank::getWheelAngle()
{
	return make_pair(wheel_angle_left, wheel_angle_right);
}

void Tank::setWheelAngle(pair<float, float> new_angle)
{
	wheel_angle_left = new_angle.first;
	wheel_angle_right = new_angle.second;
}
