#include "unit.h"

unit::unit(int x, int y, std::string set_type, int set_team, int set_move)
		:unit_x(x), unit_y(y), move(set_move),
		type(set_type), team(set_team){
	QPixmap image(QString::fromStdString(std::string(":/images/sprites/unit_") + type + std::string(".png")));
	sheet = (image).scaled(image.width()*scaling,image.height()*scaling,Qt::IgnoreAspectRatio, Qt::FastTransformation);
	setPos(unit_x*grid_size,unit_y*grid_size);
	setPixmap(sheet.copy(4*team*16*scaling,0,16*scaling,16*scaling));
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
}

//leftover code
/*
int unit::get_hp()
{
	return hp;
}

int unit::get_sta()
{
	return sta;
}

int unit::get_att()
{
	return att;
}

int unit::get_def()
{
	return def;
}
*/

int unit::get_move()
{
	return move;
}

//unit type
//axe beats lance, lance beats sword, and sword beats axe
//units of the same type will destroy eachother
int unit::get_type()
{
	if(type == "axe")
		return 0;
	else if(type == "sword")
		return 1;
	else if(type == "lance")
		return 2;
	else
		return 0; //default to axe
}

int unit::get_team()
{
	return team;
}

int unit::get_x()
{
	return unit_x;
}

int unit::get_y()
{
	return unit_y;
}

//calculates array index
int unit::index()
{
	return unit_x+(unit_y*grid_width);
}

//indicates if a unit has taken its turn
bool unit::get_status()
{
	return active;
}

//sets position based on new index
void unit::set_index(int index)
{
	unit_x = index%grid_width;
	unit_y = index/grid_width;
	setPos(unit_x*grid_size,unit_y*grid_size);
}

//indicates unit turn is over
void unit::set_status(int status) // 1 or 0
{
	active = status;
	set_cycle(1-status); //swaps 1 and 0 values
}

//visual, grayscale
void unit::set_cycle(int new_cycle)
{
	cycle = new_cycle;
	setPixmap(sheet.copy((frame+(4*team)+(2*cycle))*16*scaling, 0, 16*scaling, 16*scaling));
}

//visual
void unit::animate()
{
	++frame;
	if (frame > 1){
		frame = 0;
	}
	setPixmap(sheet.copy((frame+(4*team)+(2*cycle))*16*scaling, 0, 16*scaling, 16*scaling));
}
