#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "cursor.h"
#include "unit.h"
#include "game.h"

int scaling = 4;
int grid_size = 16*scaling;
int grid_height = 9;
int grid_width = 16;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QGraphicsScene* scene = new QGraphicsScene();

	game* current_game = new game(grid_width, grid_height, scene);
	cursor* player_cursor = new cursor(7, 4, current_game);
	scene->addItem(player_cursor);
	player_cursor->setFlag(QGraphicsItem::ItemIsFocusable);
	player_cursor->setFocus();

	current_game->add_unit(new unit(7,3,"axe",0,1,1,1,1,4));
	current_game->add_unit(new unit(8,3,"axe",1,1,1,1,1,4));
	current_game->add_unit(new unit(7,4,"sword",0,1,1,1,1,4));
	current_game->add_unit(new unit(8,4,"sword",1,1,1,1,1,4));
	current_game->add_unit(new unit(7,5,"lance",0,1,1,1,1,4));
	current_game->add_unit(new unit(8,5,"lance",1,1,1,1,1,4));

	QGraphicsView* view = new QGraphicsView(scene);
	view->show();

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedSize(grid_width*grid_size+2,grid_height*grid_size+2);
	scene->setSceneRect(0,0,grid_width*grid_size+2,grid_height*grid_size+2);

    return a.exec();
}
