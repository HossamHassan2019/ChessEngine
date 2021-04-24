//
//  piece.cpp
//  ChessEngine
//
//  Created by Hossam on 4/23/21.
//  Copyright © 2021 Hossam. All rights reserved.
//


#include "board.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std ;


Piece::Piece(string pos, bool White , string pName ){
    position = pos;
    isWhite = White;
    pieceName = pName;
    threatenedCells ={};
    captureOpnentCells = {};
    legalMoves = {};
}

Piece::~Piece(){
    
}

void Piece::analysePieceMovement(string code){
    pair<int,int> pr  = Board::boardCodeToIndex(code);
    Piece* p = Board::chessBoard[pr.second][pr.first];
    p->calculateMoves();
}


/* calculateLegalAndCaptureMoves function
Params:
   * src : Current position of the piece
   * dest: destination or the position that the piece will move to
Description:
   This function responsible for nulling the piece object after it is moved and to update the
   new position
   All the heavy lifiting logic is done at the end of this function , It recalculate all the vectors
   again for each piece and update Board Maps as well
*/
void Piece::move(string src , string dest){
    pair<int,int> srcIndex  = Board::boardCodeToIndex(src);
    pair<int,int> destIndex = Board::boardCodeToIndex(dest);
    
    Piece* source = Board::chessBoard[srcIndex.second][srcIndex.first];
    Piece * destination = Board::chessBoard[destIndex.second][destIndex.first];
    if(destination != nullptr && destination->isWhite != source->isWhite)
        delete destination;
    Board::chessBoard[srcIndex.second ][srcIndex.first ] = nullptr ;
    Board::chessBoard[destIndex.second][destIndex.first] = source;
    Board::chessBoard[destIndex.second][destIndex.first]->position = dest;
    
//    source->captureOpnentCells.clear();
//    source->legalMoves.clear();
    Board::clearAllVectors();
    Board::clearAllMaps();
    Board::updateVectors();
    Board::updateMaps();
}




/* calculateLegalAndCaptureMoves function
 Params:
    * xIncrement , yIncrement  : These two pramaters describe how each piece move they are considered as the direction of move
    * step: This value descripes if the piece move on step or multiple steps
 Description:
    This function calculates how many legal or free space movements and how many Opponent's piece I can capture
    for each piece
 */
void Piece::calculateLegalAndCaptureMoves(int xIncrement , int yIncremernt , int step  , Piece* p ){

    string position = p->position ;
    bool pieceColor = p->isWhite;
    
    // normal array indexes
    int i {}; int j{};
    
    //get the indexes from boardCode like g1 , h3 , ...
    pair<int,int> pr = Board::boardCodeToIndex(position);
    i = pr.second;
    j = pr.first;
    
    i+= yIncremernt;
    j+= xIncrement;
    while( i >= BOARD_Y_COORD_min && i<=BOARD_Y_COORD_max && j >=BOARD_X_COORD_min && j<=BOARD_X_COORD_max  ){

        Piece* nextPossibleMove = Board::chessBoard[i][j];
        string code = Board::IndexToBoardCode(j, i);

        if(nextPossibleMove == nullptr){
            //register legal move
            p->legalMoves.push_back(code);
        }
        else if (nextPossibleMove->isWhite != pieceColor){
            //register position of cell that can be captured
            (p->captureOpnentCells).push_back(code);
            break;
        }
        else{
            //means there is no legal move neither capture
            break;
        }
        
        //For pieces that move one step like pawn , king
        if(step == 1 )
            break ;
        
        //Increment for next iteration for pieces that have multiple movements like Queen , Rook , ..
        i+= yIncremernt;
        j+= xIncrement;

    }
}



/* listLegalMoves function

Description:
   This function list  legal moves that I can make from my current position
*/
void Piece::listLegalMoves(Piece * p ){
    if(p->legalMoves.size() != 0){
    cout << "Legal Moves for " << p->pieceName << " are : " << endl;
        for(auto move : p->legalMoves)
            cout << move << endl ;
    }
}


/* listCaptureOpnentCells function

Description:
   This function shows how many Openet's pieces I can capture from my current piece
*/
void Piece::listCaptureOpnentPieces(Piece * p){
    
    if(p->captureOpnentCells.size() != 0 ){
        cout << "This piece can capture these pieces : " << endl ;
        for(auto piece : p->captureOpnentCells)
            cout << piece << endl ;
    }
}


 void Piece::listAllPossibleMoves(string code){
     pair<int,int> pr  = Board::boardCodeToIndex(code);
     Piece* p = Board::chessBoard[pr.second][pr.first];
     listLegalMoves( p );
     listCaptureOpnentPieces(p);
}


/* isMovable function

Description:
   This function tests if the piece can move or not
*/
bool Piece::isMovable(string code){
    pair<int,int> pr  = Board::boardCodeToIndex(code);
    Piece* p = Board::chessBoard[pr.second][pr.first];
    if(p->legalMoves.size() == 0 && p->captureOpnentCells.size() == 0)
        return false;

        
    
    return true;
}



//-------------------------------------------------------------------------------------------------

Rook::Rook(string pos, bool isWhite , string pieceName):Piece{pos , isWhite , pieceName} {
   
}

Rook::~Rook(){
    
}

/* calculateMoves function

Description:
   This function calculates all moves (legal and capture) for ROOK
*/
void Rook::calculateMoves(){
       

        calculateLegalAndCaptureMoves( 1  , 0   , INT_MAX ,  this);
        calculateLegalAndCaptureMoves( -1 , 0   , INT_MAX ,  this);
        calculateLegalAndCaptureMoves( 0  , 1   , INT_MAX ,  this);
        calculateLegalAndCaptureMoves( 0  , -1  , INT_MAX ,  this);


    
}

bool Rook::isPinned(){
    return false;
}
bool Rook::isHanging(){
    return false;
}


//-------------------------------------------------------------------------------------------------

/* calculateMoves function

Description:
   This function calculates all moves (legal and capture) for PAWN
*/
Pawn::Pawn(string pos, bool isWhite, string pieceName):Piece{pos, isWhite  ,pieceName}  {
   
}

Pawn::~Pawn(){
    
}


void Pawn::calculateLegalPawnMove(int xIncrement , int yIncremernt ){
    int i{}; int j{};
    pair<int,int> pr = Board::boardCodeToIndex(this->position);
    i = pr.second;
    j = pr.first;
    i+= yIncremernt;
    j+= xIncrement;
    //move forward as a white pawn
    if(i >= BOARD_Y_COORD_min && i<=BOARD_Y_COORD_max && j >=BOARD_X_COORD_min && j<=BOARD_X_COORD_max ){
        Piece* nextPossibleMove = Board::chessBoard[i][j];
        string code = Board::IndexToBoardCode(j, i);

        if(nextPossibleMove == nullptr){
            //register legal move
            this->legalMoves.push_back(code);
        }
    }
}


void Pawn::calculateCapturePawnMove(int xIncrement , int yIncremernt){
    int i{}; int j{};
    pair<int,int> pr = Board::boardCodeToIndex(this->position);
    i = pr.second;
    j = pr.first;
    i+= yIncremernt;
    j+= xIncrement;
    if(i >= BOARD_Y_COORD_min && i<=BOARD_Y_COORD_max && j >=BOARD_X_COORD_min && j<=BOARD_X_COORD_max ){
         Piece* nextPossibleMove = Board::chessBoard[i][j];
         string code = Board::IndexToBoardCode(j, i);

        if(nextPossibleMove != nullptr &&( this->isWhite != nextPossibleMove->isWhite)){
             //register legal move
             this->captureOpnentCells.push_back(code);
        }else if(nextPossibleMove == nullptr)
             this->threatenedCells.push_back(code);
        
    }
}
void Pawn::calculateMoves(){

    if(this->isWhite){
        //move forward as a white pawn
        calculateLegalPawnMove(0,-1);
        //calculate capture moves
        calculateCapturePawnMove(1,-1);
        calculateCapturePawnMove(-1,-1);
        
    }else{
        //move forward as a black pawn
        calculateLegalPawnMove(0,1);
        //calculate capture moves
        calculateCapturePawnMove(1,1);
        calculateCapturePawnMove(-1,1);
    }
    
    
}

bool Pawn::isPinned(){
    return false;
}
bool Pawn::isHanging(){
    return false;
}


//-------------------------------------------------------------------------------------------------

/* calculateMoves function

Description:
   This function calculates all moves (legal and capture) for QUEEN
*/
Queen::Queen(string pos, bool isWhite , string pieceName):Piece{pos, isWhite,pieceName}  {
   
}

Queen::~Queen(){
    
}

void Queen::calculateMoves(){

    calculateLegalAndCaptureMoves( 1  , 0   , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( -1 , 0   , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( 0  , 1   , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( 0  , -1  , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( 1  , 1   , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( 1  , -1  , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( -1 , 1   , INT_MAX ,  this);
    calculateLegalAndCaptureMoves( -1 , -1  , INT_MAX ,  this);
     
}

bool Queen::isPinned(){
    return false;
}
bool Queen::isHanging(){
    return false;
}


//-------------------------------------------------------------------------------------------------


/* calculateMoves function

Description:
   This function calculates all moves (legal and capture) for KING
*/
King::King(string pos, bool isWhite , string pieceName):Piece{pos, isWhite,pieceName}  {
   
}

King::~King(){
    
}

void King::calculateMoves(){
        
        calculateLegalAndCaptureMoves( 1  , 0   , 1 ,  this);
        calculateLegalAndCaptureMoves( -1 , 0   , 1 ,  this);
        calculateLegalAndCaptureMoves( 0  , 1   , 1 ,  this);
        calculateLegalAndCaptureMoves( 0  , -1  , 1 ,  this);
        calculateLegalAndCaptureMoves( 1  , 1   , 1 ,  this);
        calculateLegalAndCaptureMoves( 1  , -1  , 1 ,  this);
        calculateLegalAndCaptureMoves( -1 , 1   , 1 ,  this);
        calculateLegalAndCaptureMoves( -1 , -1  , 1 ,  this);
}

bool King::isPinned(){
    return false;
}
bool King::isHanging(){
    return false;
}


//-------------------------------------------------------------------------------------------------

/* calculateMoves function

Description:
   This function calculates all moves (legal and capture) for KNIGHT
*/
Knight::Knight(string pos, bool isWhite , string pieceName):Piece{pos, isWhite,pieceName}  {
   
}

Knight::~Knight(){
    
}

void Knight::calculateMoves(){
    
        calculateLegalAndCaptureMoves( 1   , 2   , 1 ,  this);
        calculateLegalAndCaptureMoves( 2   , 1   , 1 ,  this);
        calculateLegalAndCaptureMoves( -1  , 2   , 1 ,  this);
        calculateLegalAndCaptureMoves( -2  , 1   , 1 ,  this);
        calculateLegalAndCaptureMoves( 1   , -2  , 1 ,  this);
        calculateLegalAndCaptureMoves( 2   , -1  , 1 ,  this);
        calculateLegalAndCaptureMoves( -1  , -2  , 1 ,  this);
        calculateLegalAndCaptureMoves( -2  , -1  , 1 ,  this);
}

bool Knight::isPinned(){
    return false;
}
bool Knight::isHanging(){
    return false;
}


//-------------------------------------------------------------------------------------------------

/* calculateMoves function

Description:
   This function calculates all moves (legal and capture) for BISHOP
*/
Bishop::Bishop(string pos, bool isWhite , string pieceName):Piece{pos, isWhite,pieceName}{
   
}

Bishop::~Bishop(){
    
}

void Bishop::calculateMoves(){
        calculateLegalAndCaptureMoves( 1  , 1   , INT_MAX ,  this);
        calculateLegalAndCaptureMoves( 1  , -1  , INT_MAX ,  this);
        calculateLegalAndCaptureMoves( -1 , 1   , INT_MAX ,  this);
        calculateLegalAndCaptureMoves( -1 , -1  , INT_MAX ,  this);
}

bool Bishop::isPinned(){
    return false;
}
bool Bishop::isHanging(){
    return false;
}


//-------------------------------------------------------------------------------------------------




