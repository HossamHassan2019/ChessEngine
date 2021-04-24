#ifndef PIECE_H
#define PIECE_H
#include <string>
//#include "board.h"
//#include <iostream>
#include<unordered_map>
using namespace std;
//abstract/base class
class Piece {
     
public:
    string position;
    bool isWhite;
    string pieceName;
    vector<string> threatenedCells;
    vector<string> captureOpnentCells;
    vector<string> legalMoves;
    
    static void calculateLegalAndCaptureMoves(int x , int y , int step ,  Piece* );
    static void move(string src , string dest);
    static void analysePieceMovement(string code);
    static void listCaptureOpnentPieces(Piece *);
    static void listLegalMoves(Piece *);
    static void listAllPossibleMoves(string code);
    static void showCaptureMoves(Piece *);
    static bool isMovable(string code);
    Piece(string pos , bool White , string pName);
    virtual void calculateMoves() = 0;
    virtual bool isPinned() = 0 ;
    virtual bool isHanging() = 0 ;
    virtual ~Piece();
    
};

class Pawn : public Piece // derive class Pawn from class Piece
{
public:

    Pawn(string pos, bool isWhite ,  string pieceName);
    void calculateMoves();
    void calculateLegalPawnMove(int , int  );
    void calculateCapturePawnMove(int , int);
    bool isPinned();
    bool isHanging();
    ~Pawn();
  
};

class Rook : public Piece
{
public:

    Rook(string pos, bool isWhite,  string pieceName );
    void calculateMoves();
    bool isPinned();
    bool isHanging();
    ~Rook();
};

class Bishop : public Piece
{
public:

    Bishop(string pos, bool isWhite,  string pieceName );
    void calculateMoves();
    bool isPinned();
    bool isHanging();
    ~Bishop();
};

class Knight : public Piece
{
public:

    Knight(string pos, bool isWhite ,  string pieceName);
    void calculateMoves();
    bool isPinned();
    bool isHanging();
    ~Knight();
};

class Queen : public Piece
{
public:

    Queen (string pos, bool isWhite ,  string pieceName);
    void calculateMoves();
    bool isPinned();
    bool isHanging();
    ~Queen();
};

class King : public Piece
{
public:

    King(string pos, bool isWhite ,  string pieceName);
    void calculateMoves();
    bool isPinned();
    bool isHanging();
    ~King();
};

#endif
