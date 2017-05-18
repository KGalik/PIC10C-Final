#include "cursor.h"

#include <QDebug>
cursor::cursor(int set_x, int set_y): cursor_x(set_x), cursor_y(set_y)
{
	QPixmap image(":/images/sprites/player_cursor.png");
	sheet = (image).scaled(image.width()*scaling,image.height()*scaling,Qt::IgnoreAspectRatio, Qt::FastTransformation);
	setPos((cursor_x*grid_size)-(2*scaling),(cursor_y*grid_size)-(2*scaling));
	setPixmap(sheet.copy(0,0,20*scaling,20*scaling));
	this->setZValue(1);
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
}

void cursor::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Up){
		if(cursor_y > 0){
			--cursor_y;
			setPos((cursor_x*grid_size)-(2*scaling),(cursor_y*grid_size)-(2*scaling));
		}
	}
	else if (event->key() == Qt::Key_Down){
		if(cursor_y < grid_height - 1){
			++cursor_y;
			setPos((cursor_x*grid_size)-(2*scaling),(cursor_y*grid_size)-(2*scaling));
		}
	}
	else if (event->key() == Qt::Key_Left){
		if(cursor_x > 0){
			--cursor_x;
			setPos((cursor_x*grid_size)-(2*scaling),(cursor_y*grid_size)-(2*scaling));
		}
	}
	else if (event->key() == Qt::Key_Right){
		if(cursor_x < grid_width - 1){
			++cursor_x;
			setPos((cursor_x*grid_size)-(2*scaling),(cursor_y*grid_size)-(2*scaling));
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
