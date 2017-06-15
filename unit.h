#ifndef UNIT_H
#define UNIT_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <string>

extern int grid_size;
extern int grid_height;
extern int grid_width;
extern int scaling;

class unit : public QWidget, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	unit(int,int,std::string,int,int,int,int,int,int);
	unit(const unit&);
	//accessors
	int get_hp();
	int get_sta();
	int get_att();
	int get_def();
	int get_move();
	std::string get_type();
	int get_team();
	int get_x();
	int get_y();
	int index();
	bool get_status();
	//mutators
	void receive_damage(int);
	void exhaust_stamina(int);
	void set_index(int);
	void set_inactive();
	void set_cycle(int);
private:
	int hp; // hitpoints or health of unit
	int	sta; // stamina of unit
	int	att; // damage dealt by unit
	int	def; // damage reduce when attacked
	int	move; // movement range of unit

	std::string type; // 0 for axe, 1 for sword, 2 for lance
	int	team; // 0 for player, 1 for AI

	// unit location
	int unit_x;
	int unit_y;

	bool active = true;

	int frame = 0;
	int cycle = 0;
	QPixmap sheet;
signals:

public slots:
	void animate();
	void activated();
};

#endif // UNIT_H
