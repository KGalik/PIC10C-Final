#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "cursor.h"
#include "unit.h"
#include "game.h"

int scaling = 2;
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

	current_game->add_unit(new unit(0,0,"axe",0,10,100,10,10,4));
	current_game->add_unit(new unit(12,1,"axe",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,1,"sword",0,10,100,10,10,4));
	current_game->add_unit(new unit(15,2,"sword",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,2,"lance",0,10,100,10,10,4));
	current_game->add_unit(new unit(12,3,"lance",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,3,"axe",0,10,100,10,10,4));
	current_game->add_unit(new unit(15,4,"axe",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,4,"sword",0,10,100,10,10,4));
	current_game->add_unit(new unit(12,5,"sword",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,5,"lance",0,10,100,10,10,4));
	current_game->add_unit(new unit(15,6,"lance",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,6,"axe",0,10,100,10,10,4));
	current_game->add_unit(new unit(12,7,"axe",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,7,"sword",0,10,100,10,10,4));
	current_game->add_unit(new unit(15,8,"sword",1,10,100,10,10,4));
	current_game->add_unit(new unit(0,8,"lance",0,10,100,10,10,4));
	current_game->add_unit(new unit(15,0,"lance",1,10,100,10,10,4));
	current_game->add_unit(new unit(9,2,"axe",1,10,100,10,10,4));
	current_game->add_unit(new unit(6,3,"sword",1,10,100,10,10,4));
	current_game->add_unit(new unit(9,4,"lance",1,10,100,10,10,4));
	current_game->add_unit(new unit(6,5,"axe",1,10,100,10,10,4));
	current_game->add_unit(new unit(9,6,"sword",1,10,100,10,10,4));
	current_game->add_unit(new unit(6,7,"lance",1,10,100,10,10,4));
	current_game->add_unit(new unit(9,8,"axe",1,10,100,10,10,4));
	current_game->add_unit(new unit(9,0,"sword",1,10,100,10,10,4));
	current_game->add_unit(new unit(6,1,"lance",1,10,100,10,10,4));

	QGraphicsView* view = new QGraphicsView(scene);
	view->show();

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedSize(grid_width*grid_size+2,grid_height*grid_size+2);
	scene->setSceneRect(0,0,grid_width*grid_size+2,grid_height*grid_size+2);

    return a.exec();
}
