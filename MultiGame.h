#ifndef MULTIGAME_H
#define MULTIGAME_H

#include "Board.h"

class MultiGame : public Board//棋盘已经支持双人游戏了
{
    Q_OBJECT
public:
    explicit MultiGame(QWidget *parent = 0);
    ~MultiGame();

signals:

public slots:
};

#endif // MULTIGAME_H
