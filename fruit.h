#ifndef FRUIT_H
#define FRUIT_H
#include <QGraphicsRectItem>
#include <QObject>
#include <stdlib.h>

class Fruit: public QObject,public QGraphicsRectItem {
    Q_OBJECT
public:
    Fruit();


};

#endif // FRUIT_H
