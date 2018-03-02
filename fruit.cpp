#include "fruit.h"
#include <QObject>
#include <stdlib.h>
#include <QDebug>
#include <QtMath>
#include <QBrush>


Fruit::Fruit(){
    //random x and y cordinates
    int fruitX = rand() % 599;
    int fruitY = rand() % 599;

    int multiplierX = fruitX / 50;
    fruitX = multiplierX * 50;

    int multiplierY = fruitY / 50;
    fruitY = multiplierY * 50;

    setPos(fruitX,fruitY);
    setRect(0,0,50,50);
    this->setBrush(QBrush(Qt::lightGray));
    qDebug() << "x = " << fruitX << " y = " << fruitY;
}
