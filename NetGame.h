#ifndef NETGAME_H
#define NETGAME_H

#include "Board.h" //从棋盘类派生
#include <QTcpServer>//网络相关的头文件
#include <QTcpSocket>

/*
 * 报文格式定义
 * 1.初始化    两个字节   第一个字节是1，第二个字节01表示红棋黑棋
 * 2.鼠标点击   四个字节  第一个字节2，第二个字节row，第三个字节col，第四个字节是点击的棋子
 * 3.悔棋      一个字节
 *
*/

class NetGame : public Board
{
    Q_OBJECT//信号和槽所用宏
public:
    explicit NetGame(bool server, QWidget *parent = 0);//带参构造函数
    ~NetGame();

    bool _bServer;//服务器还是客户端
    QTcpServer* _server;//服务器
    QTcpSocket* _socket;//套接字，客户端用

    void back();
    void click(int id, int row, int col);

    void backFromNetwork(QByteArray buf);
    void clickFromNetwork(QByteArray buf);
    void initFromNetwork(QByteArray buf);

signals:

public slots:
    void slotNewConnection();
    void slotDataArrive();
};

#endif // NETGAME_H
