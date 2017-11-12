#include "myrect.h"
#include "fruit.h"
#include "game.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <typeinfo>
#include <QList>
#include <QApplication>
#include <QVector>
#include <QtCore>

extern Game * game; //added the global object Game

QList<MyRect> bodylist;
extern MyRect * bodyArray[3];
extern QVector<MyRect> bodyVector;
extern QPainter *painter;
extern QBrush brush;

MyRect::MyRect(){

    timer3 = new QTimer(this);

    connect(timer3,SIGNAL(timeout()),this,SLOT(move()));
    timer3->start(150);

}

MyRect::MyRect(int x, int y)
{
    setPos(x,y);
    setRect(0,0,50,50);
}

void MyRect::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Up && thedirection != 3){
        thedirection = 1;
    }
    else if(event->key() == Qt::Key_Left && thedirection != 4){
        thedirection = 2;
    }
    else if(event->key() == Qt::Key_Down && thedirection != 1){
        thedirection = 3;
    }
    else if(event->key() == Qt::Key_Right && thedirection != 2){
        thedirection = 4;
    }
}


void MyRect::move(){
    //if player is colliding with fruit

    QList<QGraphicsItem *> colliding_items = collidingItems();
    int collideX;
    int collideY;


    for(int i = 0; i < colliding_items.size(); i++){
        //check if colliding with snakebody
        if(typeid(*(colliding_items[i])) == typeid(MyRect)){
            if(colliding_items[i]->x() == this->x() && colliding_items[i]->y() == this->y()){
                qDebug() << "collided with snakebody";
                game->gameover = true;
            }

        }else if(typeid(*(colliding_items[i])) == typeid(Fruit)){
           if(colliding_items[i]->x() == this->x() && colliding_items[i]->y() == this->y()){
               //adding to score
                game->points++;
               //remove fruit
                scene()->removeItem(colliding_items[i]);
                //delete from memory
                delete colliding_items[i];

                collideX = this->pos().x();
                collideY = this->pos().y();

                fruitCollision = true;
                MyRect * test = new MyRect(collideX,collideY);

                scene()->addItem(test);

                Fruit * fruit = new Fruit();
                scene()->addItem(fruit);
           }
        }
    }

/*
    //make body follow head                                         this is very you stoped, this is fucked up... try arrays...
    int testX = this->pos().x();
    int testY = this->pos().y();
    int oldX;
    int oldY;

    for(int i = 0; i < bodylist->length(); i++){
        if(i == 0){
            bodylist[i].first().setPos(testX,testY);
        }else{
            oldX = bodylist[i - 1].last().pos().x();
            oldY = bodylist[i - 1].last().pos().y();

           // iter->next().setPos(oldX,oldY);

            //iter->next().setPos(oldX,oldY);

            bodylist->at(i).setPos(oldX,oldY);
        }
    }
*/

    //move to the direction pressed last
    if(thedirection == 2){
        if(pos().x() != 0){
            setPos(x()-50,y());
        }else
            game->gameover = true;
    }
    else if(thedirection == 4){
       if(pos().x() != 550){
            setPos(x()+50,y());
        }else
           game->gameover = true;
    }
    else if(thedirection == 1){
        if(pos().y() != 0){
            setPos(x(),y()-50);
        }else
            game->gameover = true;
    }
    else if(thedirection == 3){
        if(pos().y() != 550){
            setPos(x(),y()+50);
        }else
            game->gameover = true;
    }

    game->gameOverBro();

    qDebug() << "x possition = " << pos().x() << " y possition = " << pos().y();
}
