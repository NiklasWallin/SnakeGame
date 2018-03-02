#include <QApplication>
#include "game.h"

//Game is now global
Game * game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Game();

    return a.exec();
}
