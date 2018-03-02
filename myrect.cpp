#include "myrect.h"
#include "fruit.h"
#include "game.h"
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <typeinfo>
#include <QList>

extern Game * game; //added the global object Game

QList<MyRect*> bodylist;

MyRect::MyRect(){

    timer3 = new QTimer(this);

    connect(timer3,SIGNAL(timeout()),this,SLOT(move()));
    timer3->start(150);

}

void MyRect::move(){
    checkCollision();
    follow();
    getDirection();
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

void MyRect::checkCollision()
{
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

                //get a new snakebody
                collideX = this->pos().x();
                collideY = this->pos().y();

                MyRect * test = new MyRect(collideX,collideY);
                bodylist.append(test);
                scene()->addItem(bodylist.back());


                Fruit * fruit = new Fruit();
                scene()->addItem(fruit);
           }
        }
    }
}

void MyRect::follow()
{
    int testX = this->pos().x();
    int testY = this->pos().y();
    int oldX;
    int oldY;
    int oldX2;
    int oldY2;

    for(int i = 0; i < bodylist.length(); i++){

        if(i == 0){
            oldX = bodylist[i]->pos().x();
            oldY = bodylist[i]->pos().y();
            bodylist[i]->setPos(testX,testY);

        }else {
            oldX2 = bodylist[i]->pos().x();
            oldY2 = bodylist[i]->pos().y();
            bodylist[i]->setPos(oldX,oldY);
            oldX = oldX2;
            oldY = oldY2;

        }
        bodylist[i]->setBrush(QBrush(Qt::darkGray));
    }
}

void MyRect::getDirection()
{
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
}




