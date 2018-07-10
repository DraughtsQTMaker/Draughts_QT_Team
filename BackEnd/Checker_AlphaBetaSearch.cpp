//
//  Checker_AlphaBetaSearch.cpp
//  
//
//  Created by Ding Meng on 5/12/15.
//
//
#include <stdlib.h>
#include <math.h>
#include "Checker_AlphaBetaSearch.h"
#include "Checker_CheckerState.h"
#include <QtCore>

#ifdef PRINT_MEMORY_OP
extern int nCount_mem_op;
#endif

extern QHash<QByteArray, QPair<double, int> > blackHashTable;

int Checker_AlphaBetaSearch::totalStep = 0;

Checker_AlphaBetaSearch::Checker_AlphaBetaSearch(int depth)
{
    maximumDepth = depth;
}

Checker_AlphaBetaSearch::~Checker_AlphaBetaSearch()
{
    clearNextPossibleStateList();
}


void Checker_AlphaBetaSearch::clearNextPossibleStateList() {
    for (auto i = nextPossibleStateList.begin(); i != nextPossibleStateList.end(); i++) {
        delete (*i);
#ifdef PRINT_MEMORY_OP
        MEMORY_RELEASE(nCount_mem_op);
#endif
    }
    nextPossibleStateList.clear();
};


//need to be implemented.
RETURN_VALUE* Checker_AlphaBetaSearch::alphaBetaPruning(const ChessStatus& currentChessStatus, bool nextTurnIsBlack, const int rows, const int cols)
{
    //generate current chess state according to the current bitBoard
    Checker_CheckerState *currentState = new Checker_CheckerState(currentChessStatus, nextTurnIsBlack, std::list<SingleChessPiece>(), rows, cols);
#ifdef PRINT_MEMORY_OP
    MEMORY_ALLOC(nCount_mem_op);
#endif
    int activeKingPieceCount;
    if(nextTurnIsBlack)
        activeKingPieceCount = currentState->getBlackKingPieceList().size();
    else
        activeKingPieceCount = currentState->getRedKingPieceList().size();
    
    if(activeKingPieceCount && maximumDepth >= 11) {
        maximumDepth = 9;
    }
    currentState->setCurrentDepth(0);
    clearNextPossibleStateList();
    
    
    //initial return value
    RETURN_VALUE* return_value;
    int status = 0;
    int step = 0;
    //return_value.chessStatusList = NULL;
    int alpha = MIN_INT;
    int beta = MAX_INT;
    
    
    //prepare the next possible states list according the current checkerState.
    nextPossibleStateList = currentState->getNextPossibleStateList();
    if(nextPossibleStateList.size() == 0)
    {
        //no more steps can be performed, you win!
        delete currentState;
        return_value = (RETURN_VALUE*) malloc( sizeof(RETURN_VALUE) );
        return_value->status = 1;
        return return_value;
    }
    if(nextPossibleStateList.size() == 1) {
        //there is only one possible move, so no need to do the search.
        Checker_CheckerState* nextState = nextPossibleStateList.front();
        std::vector<ChessStatus> consecutiveMoveList = getConsecutiveMoveList(currentState, nextState);
        
        //construct the return value.
        step = (int)consecutiveMoveList.size();
        
        return_value = (RETURN_VALUE*) malloc( sizeof(RETURN_VALUE) + sizeof(ChessStatus) * step ) ;
        //ChessStatus *temp = (ChessStatus*) malloc(return_value.step * sizeof(ChessStatus));
        memcpy(return_value->chessStatusList, consecutiveMoveList.data(), sizeof(ChessStatus) * step);
        return_value->step = step;
        return_value->status = status;
        
        delete currentState;
#ifdef PRINT_MEMORY_OP
        MEMORY_RELEASE(nCount_mem_op);
#endif
        clearNextPossibleStateList();
        return return_value;
    }
    
    //the first max_value search
    currentState->value = (double)MIN_INT;
    double value = (double)MIN_INT;
//    
//    if(nextPossibleStateList.size() >= 12  && maximumDepth >= 11 ) {
//        Checker_CheckerState *t_opp = new Checker_CheckerState(currentChessStatus, !nextTurnIsBlack, std::list<SingleChessPiece>(), rows, cols);
//        std::list<Checker_CheckerState*> tempList = t_opp->getNextPossibleStateList();
//        if(tempList.size() >= 12)
//            maximumDepth = 9;
//        for(auto i = tempList.begin(); i != tempList.end(); ++i) {
//            delete *i;
//        }
//        delete t_opp;
//    }
    for(auto i = nextPossibleStateList.begin(); i != nextPossibleStateList.end(); ++i)
    {
        if(*i == NULL)
        {
            printf("******");
            continue;
        }
        Checker_CheckerState *checkerState = *i;
        
        double temp;
#ifdef  BLACK_HASH_TABLE
        //look up from hash table ---- added by DMM 2016-7-10
        if(Checker_CheckerState::getEvaluateBlack()) {
            QPair<double, int> hashValue = blackHashTable.value(convertToByteArray((*i)->getCurrentChessStatus()), QPair<double,int>(-1., -1));
            if( hashValue.second > totalStep) {
                temp = hashValue.first;
                //qDebug () << "hit";
            }
            else {
                //qDebug() << step;
                temp = minValue(checkerState, alpha, beta);
                blackHashTable.insert(convertToByteArray((*i)->getCurrentChessStatus()), QPair<double, int>(temp, totalStep) );
            }
        }
        else        //---- added by DMM 2016-7-10
            temp = minValue(checkerState, alpha, beta);
#else
        temp = minValue(checkerState, alpha, beta);
#endif
        if(value < temp)
            value = temp;
        currentState->value = currentState->value > value ? currentState->value : value;

        //update alpha
        if(alpha <= currentState->value)
            alpha = currentState->value;
        //beta pruning
        if(alpha >= beta){
            break;
        }


#ifdef PRINT_MEMORY_OP
        printf("level: %d, %d, MEMORY_OP:%d\n", 0, i, nCount_mem_op - nextPossibleStateList.size() - 1);
#endif
    }

    //double value = maxValue(currentState, MIN_INT, MAX_INT);
    
    Checker_CheckerState* nextState = NULL;
    for(auto i = nextPossibleStateList.begin(); i != nextPossibleStateList.end(); ++i)
    {
        if( fabs((*i)->value - value) < 1.e-5)
        {
            //candidateList.push_back(*i);
            nextState = (*i);
            break;
        }
    }

    if(nextState == NULL)
    {
        //no more steps can be performed, you win!
        delete currentState;
        return_value = (RETURN_VALUE*) malloc( sizeof(RETURN_VALUE) );
        return_value->status = 1;
        return return_value;
    }
    
    //Because next move may contain consecutive eating actions,
    //so we need generate all consecutive moves according to the start and the final State;
    std::vector<ChessStatus> consecutiveMoveList = getConsecutiveMoveList(currentState, nextState);
    
    //construct the return value.
    
    step = (int)consecutiveMoveList.size();
    
    
    return_value = (RETURN_VALUE*) malloc( sizeof(RETURN_VALUE) + sizeof(ChessStatus) * step ) ;
    //ChessStatus *temp = (ChessStatus*) malloc(return_value.step * sizeof(ChessStatus));
    memcpy(return_value->chessStatusList, consecutiveMoveList.data(), sizeof(ChessStatus) * step);
    return_value->step = step;
    return_value->status = status;
    
    delete currentState;
#ifdef PRINT_MEMORY_OP
    MEMORY_RELEASE(nCount_mem_op);
#endif
    
    clearNextPossibleStateList();

    return return_value;
}

double Checker_AlphaBetaSearch::maxValue(Checker_CheckerState *currentState, int alpha, int beta)
{
    
    int _level = currentState->getCurrentDepth();
    if(currentState->getCurrentDepth() == maximumDepth)
    {
        return currentState->getValue();
    }
    double value;
    currentState->value = (double)MIN_INT;
    
    std::list<Checker_CheckerState*> list;

    
    list = currentState->getNextPossibleStateList();
    
    if(list.size() == 0)
    {
        return (double)-MAX_INT;
    }
    
    value = (double)MIN_INT;
    for(auto i = list.begin(); i != list.end(); ++i)
    {
        if(*i == NULL)
        {
            printf("******");
            continue;
        }
        Checker_CheckerState *checkerState = *i;
        
        double temp;
#ifdef BLACK_HASH_TABLE
        //look up from hash table ---- added by DMM 2016-7-10
        if(Checker_CheckerState::getEvaluateBlack()) {
            QPair<double, int> hashValue = blackHashTable.value(convertToByteArray((*i)->getCurrentChessStatus()), QPair<double,int>(-1., -1));
            if( hashValue.second > totalStep) {
                temp = hashValue.first;
                //qDebug () << "hit";
            }
            else {
                //qDebug() << step;
                temp = minValue(checkerState, alpha, beta);
                blackHashTable.insert(convertToByteArray((*i)->getCurrentChessStatus()), QPair<double, int>(temp, totalStep + _level) );
            }
        }
        else        //---- added by DMM 2016-7-10
            temp = minValue(checkerState, alpha, beta);
#else
        temp = minValue(checkerState, alpha, beta);
#endif
        if(value < temp)
            value = temp;
        currentState->value = currentState->value > value ? currentState->value : value;
        
        //update alpha
        if(alpha <= currentState->value)
            alpha = currentState->value;
        //beta pruning
        if(alpha >= beta){
            //printf("beta pruning.\n");
            break;
        }
    }
    if(currentState->getCurrentDepth() > 0)
    {
        for(auto i = list.begin(); i != list.end(); ++i)
        {
            delete *i;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
        }
    }
    list.clear();
    return currentState->value;
}

double Checker_AlphaBetaSearch::minValue(Checker_CheckerState *currentState, int alpha, int beta)
{

    int _level = currentState->getCurrentDepth();
    
    if(currentState->getCurrentDepth() == maximumDepth)
        return currentState->getValue();
 
#ifdef PRINT_MEMORY_OP
    if(_level == 5)
        printf("IN: level:%d, MEMORY_OP:%d\n", _level, nCount_mem_op);
    int beforeNext = nCount_mem_op;

#endif
    double value = (double)MAX_INT;
    currentState->value = (double)MAX_INT;
    
    std::list<Checker_CheckerState*> list;
    list = currentState->getNextPossibleStateList();
    
    if(list.size() == 0)
    {
        return (double)MAX_INT;
        //return currentState->getValue();
    }
    
    std::list<Checker_CheckerState*>::iterator iter;
    for(iter = list.begin(); iter != list.end(); ++iter)
    {
        if(*iter == NULL)
            continue;
        Checker_CheckerState *checkerState = *iter;
        double temp;
        
#ifdef BLACK_HASH_TABLE
        //look up from hash table ---- added by DMM 2016-7-10
        if(Checker_CheckerState::getEvaluateBlack()) {
            //qDebug () << "existed";
            QPair<double, int> hashValue = blackHashTable.value(convertToByteArray((*iter)->getCurrentChessStatus()), QPair<double,int>(-1., -1));
            if( hashValue.second > totalStep) {
                temp = hashValue.first;
                //qDebug () << "hit";
            }
            else {
                //qDebug() << step;
                temp = maxValue(checkerState, alpha, beta);
                blackHashTable.insert(convertToByteArray((*iter)->getCurrentChessStatus()), QPair<double, int>(temp, totalStep + _level) );
            }
        }
        else        //---- added by DMM 2016-7-10
            temp = maxValue(checkerState, alpha, beta);
#else
        
        temp = maxValue(checkerState, alpha, beta);
#endif
        if(value > temp)
            value = temp;
        currentState->value = currentState->value < value ? currentState->value : value;
        
        //update beta
        if(beta >= currentState->value )
            beta = currentState->value;
        //alpha pruning
        if(beta <= alpha){
            //printf("alpha pruning.\n");
            break;
        }
    }
    if(currentState->getCurrentDepth() > 0)
    {
        for(auto i = list.begin(); i != list.end(); ++i)
        {
            delete *i;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
        }
    }
    list.clear();
#ifdef PRINT_MEMORY_OP
    if(_level == 5)
        printf("OUT: level:%d, MEMORY_OP:%d\n", _level, nCount_mem_op);
//    if(beforeNext == 58 && nCount_mem_op == 59)
//        printf("***************************");
#endif
    return currentState->value;
}


//need to be implemented
std::vector<ChessStatus> Checker_AlphaBetaSearch::getConsecutiveMoveList(Checker_CheckerState *currentChessState, Checker_CheckerState *finalChessState)
{
    std::vector<ChessStatus> stepList;
    std::list<SingleChessPiece> pieceMovingList = finalChessState->getConsecutiveMoveStepList();
    if(pieceMovingList.size() < 2){
        fprintf(stderr, "Error: there shoule be at least two elements in pieceMovingList.\n");
        pieceMovingList.clear();
        return stepList;
    }
    SingleChessPiece before, after;
    before = pieceMovingList.front();
    auto i = pieceMovingList.begin();
    ++i;
    after = *i;
    Checker_CheckerState *nextState = currentChessState;
    bool isEatingMove = false;
    if(currentChessState->getEvaluateBlack()){
        //check wether a red piece was eaten.
        if(finalChessState->getRedNormalPieceList().size() + finalChessState->getRedKingPieceList().size()
           != currentChessState->getRedNormalPieceList().size() + currentChessState->getRedKingPieceList().size())
            isEatingMove = true;
    }
    else{
        //check wether a black piece was eaten.
        if(finalChessState->getBlackNormalPieceList().size() + finalChessState->getBlackKingPieceList().size()
           != currentChessState->getBlackNormalPieceList().size() + currentChessState->getBlackKingPieceList().size())
            isEatingMove = true;
    }
    if(isEatingMove){
        nextState = Checker_CheckerState::generateCheckerStateAfterAEating(nextState, before, after);
        stepList.reserve(pieceMovingList.size());
        stepList.push_back(nextState->getCurrentChessStatus());
        for(++i; i != pieceMovingList.end(); ++i){
            Checker_CheckerState *old = nextState;
            before = after;
            after = *i;
            nextState = Checker_CheckerState::generateCheckerStateAfterAEating(nextState, before, after);
            delete old;
#ifdef PRINT_MEMORY_OP
            MEMORY_RELEASE(nCount_mem_op);
#endif
            stepList.push_back(nextState->getCurrentChessStatus());
        }
        pieceMovingList.clear();
        delete nextState;
#ifdef PRINT_MEMORY_OP
        MEMORY_RELEASE(nCount_mem_op);
#endif
        return stepList;
    }
    else
    {
        stepList.push_back(currentChessState->getCurrentChessStatus());
        stepList.push_back(finalChessState->getCurrentChessStatus());
        return stepList;
    }

}
