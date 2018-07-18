#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <QPair>
#include <QList>

extern QString chessImageFileNames[11];
extern QList<QPair<int,int> > clickedPositionList;
extern bool blackTurn;
extern bool redGuiPieceAvailable;

extern bool consecutiveEating;

extern QString path;
extern QString first;
extern QString second;

extern bool gameOver;
#endif // GLOBALVARIABLE_H
