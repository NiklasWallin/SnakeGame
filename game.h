#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "myrect.h"

class Game: public QGraphicsView{
public:
    Game();
    QGraphicsScene * scene;
    MyRect * player;

    bool gameover = false;

    void gameOverBro();
    int points;

};

#endif // GAME_H
