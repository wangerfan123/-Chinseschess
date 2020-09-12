#include "NetGame.h"

NetGame::NetGame(bool server, QWidget *parent) : Board(parent)//派生
{
    _server = NULL;
    _socket = NULL;
    _bServer = server;

    if(_bServer)//服务端
    {
        _server = new QTcpServer(this); //创建服务器
        _server->listen(QHostAddress::Any, 9899);//此端口监听
        connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));//监听信号，有一个槽函数进行处理
    }
    else//客户端
    {
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"), 9899);//连接到服务器
        connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));//信号和槽函数
    }
}
//服务器槽函数
void NetGame::slotNewConnection()
{
    if(_socket) return;

    _socket = _server->nextPendingConnection();//返回用来通信的套接字
    connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));//连接信号

    /* 产生随机数来决定谁走红色 */
    bool bRedSide = qrand()%2>0;
    init(bRedSide);

    /* 发送给对方，两个字节 */
    QByteArray buf;
    buf.append(1);
    buf.append(bRedSide?0:1);
    _socket->write(buf);
}
//悔棋
void NetGame::back()
{
    if(_bRedTurn != _bSide)
        return;
    backOne();
    backOne();

    QByteArray buf;
    buf.append(3);
    _socket->write(buf);
}
//重写点击函数
void NetGame::click(int id, int row, int col)
{
    if(_bRedTurn != _bSide)//防止动了对方的棋子
        return;

    Board::click(id, row, col);

    /* 发送给对方 */
    QByteArray buf;
    buf.append(2);
    buf.append(id);
    buf.append(row);
    buf.append(col);
    _socket->write(buf);
    //写入套接字发送
}

void NetGame::backFromNetwork(QByteArray)
{
    backOne();
    backOne();
}
void NetGame::clickFromNetwork(QByteArray buf)
{
    Board::click(buf[1], 9-buf[2], 8-buf[3]);
}
//初始化棋盘
void NetGame::initFromNetwork(QByteArray buf)
{
    bool bRedSide = buf.at(1)>0?true:false;
    init(bRedSide);
}
//客户端槽函数
void NetGame::slotDataArrive()
{
    QByteArray buf = _socket->readAll(); //读取数据，字节数组
    switch (buf.at(0)) { //根据字节数组选择
    case 1:
        initFromNetwork(buf); //初始化
        break;
    case 2:
        clickFromNetwork(buf); //点击
        break;
    case 3:
        backFromNetwork(buf); //悔棋
        break;
    default:
        break;
    }
}

NetGame::~NetGame()
{

}

