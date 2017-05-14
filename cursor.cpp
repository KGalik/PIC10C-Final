#include "cursor.h"

void cursor::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up){
        setPos(x(),y() - grid_size);
    }
    else if (event->key() == Qt::Key_Down){
        setPos(x(),y() + grid_size);
    }
    else if (event->key() == Qt::Key_Left){
        setPos(x() - grid_size,y());
    }
    else if (event->key() == Qt::Key_Right){
        setPos(x() + grid_size,y());
    }
}
