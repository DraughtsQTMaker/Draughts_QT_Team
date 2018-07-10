//
//  Checker_AlphaBetaSearch.h
//  
//
//  Created by Ding Meng on 5/12/15.
//
//

#ifndef ____Checker_AlphaBetaSearch__
#define ____Checker_AlphaBetaSearch__

#include <stdio.h>
#include <vector>
#include <list>
#include "Checker_CheckerState.h"
#include "DataStructure.h"

#define MAX_INT 0x7FFFFFFF
#define MIN_INT -MAX_INT



class Checker_CheckerState;
class Checker_AlphaBetaSearch {

public:
    Checker_AlphaBetaSearch(int depth = 3);
    ~Checker_AlphaBetaSearch();
    
    static int totalStep;
private:
    int maximumDepth;
    std::list<Checker_CheckerState *> nextPossibleStateList;
    
private:
    double maxValue(Checker_CheckerState *,  int alpha,  int beta);
    double minValue(Checker_CheckerState *,  int alpha,  int beta);
    
    void clearNextPossibleStateList();
    
    std::vector<ChessStatus> getConsecutiveMoveList(Checker_CheckerState *, Checker_CheckerState *);
    
public:
    RETURN_VALUE* alphaBetaPruning(const ChessStatus& currentChessStatus, bool nextTurnIsBlack, const int rows = 8, const int cols = 8);
    

};







#endif /* defined(____Checker_AlphaBetaSearch__) */
