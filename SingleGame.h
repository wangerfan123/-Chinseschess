#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h" //从Board类进行派生，是Board的子类，子类具有父类所有public的内容

class SingleGame : public Board //派生自Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);
    ~SingleGame();

    int _level;//层数，层数越多，计算越慢

    void back();
    void click(int id, int row, int col);
    //人工智能函数
    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);
    int getMinScore(int level, int curMin);
    int getMaxScore(int level, int curMax);
    int score();//获取局面分函数
    //虚假移动
    void fakeMove(Step* step);
    void unfakeMove(Step* step);

signals:

public slots:
    void computerMove();
};

#endif // SINGLEGAME_H
