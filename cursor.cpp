#include "cursor.h"
#include "game.h"

#include <QDebug>
cursor::cursor(int set_x, int set_y, game* new_game): cursor_x(set_x), cursor_y(set_y), the_game(new_game)
{
	QPixmap image(":/images/sprites/player_cursor.png");
	sheet = (image).scaled(image.width()*scaling,image.height()*scaling,Qt::IgnoreAspectRatio, Qt::FastTransformation);
	setPos((cursor_x*grid_size)-(2*scaling),(cursor_y*grid_size)-(2*scaling));
	setPixmap(sheet.copy(0,0,20*scaling,20*scaling));
	this->setZValue(1);
	QTimer* timer = new QTimer();
	connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
	timer->start(500);
	connect(this, SIGNAL(zPressed(int)), the_game, SLOT(select(int)));
	connect(this, SIGNAL(xPressed(int)), the_game, SLOT(back(int)));
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
	else if (event->key() == Qt::Key_Z){
		emit zPressed(cursor_index());
	}
	else if (event->key() == Qt::Key_X){
		emit xPressed(cursor_index());
	}
}

int cursor::cursor_index()
{
	return cursor_x+(cursor_y*grid_width);
}

void cursor::animate()
{
	++frame;
	if (frame > 1){
		frame = 0;
	}
	setPixmap(sheet.copy(frame*20*scaling,0,20*scaling,20*scaling));
}
