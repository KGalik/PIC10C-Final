#include "cursor.h"

void cursor::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Up){
		if(cursor_y > 0){
			--cursor_y;
			update_cursor();
		}
	}
	else if (event->key() == Qt::Key_Down){
		if(cursor_y < grid_height - 1){
			++cursor_y;
			update_cursor();
		}
	}
	else if (event->key() == Qt::Key_Left){
		if(cursor_x > 0){
			--cursor_x;
			update_cursor();
		}
	}
	else if (event->key() == Qt::Key_Right){
		if(cursor_x < grid_width - 1){
			++cursor_x;
			update_cursor();
		}
	}
}

void cursor::update_cursor()
{
	setPos(cursor_x*grid_size,cursor_y*grid_size);
}
