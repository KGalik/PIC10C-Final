#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "cursor.h"

int grid_size = 16;
int grid_height = 9;
int grid_width = 16;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QGraphicsScene* scene = new QGraphicsScene();

	cursor* player_cursor = new cursor();
	player_cursor->setRect(0,0,14,14);
	scene->addItem(player_cursor);
	player_cursor->setFlag(QGraphicsItem::ItemIsFocusable);
	player_cursor->setFocus();

	QGraphicsView* view = new QGraphicsView(scene);
	view->show();

	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setFixedSize(256,144);
	scene->setSceneRect(0,0,256,144);

    return a.exec();
}
