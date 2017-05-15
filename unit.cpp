#include "unit.h"


unit::unit(int x, int y, int set_hp, int set_sta, int set_att, int set_def, int set_move, int set_type, int set_team)
		:unit_x(x), unit_y(y),
		hp(set_hp), sta(set_sta), att(set_att), def(set_def), move(set_move),
		type(set_type), team(set_team){
	sheet = QPixmap(":/images/sprites/unit_red_sword.png");
	setPixmap(sheet.copy(0, 0, 16,16));
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

int unit::get_type()
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

}
