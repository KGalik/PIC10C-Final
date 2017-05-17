#include "cursor.h"

#include <QDebug>
cursor::cursor(int set_x, int set_y): cursor_x(set_x), cursor_y(set_y)
{
	sheet = (QPixmap(":/images/sprites/player_cursor.png")).scaled(QPixmap(":/images/sprites/player_cursor.png").height()*scaling,QPixmap(":/images/sprites/player_cursor.png").width()*scaling,Qt::IgnoreAspectRatio, Qt::FastTransformation);
	setPos(cursor_x*grid_size,cursor_y*grid_size);
	setPixmap(sheet.copy(0,0,20*scaling,20*scaling));
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
}

void cursor::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Up){
		if(cursor_y > 0){
			--cursor_y;
			setPos(cursor_x*grid_size,cursor_y*grid_size);
		}
	}
	else if (event->key() == Qt::Key_Down){
		if(cursor_y < grid_height - 1){
			++cursor_y;
			setPos(cursor_x*grid_size,cursor_y*grid_size);
		}
	}
	else if (event->key() == Qt::Key_Left){
		if(cursor_x > 0){
			--cursor_x;
			setPos(cursor_x*grid_size,cursor_y*grid_size);
		}
	}
	else if (event->key() == Qt::Key_Right){
		if(cursor_x < grid_width - 1){
			++cursor_x;
			setPos(cursor_x*grid_size,cursor_y*grid_size);
		}
	}
}

void cursor::animate()
{
	++frame;
	if (frame > 1){
		frame = 0;
	}
	setPixmap(sheet.copy(frame*20*scaling,0,20*scaling,20*scaling));
}
