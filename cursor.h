#ifndef CURSOR_H
#define CURSOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QTimer>

extern int grid_size;
extern int grid_height;
extern int grid_width;
extern int scaling;

class game;

class cursor : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
	cursor(int,int, game*);
	void keyPressEvent(QKeyEvent* key);
	int cursor_index();
private:
	int cursor_x = 0;
	int cursor_y = 0;
	int frame = 0;
	QPixmap sheet;
	game* the_game;
signals:
	void zPressed(int);
	void xPressed();
public slots:
	void animate();
};

#endif // CURSOR_H
