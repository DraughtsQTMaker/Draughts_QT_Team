//
//  Checker_CheckerState.cpp
//  Checker
//
//  Created by Ding Meng on 5/12/15.
//
//

#define FLYING_KING

#include "Checker_CheckerState.h"
#include <cstdlib>

#include <QtCore>


#ifdef PRINT_MEMORY_OP
extern int nCount_mem_op;
#endif

const double Checker_CheckerState::weight[8] = {8, 4, 4, 9, 9 ,8 ,6 ,4};

/*
 blackPieceMovingDirection is used to specify whether the row count of a black piece should be increased or decreased when moving it;
 -1 means black piece moving from bottom to up;
 +1 means black piece moving from up to bottom;
 */
int Checker_CheckerState::blackPieceMovingDirection = +1;
bool Checker_CheckerState::evaluateBlackPiece = true;




QHash<QByteArray, QPair<double, int> > blackHashTable;

Checker_CheckerState::Checker_CheckerState(const ChessStatus& currentChessStatus, bool nextTurnIsBlack, const std::list<SingleChessPiece> &moveStepList, const int rows, const int cols, const int depth)
{
    
    this->currentChessStatus = currentChessStatus;

    currentDepth = depth;
    this->rows = rows;
    this->cols = cols;
    nextTurn = nextTurnIsBlack;
    
    
    piecePositionMap = new bool[rows * cols];
    redPiecePositionMap = new bool[rows * cols];
    blackPiecePositionMap = new bool[rows * cols];
    barrierPositionMap = new bool[rows * cols];
    memset(piecePositionMap, 0, sizeof(bool) * rows * cols);
    memset(redPiecePositionMap, 0, sizeof(bool) * rows * cols);
    memset(blackPiecePositionMap, 0, sizeof(bool) * rows * cols);
    memset(barrierPositionMap, 0, sizeof(bool) * rows * cols);
    
    //generate data structure according to the given Chess Status.
    redKingPieceList.reserve(5);
    redNormalPieceList.reserve(20);
    blackNormalPieceList.reserve(20);
    blackKingPieceList.reserve(5);
    for(int i = 0; i < currentChessStatus.nCountRed; ++i)
    {
        SingleChessPiece tempPiece = currentChessStatus.redPieceList[i];
        if(tempPiece.isExisted())
        {
            if(tempPiece.isKing())
                redKingPieceList.push_back(tempPiece);
            else
                redNormalPieceList.push_back(tempPiece);
            piecePositionMap[tempPiece.getRow() * cols + tempPiece.getCol()] = true;
            redPiecePositionMap[tempPiece.getRow() * cols + tempPiece.getCol()] = true;
        }
    }
    
    for(int i = 0; i < currentChessStatus.nCountBlack; ++i)
    {
        SingleChessPiece tempPiece = currentChessStatus.blackPieceList[i];
        if(tempPiece.isExisted())
        {
            if(tempPiece.isKing())
                blackKingPieceList.push_back(tempPiece);
            else
                blackNormalPieceList.push_back(tempPiece);
            piecePositionMap[tempPiece.getRow() * cols + tempPiece.getCol()] = true;
            blackPiecePositionMap[tempPiece.getRow() * cols + tempPiece.getCol()] = true;
        }
    }
    for(auto i  = moveStepList.begin(); i != moveStepList.end(); ++i)
    {
        consecutiveMoveStepList.push_back(*i);
    }
    //consecutiveMoveStepList = moveStepList;
}


Checker_CheckerState::Checker_CheckerState(const Checker_CheckerState *t)
{
    currentDepth = t->currentDepth;
    
}

Checker_CheckerState::~Checker_CheckerState()
{
    delete [] piecePositionMap;
    delete [] redPiecePositionMap;
    delete [] blackPiecePositionMap;
    delete [] barrierPositionMap;
    //piecePositionMap = nullptr;
    redNormalPieceList.clear();
    redKingPieceList.clear();
    blackKingPieceList.clear();
    blackNormalPieceList.clear();
    consecutiveMoveStepList.clear();
}


std::list<SingleChessPiece> Checker_CheckerState::getSingleKingPiecePossibleFirstMove(const Checker_CheckerState* currentState, const SingleChessPiece& piece)
{
    //find all possible non-eatning move destiniations of the given king piece
    std::list<SingleChessPiece> list;
    if(!piece.isKing())
    {
        fprintf(stderr, "Error: piece %d in (%d, %d) to be tested should be a king piece.\n", piece.piece, piece.getRow(), piece.getCol());
        return list;
    }
    int colStepDir[2] = {-1, 1};
    int rowStepDir[2] = {-1, 1};
    int piece_row = piece.getRow();
    int piece_col = piece.getCol();
    

    int maximumStep;
#ifdef FLYING_KING
    maximumStep = currentState->rows;
#else
    maximumStep = 1;
#endif
    
    //for a king piece, we need to check all four diagonal directions
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            for(int step = 1; step < maximumStep; ++step)
            {
                int targetRow = piece_row + rowStepDir[i] * step;
                int targetCol = piece_col + colStepDir[j] * step;
                if( targetRow < 0 || targetRow > currentState->rows - 1 || targetCol < 0 ||
                   targetCol > currentState->cols - 1)
                {
                    //out of chess board, then break;
                    break;
                }
                //if chess[piece_row + rowStep[i]][piece_col + colStep[j]] is not occupied.
                if(!currentState->checkOccupied(currentState->piecePositionMap, targetRow, targetCol))
                {
                    list.push_back(SingleChessPiece(targetRow, targetCol, true, piece.isBlack(), true));
                    //          printf("possible non-eating firstMove %d(%d,%d) for the given king piece %d(%d,%d)\n",
                    //              piece, piece_row, piece_col, firstMove.piece, firstMove.getRow(), firstMove.getCol());
                }
                else
                    break;
            }
        }
    }
    return list;
}

std::list<SingleChessPiece> Checker_CheckerState::getSingleKingPiecePossibleFirstEatingMove(const Checker_CheckerState* currentState, const SingleChessPiece& piece, bool fasterVersion, int flag)
{
    //find all possible eating move destiniations of the given king piece
    std::list<SingleChessPiece> list;

    if(!piece.isKing())
    {
        fprintf(stderr, "Error: piece %d in (%d, %d) to be tested should be a king piece.\n", piece.piece, piece.getRow(), piece.getCol());
        return list;
    }
    //get the coordinates of the checking piece.
    int piece_row = piece.getRow();
    int piece_col = piece.getCol();
    
    std::vector<int> rowStep;
    std::vector<int> colStep;

    //for checking whether a king piece can eat some opposing pieces,
    //we need to check all the suqares in all four diagonal directions
    int rowStepDir[2] = {-1, +1};
    int colStepDir[2] = {-1, +1};
    
    bool *opposingMap = NULL;
    bool *currentPieceMap = NULL;
    
    //checking the consistency
    if(currentState->nextTurn)
    {
        //black's turn, piece should be a black one
        if(!piece.isBlack())
        {
            fprintf(stderr, "Error: %d should be a black one!\n", piece.piece);
            return list;
        }
        opposingMap = currentState->redPiecePositionMap;
        currentPieceMap = currentState->blackPiecePositionMap;
    }
    else
    {
        //red's turn, piece should be a red piece
        if(piece.isBlack())
        {
            fprintf(stderr, "Error: %d should be a red one!\n", piece.piece);
            return list;
        }
        opposingMap = currentState->blackPiecePositionMap;
        currentPieceMap = currentState->redPiecePositionMap;
    }
    
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            for(int step = 1; step < currentState->rows; ++step)
            {
                int targetRow = piece_row + rowStepDir[i] * step;
                int targetCol = piece_col + colStepDir[j] * step;
                if( targetRow <= 0 || targetRow >= currentState->rows - 1 || targetCol <= 0 ||
                   targetCol >= currentState->cols - 1)
                {
                    //out of chess board, then break;
                    break;
                }
                //(targetRow, targetCol) should not be a barrier
                if(currentState->checkOccupied(currentState->barrierPositionMap, targetRow, targetCol))
                    break;
                //(targetRow, targetCol) should not be occupied by the same piece
                if(currentState->checkOccupied(currentPieceMap, targetRow, targetCol))
                    break;
        
                //if there the two adjacent suqare are all occupied by two oppsoing pieces, then break;
                if(currentState->checkOccupied(opposingMap, targetRow, targetCol) && currentState->checkOccupied(opposingMap, targetRow + rowStepDir[i], targetCol + colStepDir[j])) {
                    break;
                }
                //firstly, (targetRow, targetCol) should be occupied by an opposing piece and
                //the next adjacent suqare of (targetRow, targetCol) should not be occupied by a piece with the same color as current piece
                if( currentState->checkOccupied(opposingMap, targetRow, targetCol)
                   && !currentState->checkOccupied(currentState->piecePositionMap, targetRow + rowStepDir[i], targetCol + colStepDir[j])
                   )
                {
                    //secondly, the two adjacent squares of (targetRow, targetCol) under the direction should be both empty or one empty, one is
                    //the current piece itself.
                    if( !currentState->checkOccupied(currentState->piecePositionMap, targetRow - rowStepDir[i], targetCol - colStepDir[j])
                       || (piece_row == targetRow - rowStepDir[i] && piece_col == targetCol - colStepDir[j]) )
                    {
                        //find a possible eating first move
                        SingleChessPiece firstMove(targetRow + rowStepDir[i], targetCol + colStepDir[j], piece.isKing(), piece.isBlack(), true);
                        list.push_back(firstMove);
                        if(fasterVersion)
                            return list;
//                      printf("possible firstMove %d(%d,%d) for the given king piece %d(%d,%d)\n",
//                             piece, piece_row, piece_col, firstMove.piece, firstMove.getRow(), firstMove.getCol());
                        if(flag & FLY_KING)
                        {
                        //check the possible drop positions along the direction after 'firstMove'
                            int targetRow1 = firstMove.getRow();
                            int targetCol1 = firstMove.getCol();
                            for(int step1 = step + 1; step1 < currentState->rows; ++step1)
                            {
                                targetRow1 += rowStepDir[i];
                                targetCol1 += colStepDir[j];
                                if( targetRow1 < 0 || targetRow1 > currentState->rows - 1 || targetCol1 < 0 ||
                                   targetCol1 > currentState->cols - 1)
                                {
                                    //out of chess board, then break;
                                    break;
                                }
                                if(!currentState->checkOccupied(currentState->piecePositionMap, targetRow1, targetCol1))
                                {
                                    list.push_back(SingleChessPiece(targetRow1, targetCol1, piece.isKing(), piece.isBlack(), true));
                                }
                                else
                                    break;
                            }
                        }

                        break;
                    }
                }
            }
        }
    }
    return list;
}

std::list<SingleChessPiece> Checker_CheckerState::getSingleNormalPiecePossibleFirstMove(const Checker_CheckerState* currentState, const SingleChessPiece& piece)
{
    //return list stores all possible move destiniations of the given normal piece
    std::list<SingleChessPiece> list;
    int rowStep;
    int piece_row = piece.getRow();
    int piece_col = piece.getCol();
    
    //printf("Current checking piece %d(%d, %d).\n", piece, piece.getRow(), piece.getCol());
    int colStep[2] = {-1,1};
    
    //for a non-king piece, we need to check two 'forward' diagonal directions
    if(currentState->nextTurn)
    {
        //black's turn, piece should be a black piece
        rowStep = blackPieceMovingDirection;        //for black piece
        if(!piece.isBlack())
        {
            fprintf(stderr, "Error: %d should be a black one!\n", piece.piece);
            return list;
        }
    }
    else
    {
        //red's turn
        rowStep = -blackPieceMovingDirection;        //for red piece
        if(piece.isBlack())
        {
            fprintf(stderr, "Error: %d should be a red one!\n", piece.piece);
            return list;
        }
    }
    //printf("rowStep:%d\n", rowStep);
    for(int i = 0; i < 2; ++i)
    {
        if(!currentState->checkOccupied(currentState->piecePositionMap, piece_row, piece_col, rowStep, colStep[i]))
        {
            list.push_back(SingleChessPiece (piece_row + rowStep, piece_col + colStep[i], false, piece.isBlack(), true));
//          printf("possible non-eating firstMove %d(%d,%d) for the given normal piece %d(%d,%d)\n",
//              piece, piece_row, piece_col, firstMove.piece, firstMove.getRow(), firstMove.getCol());
        }
    }
    return list;
}


std::list<SingleChessPiece> Checker_CheckerState::getSingleNormalPiecePossibleFirstEatingMove(const Checker_CheckerState* currentState, const SingleChessPiece& piece, bool fasterVersion, int flag)
{
    //return list stores all possible move destiniations of the given normal piece
    std::list<SingleChessPiece> list;
    
    int rowStep[2] = {-1, 1};
    int colStep[2] = {-1, 1};
    
    int piece_row = piece.getRow();
    int piece_col = piece.getCol();
 
    bool *opposingMap = NULL;
    if(currentState->nextTurn)
    {
        //black's turn, piece should be a black piece
        if(!piece.isBlack())
        {
            fprintf(stderr, "Error: %d should be a black one!\n", piece.piece);
            return list;
        }
        opposingMap = currentState->redPiecePositionMap;
    }
    else
    {
        //red's turn, piece should be a red piece
        if(piece.isBlack())
        {
            fprintf(stderr, "Error: %d should be a red one!\n", piece.piece);
            return list;
        }
        opposingMap = currentState->blackPiecePositionMap;
    }
    for(int i = 0; i < 2; ++i)
    {
        for(int j = 0; j < 2; ++j)
        {
            //firstly, check whether there is a oppsoing piece in four digonal adjacent squares.
            //secondly, check whether there is vacant in the adjacent square of the opposing piece to be eaten.
            if(currentState->checkOccupied(opposingMap, piece_row, piece_col, rowStep[i], colStep[j])
               && !currentState->checkOccupied(currentState->piecePositionMap, piece_row, piece_col, 2 * rowStep[i], 2 * colStep[j])
               )
            {
                list.push_back(SingleChessPiece(piece_row + rowStep[i] * 2, piece_col + colStep[j] * 2, false, piece.isBlack(), true));
                if(fasterVersion)
                    return list;
    //          printf("possible eating firstMove %d(%d,%d) for the given normal piece %d(%d,%d)\n",
    //              piece, piece_row, piece_col, firstMove.piece, firstMove.getRow(), firstMove.getCol());
            }
        }
    }
    
    return list;
}



//need to be implemented
std::list<Checker_CheckerState*> Checker_CheckerState::getNextPossibleStateList()
{

    std::list<Checker_CheckerState *> nextPossibleStateList;
    std::vector<SingleChessPiece> activeKingPieceList;
    std::vector<SingleChessPiece> activeNormalPieceList;
    if(nextTurn)
    {
        activeKingPieceList = blackKingPieceList;
        activeNormalPieceList = blackNormalPieceList;
    }
    else
    {
        activeKingPieceList = redKingPieceList;
        activeNormalPieceList = redNormalPieceList;
    }
    //check each king piece to see whether it has possible move. need to check if a king
    //and normal piece both can move
    //then which one should be considered as next move?
    
    //since for eating move, we need to choose the longest eating steps
    //so here we just need to check whether a king piece has possible eating move.
    //we store all king pieces which have a possible eating move in std::vector<SingleChessPiece> pieceEatingMoveList;
    //and using function getEatingFinalChessState() to find the longest one.
    std::vector<SingleChessPiece> pieceEatingMoveList;
    std::list<Checker_CheckerState*> tempCheckerStateListFromKingEating;
    //check the possible eating move of each king piece
#ifdef FLYING_KING
    pieceEatingMoveList = getPieceEatingMoveList(activeKingPieceList, getSingleKingPiecePossibleFirstEatingMove, FLY_KING);
#else
    pieceEatingMoveList = getPieceEatingMoveList(activeKingPieceList, getSingleKingPiecePossibleFirstEatingMove);
#endif
    
    int maxEatingCountKing = -1;
    if(pieceEatingMoveList.size())
    {
        tempCheckerStateListFromKingEating = getEatingFinalChessState(pieceEatingMoveList, true, getFinalChessStateCoreKingEating);
        for(auto i = tempCheckerStateListFromKingEating.begin(); i != tempCheckerStateListFromKingEating.end(); ++i)
            (*i)->currentDepthInc();
        maxEatingCountKing = (*tempCheckerStateListFromKingEating.begin())->consecutiveMoveStepList.size();
    }
    //check the possible eating move of each normal piece
#ifdef FLYING_KING
    pieceEatingMoveList = getPieceEatingMoveList(activeNormalPieceList, getSingleNormalPiecePossibleFirstEatingMove);
#endif
    
    if(pieceEatingMoveList.size())
    {
        std::list<Checker_CheckerState *> temp;
        temp = getEatingFinalChessState(pieceEatingMoveList, true, getFinalChessStateCoreNormalEating);
        //printf("%d\n", (*temp.begin())->consecutiveMoveStepList.size() );
        if(maxEatingCountKing > (int)(*temp.begin())->consecutiveMoveStepList.size())
        {
            //chose result from king eating
            for(auto i = temp.begin(); i != temp.end(); ++i)
            {
                delete (*i);
#ifdef PRINT_MEMORY_OP
                MEMORY_RELEASE(nCount_mem_op);
#endif
            }
            //temp.clear();
            for(auto i = tempCheckerStateListFromKingEating.begin(); i != tempCheckerStateListFromKingEating.end(); ++i)
                nextPossibleStateList.push_back(*i);
        }
        else if(maxEatingCountKing == (int)(*temp.begin())->consecutiveMoveStepList.size())
        {
            //merge result from king eating and normal eating.
            for(auto i = tempCheckerStateListFromKingEating.begin(); i != tempCheckerStateListFromKingEating.end(); ++i)
                nextPossibleStateList.push_back(*i);
            for(auto i = temp.begin(); i != temp.end(); ++i)
            {
                (*i)->currentDepthInc();
                nextPossibleStateList.push_back(*i);
            }
        }
        else
        {
            //choose result from normal eating
            for(auto i = tempCheckerStateListFromKingEating.begin(); i != tempCheckerStateListFromKingEating.end(); ++i)
            {
                delete (*i);
#ifdef PRINT_MEMORY_OP
                MEMORY_RELEASE(nCount_mem_op);
#endif
            }
            tempCheckerStateListFromKingEating.clear();
            for(auto i = temp.begin(); i != temp.end(); ++i)
            {
                (*i)->currentDepthInc();
                nextPossibleStateList.push_back(*i);
            }
        }
        temp.clear();
    }
    else
    {
        //chose result from king eating
        //temp.clear();
        for(auto i = tempCheckerStateListFromKingEating.begin(); i != tempCheckerStateListFromKingEating.end(); ++i)
        {
            nextPossibleStateList.push_back(*i);
        }
    }
    
    tempCheckerStateListFromKingEating.clear();
    pieceEatingMoveList.clear();
    if(nextPossibleStateList.size())
    {
        activeKingPieceList.clear();
        activeNormalPieceList.clear();
        return nextPossibleStateList;
    }
    //no possible eating. then find possible non-eating move
    std::vector<std::pair<SingleChessPiece, SingleChessPiece > > pairList;
    pairList = getPieceMovePairList(activeNormalPieceList, activeKingPieceList);
    if(pairList.size())
    {
        nextPossibleStateList = getMovingFinalChessState(pairList, getFinalChessStateCoreMoving);
        for(auto i = nextPossibleStateList.begin(); i != nextPossibleStateList.end(); ++i)
            (*i)->currentDepthInc();
        activeKingPieceList.clear();
        activeNormalPieceList.clear();
        pairList.clear();
        return nextPossibleStateList;
    }
    activeKingPieceList.clear();
    activeNormalPieceList.clear();
    return nextPossibleStateList;
}

std::vector<SingleChessPiece > Checker_CheckerState::getPieceEatingMoveList(const std::vector<SingleChessPiece> &pieceList, std::list<SingleChessPiece> (*getSinglePiecePossibleFirstEatingMove) (const Checker_CheckerState*, const SingleChessPiece& piece, bool, int) , int flag) const
{
    std::vector<SingleChessPiece> pieceEatingMoveList;
    pieceEatingMoveList.reserve(10);
    //check the possible eating move of each piece
    for(auto i = pieceList.begin(); i != pieceList.end(); ++i)
    {
        std::list<SingleChessPiece> tempFirstMoveList = getSinglePiecePossibleFirstEatingMove(this, *i, true, flag);
        if(tempFirstMoveList.size() != 0)
            pieceEatingMoveList.push_back(*i);
    }
    return pieceEatingMoveList;
}

double Checker_CheckerState::getThreatedPieceCount()
{
 
    double value = -100000;
    if (Checker_CheckerState::evaluateBlackPiece != nextTurn)
        value = 100000;

    std::vector<SingleChessPiece> activeKingPieceList;
    std::vector<SingleChessPiece> activeNormalPieceList;
    if(nextTurn)
    {
        activeKingPieceList = blackKingPieceList;
        activeNormalPieceList = blackNormalPieceList;
        //value = -100000;
    }
    else
    {
        activeKingPieceList = redKingPieceList;
        activeNormalPieceList = redNormalPieceList;
        //value = 100000;
    }
    int number = 0;
    
    std::vector<SingleChessPiece> pieceEatingMoveList;
    //check the possible eating move of each king piece
#ifdef FLYING_KING
    pieceEatingMoveList = getPieceEatingMoveList(activeKingPieceList, getSingleKingPiecePossibleFirstEatingMove, FLY_KING);
#else
    pieceEatingMoveList = getPieceEatingMoveList(activeKingPieceList, getSingleKingPiecePossibleFirstEatingMove);
#endif
    number = (int)pieceEatingMoveList.size();
    int maxEatingCountKing = -1;

    bool flag = false;
    if(pieceEatingMoveList.size())
    {
        std::list<Checker_CheckerState*> tempCheckerStateListFromKingEating = getEatingFinalChessState(pieceEatingMoveList, true, getFinalChessStateCoreKingEating);
        int kingPieceCount = 100, normalPieceCount;
        maxEatingCountKing = (*tempCheckerStateListFromKingEating.begin())->consecutiveMoveStepList.size();
        for(auto i = tempCheckerStateListFromKingEating.begin(); i != tempCheckerStateListFromKingEating.end(); ++i){
            double _v = getValueCore(*i);
            if(Checker_CheckerState::evaluateBlackPiece != nextTurn) { //search depth is odd.
                if( _v < value) {
                    value = _v;
                }
            }
            else {
                if( _v > value) {
                    value = _v;
                }
            }
           delete *i;
        }
        flag = true;
    }
    //check the possible eating move of each normal piece
#ifdef FLYING_KING
    pieceEatingMoveList = getPieceEatingMoveList(activeNormalPieceList, getSingleNormalPiecePossibleFirstEatingMove);
#endif
    if(pieceEatingMoveList.size())
    {
        std::list<Checker_CheckerState *> temp;
        temp = getEatingFinalChessState(pieceEatingMoveList, true, getFinalChessStateCoreNormalEating);
        int maxEatingCountNormal = (*temp.begin())->consecutiveMoveStepList.size();
        if(maxEatingCountKing < maxEatingCountNormal){
            if(Checker_CheckerState::evaluateBlackPiece != nextTurn)
                value = 100000;
            else{
                value = -100000;
            }
            for(auto i = temp.begin(); i != temp.end(); ++i){
                double _v = getValueCore(*i);
                if(Checker_CheckerState::evaluateBlackPiece != nextTurn) { //red's turn, then check how many king piece and normal piece of black side.
                    if( _v < value) {
                        value = _v;
                    }
                }
                else {
                    if( _v > value) {
                        value = _v;
                    }
                }
                delete *i;
            }
        }
        else {
            for(auto i = temp.begin(); i != temp.end(); ++i)
                delete *i;
        }
        return value;
    }
  
    if(flag)
        return value;
    
    //no possible eating. then find possible non-eating move
    value = getValueCore(this);
//    std::vector<std::pair<SingleChessPiece, SingleChessPiece > > pairList;
//    pairList = getPieceMovePairList(activeNormalPieceList, activeKingPieceList);
//    if(pairList.size())
//    {
//        std::list<Checker_CheckerState*> temp;
//        temp = getMovingFinalChessState(pairList, getFinalChessStateCoreMoving);
//        for(auto i = temp.begin(); i != temp.end(); ++i) {
//            double _v = getValueCore(*i) + (double)qrand() / RAND_MAX;
//            if(Checker_CheckerState::evaluateBlackPiece != nextTurn) { //red's turn, then check how many king piece and normal piece of black side.
//                if( _v < value) {
//                    value = _v;
//                }
//            }
//            else {
//                if( _v > value) {
//                    value = _v;
//                }
//            }
//            delete *i;
//        }
//    }
    return value;
}

double Checker_CheckerState::getValueCore(Checker_CheckerState *nextState) {
    int remainKingPieceCount;
    int remainNormalPieceCount;
    int remainOppKingPieceCount;
    int remainOppNormalPieceCount;
    if(evaluateBlackPiece) {
        remainKingPieceCount = nextState->blackKingPieceList.size();
        remainNormalPieceCount = nextState->blackNormalPieceList.size();
        remainOppKingPieceCount = nextState->redKingPieceList.size();
        remainOppNormalPieceCount = nextState->redNormalPieceList.size();
    }
    else{
        remainKingPieceCount = nextState->redKingPieceList.size();
        remainNormalPieceCount = nextState->redNormalPieceList.size();
        remainOppKingPieceCount = nextState->blackKingPieceList.size();
        remainOppNormalPieceCount = nextState->blackNormalPieceList.size();
    }
    return weight[0] + weight[1] * remainNormalPieceCount - weight[2] * remainOppNormalPieceCount + weight[3] * remainKingPieceCount - weight[4] * remainOppKingPieceCount;
}

std::vector<std::pair<SingleChessPiece, SingleChessPiece > > Checker_CheckerState::getPieceMovePairList(const std::vector<SingleChessPiece> &normalPieceList, const std::vector<SingleChessPiece> &kingPieceList)
{
    std::vector<std::pair<SingleChessPiece, SingleChessPiece > > pairList;
    pairList.reserve(50);
    //get normal piece possible non-eating move
    for(auto i = normalPieceList.begin(); i != normalPieceList.end(); ++i)
    {
        std::list<SingleChessPiece> tempFirstMoveList = getSingleNormalPiecePossibleFirstMove(this, *i);
        //printf("%d\n", tempFirstMoveList.size() );
        for(auto iter = tempFirstMoveList.begin(); iter != tempFirstMoveList.end(); ++iter)
            pairList.push_back(std::make_pair(*i, *iter));
        tempFirstMoveList.clear();
    }
    //get king piece normal possible move
    for(auto i = kingPieceList.begin(); i != kingPieceList.end(); ++i)
    {
        std::list<SingleChessPiece> tempFirstMoveList = getSingleKingPiecePossibleFirstMove(this, *i);
        for(auto iter = tempFirstMoveList.begin(); iter != tempFirstMoveList.end(); ++iter)
            pairList.push_back(std::make_pair(*i, *iter));
        tempFirstMoveList.clear();
    }
    
    return pairList;
}


std::list<Checker_CheckerState*> Checker_CheckerState::getMovingFinalChessState(const std::vector<std::pair<SingleChessPiece, SingleChessPiece> > &pairList, Checker_CheckerState* (*getFinalChessStateCoreM) (const Checker_CheckerState *, SingleChessPiece, SingleChessPiece) )
{
    std::list<Checker_CheckerState*> list;
    for(auto i = pairList.begin(); i != pairList.end(); ++i)
    {
        Checker_CheckerState* temp = getFinalChessStateCoreM(this, i->first, i->second);
        if(temp != NULL)
            list.push_back(temp);
    }
    return list;
}

std::list<Checker_CheckerState*> Checker_CheckerState::getEatingFinalChessState(const std::vector<SingleChessPiece> &pieceEatingMoveList, bool isFirstLevel, std::list<std::pair<Checker_CheckerState *, int> > (*getFinalChessStateCoreE) (const Checker_CheckerState *, const SingleChessPiece&, bool) )
{
    std::list<Checker_CheckerState*> list;
    auto i = pieceEatingMoveList.begin();
    std::list<std::pair<Checker_CheckerState *, int> > moveWithMaxEatingDepth;

    moveWithMaxEatingDepth = getFinalChessStateCoreE(this, *i, isFirstLevel);
    //add the initial chess position to the front of the consecutiveMoveStepList of the current chess status.
    for(auto j = moveWithMaxEatingDepth.begin(); j != moveWithMaxEatingDepth.end(); ++j)
        (*j).first->consecutiveMoveStepList.push_front(*i);
    //find move with max eating depth
    for(i++; i != pieceEatingMoveList.end(); ++i)
    {
        //this->consecutiveMoveStepList.back() = *i;
        std::list<std::pair<Checker_CheckerState *, int> > temp = getFinalChessStateCoreE(this, *i, isFirstLevel);
        if(moveWithMaxEatingDepth.front().second < temp.front().second)
        {
            //we should delete the object of the legacy chess status with maximum longest steps explicitly.
            for(auto j = moveWithMaxEatingDepth.begin(); j != moveWithMaxEatingDepth.end(); ++j)
                delete (*j).first;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
            moveWithMaxEatingDepth = temp;
            //add the initial chess position to the front of the consecutiveMoveStepList of the current chess status.
            for(auto j = moveWithMaxEatingDepth.begin(); j != moveWithMaxEatingDepth.end(); ++j)
                (*j).first->consecutiveMoveStepList.push_front(*i);
            //moveWithMaxEatingDepth.first->consecutiveMoveStepList.push_front(*i);
        }
        else
        {
            for(auto j = temp.begin(); j != temp.end(); ++j)
                delete (*j).first;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
        }
    }
    for(auto j = moveWithMaxEatingDepth.begin(); j != moveWithMaxEatingDepth.end(); ++j)
        list.push_back((*j).first);
    return list;
}

Checker_CheckerState* Checker_CheckerState::getFinalChessStateCoreMoving(const Checker_CheckerState *currentState, SingleChessPiece beforeMove, SingleChessPiece afterFirstMove)
{
    ChessStatus currentChess = currentState->getCurrentChessStatus();
    int nCount;
    SingleChessPiece* chessPieceList = NULL;
    int kingRow;
    if(beforeMove.isBlack() != currentState->getNextTurn())
    {
        fprintf(stderr, "Error: Next Turn %d should keep consistence to the moving piece %d.\n", beforeMove.isBlack(), currentState->getNextTurn());
        return NULL;
    }
    if(beforeMove.isBlack())
    {
        
        nCount = currentChess.nCountBlack;
        chessPieceList = currentChess.blackPieceList;
        
        if(Checker_CheckerState::blackPieceMovingDirection == 1)
            kingRow = currentState->rows - 1;
        else
            kingRow = 0;
    }
    else
    {
        //fprintf(stderr, "Next Turn is %d (%d).\n", beforeMove.isBlack(), currentState->getNextTurn());
        nCount = currentChess.nCountRed;
        chessPieceList = currentChess.redPieceList;
        
        if(Checker_CheckerState::blackPieceMovingDirection == 1)
            kingRow = 0;
        else
            kingRow = currentState->rows - 1;
    }
    int i = 0;
    for(; i < nCount; ++i)
    {
        if(beforeMove == chessPieceList[i])
        {
            //check if afterFirstMove will be a king.
            if(!afterFirstMove.isKing() && afterFirstMove.getRow() == kingRow )
                afterFirstMove.setKing();
            chessPieceList[i] = afterFirstMove;
            break;
        }
    }
    if(i == nCount)
    {
        fprintf(stderr, "Error: can not find Moving piece '%d (%d, %d)' in piece list.\n", beforeMove.piece, beforeMove.getRow(), beforeMove.getCol());
        return NULL;
    }
    std::list<SingleChessPiece> moveStepList;
    moveStepList.push_back(beforeMove);
    moveStepList.push_back(afterFirstMove);
    Checker_CheckerState* temp = new Checker_CheckerState(currentChess, !currentState->getNextTurn(), moveStepList, currentState->rows, currentState->cols, currentState->getCurrentDepth());
#ifdef PRINT_MEMORY_OP
    MEMORY_ALLOC(nCount_mem_op);
#endif
    moveStepList.clear();
    return temp;
}

bool operator < (const std::pair<Checker_CheckerState*, int> &t1, const std::pair<Checker_CheckerState*, int> &t2)
{
    return t1.second < t2.second;
}


Checker_CheckerState* Checker_CheckerState::generateCheckerStateAfterAEating(const Checker_CheckerState* currentState, const SingleChessPiece& beforeMove, const SingleChessPiece &afterMove, bool isFirstLevel)
{
    ChessStatus chessStatusAfterMove = currentState->currentChessStatus;
    SingleChessPiece* opposingPieceList = NULL;
    SingleChessPiece* currentPieceList = NULL;
    bool *opposingPieceMap = NULL;
    bool *barrierMap = currentState->barrierPositionMap;
    int nCountOpposingPiece, nCountCurrentPiece;
    if(currentState->nextTurn)
    {
        //black's ture
        opposingPieceList = chessStatusAfterMove.redPieceList;
        nCountOpposingPiece = chessStatusAfterMove.nCountRed;
        currentPieceList = chessStatusAfterMove.blackPieceList;
        nCountCurrentPiece = chessStatusAfterMove.nCountBlack;
        opposingPieceMap = currentState->redPiecePositionMap;
    }
    else
    {
        opposingPieceList = chessStatusAfterMove.blackPieceList;
        nCountOpposingPiece = chessStatusAfterMove.nCountBlack;
        currentPieceList = chessStatusAfterMove.redPieceList;
        nCountCurrentPiece = chessStatusAfterMove.nCountRed;
        opposingPieceMap = currentState->blackPiecePositionMap;
    }
    
    
    //find the coordinate of the eaten piece;
    int eatenRow, eatenCol;
    int dirRow, dirCol;
    dirRow = -afterMove.getRow() + beforeMove.getRow();
    dirRow /= abs(dirRow);
    dirCol = -afterMove.getCol() + beforeMove.getCol();
    dirCol /= abs(dirCol);
#ifdef FLYING_KING
    for(int step = 1; step < abs(-afterMove.getRow() + beforeMove.getRow()); ++step )
    {
        eatenRow = afterMove.getRow() + dirRow * step;
        eatenCol = afterMove.getCol() + dirCol * step;
        if(currentState->checkOccupied(opposingPieceMap, eatenRow, eatenCol))
        {
            break;
        }
    }
#else
    eatenRow = afterMove.getRow() + dirRow;
    eatenCol = afterMove.getCol() + dirCol;
#endif
    
    //modify opposing piece list to set the eaten piece to be non-existed;
    for(int i = 0; i < nCountOpposingPiece; ++i)
    {
        if( (opposingPieceList[i].piece & 0xFF) == (eatenCol << 4 | eatenRow))
        {
            opposingPieceList[i].setBeenEaten();
        }
    }
    //modify the current piece from the position before move to the position after move.
    for(int i = 0; i < nCountCurrentPiece; ++i)
    {
        if( currentPieceList[i] == beforeMove)
        {
            currentPieceList[i] = afterMove;
            //break;
        }
    }
    Checker_CheckerState* temp;

    std::list<SingleChessPiece> moveStepList;
    if(!isFirstLevel)
        moveStepList = currentState->consecutiveMoveStepList;
    moveStepList.push_back(afterMove);
    temp = new Checker_CheckerState(chessStatusAfterMove, currentState->getNextTurn(), moveStepList ,currentState->rows, currentState->cols, currentState->getCurrentDepth());
#ifdef PRINT_MEMORY_OP
    MEMORY_ALLOC(nCount_mem_op);
#endif
    memcpy(temp->barrierPositionMap, barrierMap, sizeof(bool) * temp->rows * temp->cols);
    temp->setBarrier(eatenRow, eatenCol);
    moveStepList.clear();
    return temp;
}

Checker_CheckerState* Checker_CheckerState::modifyFinalStateAfterConsecutiveEating(const Checker_CheckerState* finalState, const SingleChessPiece& currentMove)
{
    SingleChessPiece afterMove = currentMove;
    int kingRow;
    ChessStatus chessStatusAfterMove = finalState->currentChessStatus;
    SingleChessPiece* currentPieceList = NULL;
    int  nCountCurrentPiece;
    if(finalState->nextTurn)
    {
        //black's ture
        currentPieceList = chessStatusAfterMove.blackPieceList;
        nCountCurrentPiece = chessStatusAfterMove.nCountBlack;
        if(Checker_CheckerState::blackPieceMovingDirection == 1)
             kingRow = finalState->rows - 1;
        else
            kingRow = 0;
    }
    else
    {
        currentPieceList = chessStatusAfterMove.redPieceList;
        nCountCurrentPiece = chessStatusAfterMove.nCountRed;
        if(Checker_CheckerState::blackPieceMovingDirection == 1)
            kingRow = 0;
        else
            kingRow = finalState->rows - 1;
    }
    //if the moving piece has already been a king piece, then we just need to modify 'nextTurn'.
    if(currentMove.isKing())
    {
        ((Checker_CheckerState*)finalState)->setNextTurn(!finalState->getNextTurn());
        memset(finalState->barrierPositionMap, 0, sizeof(bool) * finalState->rows * finalState->cols);
        return (Checker_CheckerState*)finalState;
    }
    //else we need modify the moving piece to a king piece and the 'nextTrun'
    Checker_CheckerState* temp = (Checker_CheckerState*)finalState;
    if(afterMove.getRow() == kingRow)
    {
        afterMove.setKing();
        for(int i = 0; i < nCountCurrentPiece; ++i)
        {
            if( currentPieceList[i] == currentMove)
            {
                currentPieceList[i] = afterMove;
                break;
            }
        }
        std::list<SingleChessPiece> moveStepList = finalState->consecutiveMoveStepList;
        moveStepList.back() = afterMove;
        temp = new Checker_CheckerState(chessStatusAfterMove, finalState->getNextTurn(), moveStepList, finalState->rows, finalState->cols, finalState->getCurrentDepth());
#ifdef PRINT_MEMORY_OP
        MEMORY_ALLOC(nCount_mem_op);
#endif
        moveStepList.clear();
        delete finalState;
#ifdef PRINT_MEMORY_OP
        MEMORY_RELEASE(nCount_mem_op);
#endif
    }
    temp->setNextTurn(!temp->getNextTurn());
    return temp;

}

std::list<std::pair<Checker_CheckerState*, int> > Checker_CheckerState::getFinalChessStateCoreNormalEating(const Checker_CheckerState *currentState, const SingleChessPiece &beforeMove, bool isFirstLevel)
{
    //Checker_CheckerState *newState;    
    std::list<SingleChessPiece> list = getSingleNormalPiecePossibleFirstEatingMove(currentState, beforeMove, 0);
    std::list<std::pair<Checker_CheckerState*, int> > returnList;
    
    std::vector<std::pair<Checker_CheckerState*, int> > consecutiveList;
    if(list.size() != 0)
    {
        for(auto i = list.begin(); i != list.end(); ++i)
        {
            //generate new chess status according to *i.
            Checker_CheckerState* newState = generateCheckerStateAfterAEating(currentState, beforeMove, *i, isFirstLevel);
            
            std::list<std::pair<Checker_CheckerState*, int> > singlePathList = getFinalChessStateCoreNormalEating(newState, *i, false);
            for(auto j = singlePathList.begin(); j!= singlePathList.end();++j)
            {
                (*j).second++;
                consecutiveList.push_back(*j);
            }
            if(singlePathList.front().second > 1)
            {
                delete newState;
#ifdef PRINT_MEMORY_OP
                MEMORY_RELEASE(nCount_mem_op);
#endif
            }
#ifdef PRINT_INFO
            fprintf(stderr, "%d(%d,%d) %d\n",i->piece, (*i).getRow(), i->getCol(), singlePath.second);
#endif
        }
        list.clear();
        //find a max one;
        //if thers is multiple items with the same max value, then return them all
        std::sort(consecutiveList.begin(), consecutiveList.end());
        int maxValue = consecutiveList.back().second;
        for(int i = consecutiveList.size() - 1; i >= 0; --i)
        {
            if(consecutiveList.at(i).second == maxValue)
            {
                returnList.push_back(consecutiveList.at(i));
                continue;
            }
            delete consecutiveList.at(i).first;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
        }
        consecutiveList.clear();
        return returnList;
    }
    //check whether beforeMove will upgrade to king.
    //
    currentState = modifyFinalStateAfterConsecutiveEating(currentState, beforeMove);
    returnList.push_back(std::make_pair<Checker_CheckerState*, int>((Checker_CheckerState*)currentState, 0));
    
    return returnList;
}


std::list<std::pair<Checker_CheckerState*, int> >  Checker_CheckerState::getFinalChessStateCoreKingEating(const Checker_CheckerState *currentState, const SingleChessPiece &beforeMove, bool isFirstLevel)
{
#ifdef FLYING_KING
    std::list<SingleChessPiece> list = getSingleKingPiecePossibleFirstEatingMove(currentState, beforeMove, false, FLY_KING);
#else
    std::list<SingleChessPiece> list = getSingleKingPiecePossibleFirstEatingMove(currentState, beforeMove);
#endif
    std::vector<std::pair<Checker_CheckerState*, int> > consecutiveList;
    std::list<std::pair<Checker_CheckerState*, int> >  returnList;
 
    if(list.size() != 0)
    {
        for(auto i = list.begin(); i != list.end(); ++i)
        {
            //generate new chess status according to *i.
            Checker_CheckerState* newState = generateCheckerStateAfterAEating(currentState, beforeMove, *i, isFirstLevel);

            std::list<std::pair<Checker_CheckerState*, int> > singlePathList = getFinalChessStateCoreKingEating(newState, *i, false);
            for(auto j = singlePathList.begin(); j!= singlePathList.end();++j)
            {
                (*j).second++;
                consecutiveList.push_back(*j);
            }
            if(singlePathList.front().second > 1)
            {
                delete newState;
#ifdef PRINT_MEMORY_OP
                MEMORY_RELEASE(nCount_mem_op);
#endif
            }
#ifdef PRINT_INFO
            fprintf(stderr,"%d(%d,%d) %d\n",i->piece, (*i).getRow(), i->getCol(), singlePath.second);
#endif
        }
        list.clear();
        //find a max one;
        //if thers is multiple items with the same max value, then return them all
        std::sort(consecutiveList.begin(), consecutiveList.end());
        int maxValue = consecutiveList.back().second;
        for(int i = consecutiveList.size() - 1; i >= 0; --i)
        {
            if(consecutiveList.at(i).second == maxValue)
            {
                returnList.push_back(consecutiveList.at(i));
                continue;
            }
            delete consecutiveList.at(i).first;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
        }
        consecutiveList.clear();
        return returnList;
    }

    currentState = modifyFinalStateAfterConsecutiveEating(currentState, beforeMove);
    returnList.push_back(std::make_pair<Checker_CheckerState*, int>((Checker_CheckerState*)currentState, 0));
    return returnList;
}


double Checker_CheckerState::getValue()
{
 //   qDebug() << "Evaluate::" << "Turn:" << nextTurn;
    int numOfNormalPiecesEvaluated;
    int numOfKingPiecesEvaluted;
    int numOfNormalPiecesOpposite;
    int numOfKingPiecesOpposite;
    
    int numOfEvaluatePieceCanEat = 0;     //large one is good

    int numOfEvaluateNormalPieceRemained = 0;   //small one is good
    int numOfEvaluateKingPieceRemained = 0;       //small one is good
    
    if(evaluateBlackPiece == true)
    {
 //       qDebug() << "Evaluate black";
        //we need evaluate black piece
        numOfNormalPiecesEvaluated = (int)blackNormalPieceList.size();
        numOfKingPiecesEvaluted = (int)blackKingPieceList.size();

        //so opposite piece is red one
        numOfNormalPiecesOpposite = (int) redNormalPieceList.size();
        numOfKingPiecesOpposite = (int) redKingPieceList.size();
    }
    else
    {
 //        qDebug() << "Evaluate red";
        //we need evaluate red piece
        numOfNormalPiecesEvaluated = (int) redNormalPieceList.size();
        numOfKingPiecesEvaluted = (int) redKingPieceList.size();
        
        //so the opposite piece is black one
        numOfNormalPiecesOpposite = (int)blackNormalPieceList.size();
        numOfKingPiecesOpposite = (int)blackKingPieceList.size();
    }

    numOfEvaluateNormalPieceRemained = numOfNormalPiecesEvaluated;
    numOfEvaluateKingPieceRemained = numOfKingPiecesEvaluted;

    int numberOfBlackPiecesCanBeEaten = 0;
    bool nt = nextTurn;
//    setNextTurn(false);
//    numberOfBlackPiecesCanBeEaten += getThreatedPieceCount();
//    //for (SingleChessPiece tempPiece : getRedKingPieceList())
    
//    setNextTurn(true);
//    int numberOfRedPiecesCanBeEaten = 0;
//    numberOfRedPiecesCanBeEaten += getThreatedPieceCount();
    double value;
//    if(evaluateBlackPiece == true)
//    {
    value = getThreatedPieceCount();


    this->value = value;
//    qDebug() << QString("Value:%1").arg(value);
    return value;
}
