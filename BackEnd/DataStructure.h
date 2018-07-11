//
//  DataStructure.h
//  Checker
//
//  Created by Ding Meng on 5/14/15.
//
//

#ifndef Checker_DataStructure_h
#define Checker_DataStructure_h


//#define PRINT_MEMORY_OP     //for debug only
//#define PRINT_INFO           //for debug only
//#define BLACK_HASH_TABLE

#ifdef PRINT_MEMORY_OP
#define MEMORY_ALLOC(x)  (++(x))
#define MEMORY_RELEASE(x) (--(x))
#endif


#define     GET_PIECE_ROW(x)    ( (x) & 0x000F )
#define     GET_PIECE_COL(x)    (((x) & 0x00F0 ) >> 4)
#define     IS_KING(x)          ( (x) & 0x0100 )
#define     IS_BLACK(x)         ( (x) & 0x0200 )
#define     IS_EXISTED(x)       ( (x) & 0x0400 )



#define     FLY_KING            0x000002





struct SingleChessPiece
{
    unsigned short piece;   //0-3 bits stand for row number, 4-7 bits stand for col number
                            //8th bit stands for whether this piece is a king: 0 is not king, 1 is king
                            //9th bit stands for black or red piece: 0 is red, 1 is black
                            //10th bit stands for whether this piece is still existed in chess board: 1 is existed, 0 is not.
    SingleChessPiece(int row, int col, bool isKing, bool isBlack, bool isExisted)
    {
        piece = 0;
        piece |= row;
        piece |= (col << 4);
        piece |= (isKing == 1 ? 1 : 0) << 8;
        piece |= (isBlack == 1 ? 1 : 0) << 9;
        piece |= (isExisted == 1 ? 1 : 0) << 10;
    };
    SingleChessPiece() { piece = 0;};
    SingleChessPiece(unsigned short p) { piece = p;};
    SingleChessPiece(const SingleChessPiece& t) { piece = t.piece;};
    
    inline bool isKing() const      { return IS_KING(piece) != 0; };
    inline bool isBlack() const     { return IS_BLACK(piece) != 0; };
    inline bool isExisted() const   { return IS_EXISTED(piece) != 0; };
    inline int getRow() const       { return GET_PIECE_ROW(piece); };
    inline int getCol() const       { return GET_PIECE_COL(piece); };
    
    inline void setRow(int row)     { (piece &= 0xFFF0) |= row; };
    inline void setCol(int col)     { (piece &= 0xFF0F) |= (col << 4); };
    inline void setKing()           { piece |= 0x0100; };
    inline void setBeenEaten()      { piece &= 0xFBFF; };
    
    inline bool operator== (const SingleChessPiece &t) const { return piece == t.piece; };
};

//interface data structure
//gui will pass a ChessStatus-type var to Checker_AlphaBetaSearch::alphaBetaPruning()
struct ChessStatus
{
    int nCountRed;
    int nCountBlack;

    // when 8*8 type's chessboard, 12 elements are used (every side of players has 12 pieces)
    // when 10*10 type;s chessboard, 20 elements are used (every side of players has 20 pieces)
    SingleChessPiece redPieceList[20];
    SingleChessPiece blackPieceList[20];
    
};

//return value to the caller of Checker_AlphaBetaSearch::alphaBetaPruning()
struct RETURN_VALUE {
    int status;     //0 means game is not over yet; >1 means game is over, and 1 means the opposite one wins, 2 means the evaluated one wins;
    int step;
    ChessStatus chessStatusList[0];
};


#endif
