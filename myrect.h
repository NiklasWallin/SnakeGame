#ifndef MYRECT_H
#define MYRECT_H
#include <QTimer>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>
#include <strings.h>
#include <QVariant>

class MyRect: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    MyRect();
    MyRect(int x, int y);

    QTimer *timer3;
    QString m_direction;
    int thedirection;
    int score;
    bool fruitCollision;
    void keyPressEvent(QKeyEvent * event);

private:

public slots:
    void move();

};

#endif // MYRECT_H
