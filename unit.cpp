#include "unit.h"


unit::unit(int x, int y, std::string set_type, int set_team, int set_hp, int set_sta, int set_att, int set_def, int set_move)
		:unit_x(x), unit_y(y),
		hp(set_hp), sta(set_sta), att(set_att), def(set_def), move(set_move),
		type(set_type), team(set_team){
	sheet = QPixmap(QString::fromStdString(std::string(":/images/sprites/unit_") + type + std::string(".png")));
	setPos(unit_x,unit_y);
	setPixmap(sheet.copy(0, 0, grid_size,grid_size));
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
}

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

int unit::get_move()
{
	return move;
}

std::string unit::get_type()
{
	return type;
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

void unit::receive_damage(int dmg)
{
	hp-=dmg;
	if(hp<=0){
		hp=0;
	}
}

void unit::exhaust_stamina(int exh)
{
	sta-=exh;
	if(sta<=0){
		sta=0;
	}
}


void unit::animate()
{
	++frame;
	if (frame > 1){
		frame = 0;
	}
	setPixmap(sheet.copy((frame+(2*team))*16, 0, 16, 16));
}
