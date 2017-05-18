#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "cursor.h"
#include "unit.h"

int scaling = 3;
int grid_size = 16*scaling;
int grid_height = 9;
int grid_width = 16;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QGraphicsScene* scene = new QGraphicsScene();

	cursor* player_cursor = new cursor(7,4);
	scene->addItem(player_cursor);
	player_cursor->setFlag(QGraphicsItem::ItemIsFocusable);
	player_cursor->setFocus();
/*
	unit* test_unit1 = new unit(7,3,"axe",0,1,1,1,1,1);
	scene->addItem(test_unit1);
	unit* test_unit2 = new unit(8,3,"axe",1,1,1,1,1,1);
	scene->addItem(test_unit2);
	unit* test_unit3 = new unit(7,4,"sword",0,1,1,1,1,1);
	scene->addItem(test_unit3);
	unit* test_unit4 = new unit(8,4,"sword",1,1,1,1,1,1);
	scene->addItem(test_unit4);
	unit* test_unit5 = new unit(7,5,"lance",0,1,1,1,1,1);
	scene->addItem(test_unit5);
	unit* test_unit6 = new unit(8,5,"lance",1,1,1,1,1,1);
	scene->addItem(test_unit6);
*/

	QGraphicsView* view = new QGraphicsView(scene);
	view->show();

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedSize(grid_width*grid_size+2,grid_height*grid_size+2);
	scene->setSceneRect(0,0,grid_width*grid_size+2,grid_height*grid_size+2);

    return a.exec();
}
