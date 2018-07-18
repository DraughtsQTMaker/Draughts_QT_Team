#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <time.h>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "chesslabel.h"
#include "globalVariable.h"
#include "BackEnd/DataStructure.h"
#include "BackEnd/Checker_AlphaBetaSearch.h"
#include "BackEnd/Checker_CheckerState.h"

struct PiecePos
{
    int row;
    int col;
    int chessType;

    PiecePos(int row, int col, int type=0) :
        row(row), col(col), chessType(type)
    {}

};

struct StackElement
{
    QPair<PiecePos, PiecePos> begin_end_pos;
    QList<PiecePos> eat_pos_lst;

    StackElement(QPair<PiecePos, PiecePos> b_e_p) :
        begin_end_pos(b_e_p)
    {}

    StackElement(QPair<PiecePos,PiecePos> b_e_p, QList<PiecePos> e_p_lst) :
        begin_end_pos(b_e_p), eat_pos_lst(e_p_lst)
    {}
};

struct ChessInfo
{
    QPair<int,int> pos;
    int chessType;
    bool isExisted;

    ChessInfo(QPair<int,int> _pos, int type, bool _isExisted) :
        pos(_pos), chessType(type), isExisted(_isExisted)
    {}
};

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

    QPushButton* undoButton; //开始悔棋
    QPushButton* redoButton; //撤销悔棋

//    QList<QPair<PiecePos, PiecePos>> historyStack_human; //栈结构，记录行棋始末位置，用于悔棋(human)
//    QList<QPair<PiecePos, PiecePos>> redoStack_human; //栈结构，记录悔棋始末位置，用于撤销悔棋(human)
//    QList<QPair<PiecePos, PiecePos>> historyStack_robot; //栈结构，记录行棋始末位置，用于悔棋(robot)
//    QList<QPair<PiecePos, PiecePos>> redoStack_robot; //栈结构，记录悔棋始末位置，用于撤销悔棋(robot)

    QList<StackElement> historyStack_human;
    QList<StackElement> redoStack_human;
    QList<StackElement> historyStack_robot;
    QList<StackElement> redoStack_robot;

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

    QList<PiecePos> getMiddleEatedPoses(PiecePos begin_pos, PiecePos end_pos, QList<PiecePos> eat_lst);
    bool searchPathByEatedPoses4NonKing(PiecePos curPos, PiecePos end_pos, QList<PiecePos>& midPoses,
                                        QList<PiecePos> eat_lst, bool visited[]);
    bool searchPathByEatedPoses4King();

public:

    //成员函数
    explicit Chessboard(QWidget *parent = 0, int chessboardType = 10, int searchLayerNumber = 7);

    //当前Chessboard对象的鼠标事件
    void mouseReleaseEvent(QMouseEvent *);

    //机器方下棋
    int robotPlay();

    //记录第几回合
    int count=0;


    // 回合完毕后，写入字符串
    void  writeText(QString str);
    //悔棋 ，更改最后一行记录，写入新字符串 newStr
    void writeNewText(QString newStr);


    // 创建打谱文件  返回文件路径
    /*输入：先手名称、后手名称
                返回：创建文件名*/
    void createText(QString first, QString second);


      /*打谱TXT重命名 */
    void reNameForText(QString first, QString second,QString winner);


signals:

public slots:
    void robotAction();
    void manAction();
    void beginConsecutiveEating();
    void repealConsecutiveEating();
    void undo();
    void redo();

};

#endif // CHESSBOARD_H
