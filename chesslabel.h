#ifndef CHESSLABEL_H
#define CHESSLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include "globalVariable.h"

class ChessLabel : public QLabel
{
    Q_OBJECT

private:
    bool dormant;
    int chessType;
    int rowNumber,colNumber;
public:
    //构造函数
    ChessLabel(QWidget *parent = 0);
    ~ChessLabel();


    //Set Get 方法
    void setDormant();  //设置该Label为休眠状态
    bool isDormant();   //获取该Label的状态

    void setChessType(int);    //设置该Label可以放置的棋子类型
    int getChessType();    //获得该Label上的棋子类型

    void setPosition(int,int);  //设置Label的位置
    QPair<int,int> getPosition();   //获得Label的位置


    //鼠标事件操作
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);



};

#endif // CHESSLABEL_H
