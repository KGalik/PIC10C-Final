#include "unit.h"


unit::unit(int x, int y, std::string set_type, int set_team, int set_hp, int set_sta, int set_att, int set_def, int set_move)
		:unit_x(x), unit_y(y),
		hp(set_hp), sta(set_sta), att(set_att), def(set_def), move(set_move),
		type(set_type), team(set_team){
	QPixmap image(QString::fromStdString(std::string(":/images/sprites/unit_") + type + std::string(".png")));
	sheet = (image).scaled(image.width()*scaling,image.height()*scaling,Qt::IgnoreAspectRatio, Qt::FastTransformation);
	setPos(unit_x*grid_size,unit_y*grid_size);
	setPixmap(sheet.copy(4*team*16*scaling,0,16*scaling,16*scaling));
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
}

unit::unit(const unit& rhs): hp(rhs.hp),sta(rhs.sta), att(rhs.att), def(rhs.def), move(rhs.move), type(rhs.type), team(rhs.team), unit_x(rhs.unit_x), unit_y(rhs.unit_y), frame(rhs.frame), sheet(rhs.sheet){}

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

int unit::index()
{
	return unit_x+(unit_y*grid_width);
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
	setPixmap(sheet.copy((frame+(4*team))*16*scaling, 0, 16*scaling, 16*scaling));
}

void unit::activated()
{

}
