#include <QString>
#include "globalVariable.h"

QString chessImageFileNames[11]= {":/Images/black.png",
                             ":/Images/black1.png",

                             ":/Images/blackKing.png",
                             ":/Images/blackKing1.png",

                             ":/Images/red.png",
                             ":/Images/red1.png",

                             ":/Images/redKing.png",
                             ":/Images/redKing1.png",

                             ":/Images/avaliable.png",
                             ":/Images/avaliable1.png",

                             ":/Images/canMove.png"
                            };


QList<QPair<int,int> > clickedPositionList;
//初始下棋方为：黑方
bool blackTurn = true;

//初始时，红色棋子可点击
bool redGuiPieceAvailable = true;

bool consecutiveEating = false;

bool gameOver = false;

//QString path="./res_tmp.txt";
QString path="/Users/hiroshi831/tmp/res_tmp.txt";
QString newFileTitle = "/Users/hiroshi831/tmp/DR";

QString first="";
QString second="";
