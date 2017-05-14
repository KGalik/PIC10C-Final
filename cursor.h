#ifndef CURSOR_H
#define CURSOR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

extern int grid_size;

class cursor : public QGraphicsRectItem
{
public:
    void keyPressEvent(QKeyEvent* key);
signals:

public slots:

};

#endif // CURSOR_H
