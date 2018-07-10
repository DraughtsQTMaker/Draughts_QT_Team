//
//  Checker_CheckerState.h
//  Checker
//
//  Created by Ding Meng on 5/12/15.
//
//

#ifndef __Checker__Checker_CheckerState__
#define __Checker__Checker_CheckerState__

#include <stdio.h>
#include <vector>
#include <list>
#include <algorithm>
//#include <QDebug>
#include "DataStructure.h"
#include <QtCore>

inline QByteArray convertToByteArray(const ChessStatus& chessStatus) {
    return QByteArray::fromRawData((char *)chessStatus.redPieceList, 20 * sizeof(SingleChessPiece)) + QByteArray::fromRawData((char *)chessStatus.blackPieceList, 20 * sizeof(SingleChessPiece));
}
//need to be implemented
class Checker_CheckerState {
public:
    Checker_CheckerState(const ChessStatus& currentChessStatus, bool nextTurnIsBlack, const std::list<SingleChessPiece> &, const int rows = 8, const int cols = 8, const int depth = 0);
    Checker_CheckerState(const Checker_CheckerState *);
    ~Checker_CheckerState();
    
    static void setBlackPieceMovingDirection(int dir = -1)
    {
        blackPieceMovingDirection = dir;
    }
    
private:
    //save the input data structure. convenience for making next Checker_CheckerState();
    ChessStatus currentChessStatus;

    int currentDepth;
    std::vector<SingleChessPiece> redNormalPieceList;
    std::vector<SingleChessPiece> blackNormalPieceList;
    
    std::vector<SingleChessPiece> redKingPieceList;
    std::vector<SingleChessPiece> blackKingPieceList;
    
    //look-up table for whether position (row, col) is occupied by a chess piece
    bool *piecePositionMap;
    bool *redPiecePositionMap;
    bool *blackPiecePositionMap;
    bool *barrierPositionMap;
    
    //the size of the chess board.
    int rows, cols;
    
    //nextTurn is used to indicate whether next turn is black. 'true' means black, 'false' means red
    bool nextTurn;
    
    //record the consecutive move steps to the chess status represented by this object from the last chess status.
    std::list<SingleChessPiece> consecutiveMoveStepList;
    const static double weight[8];
    static bool evaluateBlackPiece;
 
    
public:
    double value;      //evaluation of current chess status
    static int blackPieceMovingDirection;
    
private:    //private member functions;
    
    //getSingleXXXXPiecePossibleFirstMove() will return a list which contains all possible next single not-eating step move
    //for the given piece and the chess state.
    static std::list<SingleChessPiece> getSingleNormalPiecePossibleFirstMove(const Checker_CheckerState*, const SingleChessPiece &piece);
    static std::list<SingleChessPiece> getSingleKingPiecePossibleFirstMove(const Checker_CheckerState*, const SingleChessPiece& piece);
    
    //getSingleXXXXPiecePossibleFirstEatingMove() will return a list which contains all possible next single eating step move
    //for the given piece and the chess state.
    static std::list<SingleChessPiece> getSingleNormalPiecePossibleFirstEatingMove(const Checker_CheckerState*, const SingleChessPiece& piece, bool fasterVersion = false, int flag = 0);
    
    static std::list<SingleChessPiece> getSingleKingPiecePossibleFirstEatingMove(const Checker_CheckerState*,  const SingleChessPiece& piece, bool fasterVersion = false, int flag = 0);
  
    //get the list of pieces which have possible eating move.
    std::vector<SingleChessPiece > getPieceEatingMoveList(const std::vector<SingleChessPiece> &, std::list<SingleChessPiece> (*getSinglePiecePossibleFirstEatingMove) (const Checker_CheckerState*, const SingleChessPiece& piece, bool, int), int flag = 0 ) const;
 
    //get the pair list of (beforemove, afterFirstMove) of pieces which have non-eating move.
    std::vector<std::pair<SingleChessPiece, SingleChessPiece > > getPieceMovePairList(const std::vector<SingleChessPiece> & normalPieceList, const std::vector<SingleChessPiece> & kingPieceList);
    
    static Checker_CheckerState* getFinalChessStateCoreMoving(const Checker_CheckerState *, SingleChessPiece beforeMove, SingleChessPiece afterFirstMove);
    
    //getMovingFinalChessState() generate the list of possible next chess states presented in class Checker_CheckerState form
    //according to each (beforemove, afterFirstMove) pair.
    std::list<Checker_CheckerState*> getMovingFinalChessState(const std::vector<std::pair<SingleChessPiece, SingleChessPiece> > &pairList, Checker_CheckerState* (*getFinalChessStateCoreM) (const Checker_CheckerState *, SingleChessPiece, SingleChessPiece) );
    
    
    //find the longest eating sequences.
    static std::list<std::pair<Checker_CheckerState *, int> > getFinalChessStateCoreKingEating(const Checker_CheckerState *, const SingleChessPiece& beforeMove, bool isFirstLevel = false);
    static std::list<std::pair<Checker_CheckerState *, int> > getFinalChessStateCoreNormalEating(const Checker_CheckerState *, const SingleChessPiece& beforeMove, bool isFirstLevel = false);
    
    //modifyFinalStateAfterConsecutiveEating function will check whether a normal piece need to be upgraded to king piece after a consecutive
    //eating steps;
    static Checker_CheckerState* modifyFinalStateAfterConsecutiveEating(const Checker_CheckerState*, const SingleChessPiece& );

    //since there exists consecutive-eating situations, getEatingFinalChessState() functions
    //will return the final chess status according to the current chess status and list of pieces having possible eating move.
    std::list<Checker_CheckerState*> getEatingFinalChessState(const std::vector<SingleChessPiece> &, bool isFirstLevel, std::list<std::pair<Checker_CheckerState *, int> > (*getFinalChessStateCoreE) (const Checker_CheckerState *, const SingleChessPiece&, bool) );
    
  
    
    ///functions to check whether a given chess square (row, col) is occupied by the given color of the piece (*map);
    inline bool leftBottom (bool *map, int refRow, int refCol, int deltaRow = 1, int deltaCol = -1 ) const
    {
        //for the coordinates outside the chessboard we simply treat this situation as Occupied.
        if(refRow + deltaRow >= rows || refCol + deltaCol < 0)
            return true;
        return map[(refRow + deltaRow) * cols + refCol + deltaCol ];
    };
    
    bool rightBottom (bool *map, int refRow, int refCol, int deltaRow = 1, int deltaCol = +1 ) const
    {
        //for the coordinates outside the chessboard we simply treat this situation as Occupied.
        if(refRow + deltaRow >= rows || refCol + deltaCol >= cols)
            return true;
        return map[(refRow + deltaRow) * cols + refCol + deltaCol ];
    }
    
    bool leftUpper(bool *map, int refRow, int refCol, int deltaRow = -1, int deltaCol = -1 ) const
    {
        //for the coordinates outside the chessboard we simply treat this situation as Occupied.
        if(refRow + deltaRow < 0 || refCol + deltaCol < 0)
            return true;
        return map[(refRow + deltaRow) * cols + refCol + deltaCol ];
    }
    
    bool rightUpper(bool *map, int refRow, int refCol, int deltaRow = -1, int deltaCol = +1 ) const
    {
        //for the coordinates outside the chessboard we simply treat this situation as Occupied.
        if(refRow + deltaRow < 0 || refCol + deltaCol >= cols)
            return true;
        return map[(refRow + deltaRow) * cols + refCol + deltaCol];
    }
    inline bool checkOccupied(bool *map, int refRow, int refCol, int deltaRow, int deltaCol) const
    {
        int targetRow = refRow + deltaRow;
        int targetCol = refCol + deltaCol;
        //for the coordinates outside the chessboard we simply treat this situation as Occupied.
        if( targetRow < 0 || targetCol < 0 || targetRow >= rows || targetCol >= cols)
            return true;
        return map[targetRow * cols + targetCol];
    };
    inline bool checkOccupied(bool *map, int targetRow, int targetCol) const
    {
        //for the coordinates outside the chessboard we simply treat this situation as Occupied.
        if( targetRow < 0 || targetCol < 0 || targetRow >= rows || targetCol >= cols)
            return true;
        return map[targetRow * cols + targetCol];
    };
    
    inline void setBarrier(int row, int col) { barrierPositionMap[row * rows + col] = true ;};

    //public member functions
public:
    //generate the chess status after each eating move.
    //it takes the chess status before eating, and the moving piece and its destination.
    static Checker_CheckerState* generateCheckerStateAfterAEating(const Checker_CheckerState*, const SingleChessPiece& beforeMove, const SingleChessPiece &afterMove, bool isFirstLevel = false);
    
    
    inline void setCurrentDepth(const int d) { currentDepth = d; };
    inline void currentDepthInc() { currentDepth++; };
    
    //need to be implemented
    //inline int getBitBoard() const { return bitBoard; };
    
    inline int getCurrentDepth() const { return currentDepth; };
    
    std::list<Checker_CheckerState* > getNextPossibleStateList();
    
    
    inline std::vector<SingleChessPiece> getRedNormalPieceList() const { return redNormalPieceList;} ;
    inline std::vector<SingleChessPiece> getBlackNormalPieceList() const {return blackNormalPieceList;} ;
    
    inline std::vector<SingleChessPiece> getRedKingPieceList () const {return redKingPieceList;};
    inline std::vector<SingleChessPiece> getBlackKingPieceList () const { return blackKingPieceList;};
    
    inline const ChessStatus& getCurrentChessStatus() const {
        return currentChessStatus;
    };
    inline bool getNextTurn() const {   return nextTurn; };
    
    inline std::list<SingleChessPiece> getConsecutiveMoveStepList() const
    {
        return consecutiveMoveStepList;
    };
    
    inline static void setEvaluateBlack(bool b = true)
    {
        evaluateBlackPiece = b;
    }
    
    inline static bool getEvaluateBlack() 
    {
        return evaluateBlackPiece;
    }
    
    //need to be implemented
    double getValue();
    inline void setNextTurn(bool nt) { nextTurn = nt;};
    
    double getThreatedPieceCount();
    double getValueCore(Checker_CheckerState *);
    
    //friend bool compare(std::list<Checker_CheckerState*>::iterator i, std::list<Checker_CheckerState*>::iterator j);
    
};


#endif /* defined(__Checker__Checker_CheckerState__) */
