#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "cursor.h"

int grid_size = 16;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();

    cursor* player_cursor = new cursor();
    player_cursor->setRect(0,0,16,16);
    scene->addItem(player_cursor);
    player_cursor->setFlag(QGraphicsItem::ItemIsFocusable);
    player_cursor->setFocus();

    QGraphicsView* view = new QGraphicsView(scene);
    view->show();
    return a.exec();
}
