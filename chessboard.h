#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "chesslabel.h"
#include "globalVariable.h"
#include "BackEnd/DataStructure.h"
#include "BackEnd/Checker_AlphaBetaSearch.h"
#include "BackEnd/Checker_CheckerState.h"


class Chessboard : public QLabel
{
    Q_OBJECT
private:
    //私有成员变量
    int chessboardType; //棋盘类型为：10*10 或者 8*8，根据棋盘类型来实现具体操作
    QList<ChessLabel *> chessLabelList;

    QPushButton * robotFirstButton;
    QPushButton * manFirstButton;
    QPushButton * beginConsecutiveEatingButton; //开始连续跳吃
    QPushButton * repealConsecutiveEatingButton;   //撤销连续跳吃
    QLabel * pathLabel;

    QGridLayout * mainLayout;

    int layerNumber;

    ChessStatus chessStatus;
    Checker_AlphaBetaSearch * robot;



    //私有成员方法
    void initializeChessLabelList();    //初始化chessLabelList
    QList<QPair<int,int> > createFourConnerPosition(QPair<int,int>);//当前位置的四个邻近位置
    QList<QPair<int,int> > createFourUnitVectorForConner();  //走子路径上的四个单位方向向量
    bool positionIsLegal(QPair<int,int>);   //判断当前位置是否合法
    void setAllChessLabelDisabled();    //设置所有ChessLabel失效

    //下面两个方法是：国跳GUI和后台引擎之间联系的纽带，
    //从前端界面中的chessLabelList中获取当前棋盘状态chessStatus.主要实现前台数据结构到后台数据结构之间的转换
    void getCurrentChessStatusFromChessLabelList();
    //根据后台得出的ChessStatus对象更新前端的chessLabelList，主要实现后台数据结构到前台数据结构的转换
    void updateChessLabelListFromChessStatus();

    //显示robot一方走棋时，棋子移动（吃子）的路径（待升级：返回一个位置List）
    void showPathOfBlackPiece(ChessStatus oldChessStatus, ChessStatus newChessStatus);
    void showPathOfRedPiece(ChessStatus oldChessStatus, ChessStatus newChessStatus);


//    //设置所有空棋位Label都是激活状态
    void setAllEmptyPositionEnabled();

//    //刷新棋盘
    void refreshChessBoard();

    //当点击一个棋子后，寻找其所有可以移动的合法位置
    void searchAvaliablePositionToMove(int, QPair<int,int>);



    //显示当前可以落子的位置
    void showPossiblePositionCanMoveTo();


    //判断当前普通子是否可以吃子
    bool canNormalPieceEatOpponent(int, QPair<int,int>);

    //判断输赢
    void judge();


public:

    //成员函数
    explicit Chessboard(QWidget *parent = 0, int chessboardType = 10, int searchLayerNumber = 7);

    //当前Chessboard对象的鼠标事件
    void mouseReleaseEvent(QMouseEvent *);

    //机器方下棋
    int robotPlay();


signals:

public slots:
    void robotAction();
    void manAction();
    void beginConsecutiveEating();
    void repealConsecutiveEating();

};

#endif // CHESSBOARD_H
