#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

extern int grid_size;
extern int grid_height;
extern int grid_width;

class cursor : public QGraphicsRectItem
{
public:
	void keyPressEvent(QKeyEvent* key);
	void update_cursor();
private:
	int cursor_x;
	int cursor_y;
signals:

public slots:

};

#endif // CURSOR_H
