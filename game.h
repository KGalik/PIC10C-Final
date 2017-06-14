#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "unit.h"
#include "cursor.h"
#include <QObject>
#include <memory>
#include <vector>

extern int grid_size;
extern int grid_height;
extern int grid_width;
extern int scaling;

class game: public QObject
{
	Q_OBJECT
public:
	game(int, int, QGraphicsScene*);
	void add_unit(unit*);
	void keyPressEvent(QKeyEvent* key);
	void update_paths(int, int, int);
private:
	int width, height;
	std::unique_ptr<unit> unit_list[144];
	int pathing[144] = {0};
	std::vector<QGraphicsRectItem*> tiles;
	QGraphicsScene* scene;
	bool show_paths = 0;
	bool show_actions = 0;
	bool show_targets = 0;
signals:
	void selected(int);
public slots:
	void select(int);
	void back(int);
};

#endif // GAME_H
