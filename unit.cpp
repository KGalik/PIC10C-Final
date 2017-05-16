#include "unit.h"

template<typename type_policy, typename team_policy>
unit<typename type_policy, typename team_policy>::unit(int x, int y, int set_hp, int set_sta, int set_att, int set_def, int set_move, int set_type, int set_team)
		:unit_x(x), unit_y(y),
		hp(set_hp), sta(set_sta), att(set_att), def(set_def), move(set_move),
		type(set_type), team(set_team){
	sheet = QPixmap(":/images/sprites/unit_red_sword.png");
	setPixmap(sheet.copy(0, 0, 16,16));
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_hp()
{
	return hp;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_sta()
{
	return sta;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_att()
{
	return att;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_def()
{
	return def;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_move()
{
	return move;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_type()
{
	return type;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_team()
{
	return team;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_x()
{
	return unit_x;
}

template<typename type_policy, typename team_policy>
int unit<type_policy, team_policy>::get_y()
{
	return unit_y;
}

template<typename type_policy, typename team_policy>
void unit<type_policy, team_policy>::receive_damage(int dmg)
{
	hp-=dmg;
	if(hp<=0){
		hp=0;
	}
}

template<typename type_policy, typename team_policy>
void unit<type_policy, team_policy>::exhaust_stamina(int exh)
{
	sta-=exh;
	if(sta<=0){
		sta=0;
	}
}

