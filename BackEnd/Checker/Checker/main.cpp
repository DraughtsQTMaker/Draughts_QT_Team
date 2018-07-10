//
//  main.cpp
//  Checker
//
//  Created by Ding Meng on 6/23/16.
//  Copyright (c) 2016 Ding Meng. All rights reserved.
//

#include <iostream>


#include "../../DataStructure.h"
#include "../../Checker_AlphaBetaSearch.h"
#include "../../Checker_CheckerState.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    ChessStatus chessStatus;
    
    chessStatus.blackPieceList[0] = SingleChessPiece(4, 5, false, true, true);

    
    
    chessStatus.nCountBlack = 1;
    
    chessStatus.redPieceList[0] = SingleChessPiece(6, 5, false, false, true);
    chessStatus.redPieceList[1] = SingleChessPiece(7, 8, false, false, true);


    
    //chessStatus.redPieceList[1] = SingleChessPiece(7, 4, false, false, true);
    chessStatus.nCountRed =2;
    
    
//    Checker_CheckerState *checkerState = new Checker_CheckerState(chessStatus, false, std::list<SingleChessPiece> (), 10, 10);
//    std::list<Checker_CheckerState* > list = checkerState->getNextPossibleStateList();
    
    Checker_AlphaBetaSearch alphaBeta(9);
    Checker_CheckerState::setEvaluateBlack(false);

    RETURN_VALUE* result = alphaBeta.alphaBetaPruning(chessStatus, false, 10, 10);

    

    return 0;
}
