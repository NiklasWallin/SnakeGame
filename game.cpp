#include "game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "fruit.h"
#include "myrect.h"
#include <QApplication>
#include <QDebug>
#include <QGraphicsView>
extern Game * game;
QGraphicsView * view;
Game::Game()
{
    //create a scene
    points = 0;
    QGraphicsScene * scene = new QGraphicsScene();

    //creat rect
    MyRect * player = new MyRect();

    player->setRect(0,0,50,50);

    scene->addItem(player);

    //make item focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //creating fruit
    Fruit * fruit = new Fruit();
    scene->addItem(fruit);

    //creating score

    //create the view
    view = new QGraphicsView(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    view->setFixedSize(600,600);
    scene->setSceneRect(0,0,600,600);
    player->setPos(view->width()/2,view->height()/2 - player->rect().height());

}

void Game::gameOverBro()
{
    if(gameover){
        qDebug() << "\nGAME OVER.\n\nYou got the score " << game->points;
        QApplication::quit();
    }

}


