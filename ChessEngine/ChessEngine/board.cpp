//
//  board.cpp
//  ChessEngine
//
//  Created by Hossam on 4/23/21.
//  Copyright © 2021 Hossam. All rights reserved.
//

#include <stdio.h>
#include "board.h"
#include <iostream>
#include <unordered_map>

vector<vector<Piece *>> Board::chessBoard;
unordered_map<char , int> Board::boardMap;
string Board::lastColoredMove = "black";
unordered_map<string , int> Board::whiteAttackCellsMap = {};
unordered_map<string , int> Board::blackAttackCellsMap = {} ;
void  Board::displayBoard(){
    /* Use monospaced font to view board as uppercase letters for white and lowercase for black */

 
    cout << "                   " << endl;
    cout << "   _________________________ " << endl;

        
    for(int i = 0 ; i < 8 ; i++){
        cout << (8 - i ) << " | ";
        for(int j = 0 ; j< 8 ; j++){
            
            if(chessBoard[i][j] != NULL){
                cout << " "<<chessBoard[i][j]->pieceName << " ";
            }
            else
                cout << " . " ;
        }
        cout << "|"<< endl ;
    }
    
    cout << "   ------------------------- "  << endl;
    cout << "     a  b  c  d  e  f  g  h \n" << endl;
    
};




void Board::initBoard(){
    vector<Piece*> p{};
    for(int i = 0 ; i < 8 ; i++){
        
        if(i == 0 ){
            p.push_back(new Rook("a8" , false , "r"));
            p.push_back(new Knight("b8", false , "n"));
            p.push_back(new Bishop("c8", false , "b"));
            p.push_back(new Queen("d8", false , "q"));
            p.push_back(new King("e8", false , "k"));
            p.push_back(new Bishop("f8", false , "b"));
            p.push_back(new Knight("g8", false , "n"));
            p.push_back(new Rook("h8", false , "r"));
            

        }else if(i == 1 ){
            p.push_back(new Pawn("a7", false , "p"));
            p.push_back(new Pawn("b7", false , "p"));
            p.push_back(new Pawn("c7", false , "p"));
            p.push_back(new Pawn("d7", false , "p"));
            p.push_back(new Pawn("e7", false, "p"));
            p.push_back(new Pawn("f7", false, "p"));
            p.push_back(new Pawn("g7", false, "p"));
            p.push_back(new Pawn("h7", false, "p"));
            
        }else if(i == 6){
            p.push_back(new Pawn("a2" , true , "P"));
            p.push_back(new Pawn("b2", true, "P"));
            p.push_back(new Pawn("c2", true, "P"));
            p.push_back(new Pawn("d2", true, "P"));
            p.push_back(new Pawn("e2", true, "P"));
            p.push_back(new Pawn("f2", true, "P"));
            p.push_back(new Pawn("g2", true, "P"));
            p.push_back(new Pawn("h2", true, "P"));

        }else if(i ==  7){
            p.push_back(new Rook("a1", true, "R"));
            p.push_back(new Knight("b1", true, "N"));
            p.push_back(new Bishop("c1", true, "B"));
            p.push_back(new Queen("d1", true, "Q"));
            p.push_back(new King("e1", true, "K"));
            p.push_back(new Bishop("f1", true, "B"));
            p.push_back(new Knight("g1", true, "N"));
            p.push_back(new Rook("h1", true, "R"));
        }else{
            p.push_back(nullptr);
            p.push_back(nullptr);
            p.push_back(nullptr);
            p.push_back(nullptr);
            p.push_back(nullptr);
            p.push_back(nullptr);
            p.push_back(nullptr);
            p.push_back(nullptr);
        }
        chessBoard.push_back(p);

        p.clear();

    }
    updateVectors();
    updateMaps();
};

void  Board::clearAllVectors(void){
    for(int i = 0 ; i < BOARD_HEIGHT ; i++){
        for(int j= 0 ; j < BOARD_WIDTH ; j++){
            Piece * p = chessBoard[i][j];
            if(p != nullptr){
                p->legalMoves.clear();
                p->captureOpnentCells.clear();
                p->threatenedCells.clear();
            }
                
        }
    }
}

void  Board::clearAllMaps(void){
    whiteAttackCellsMap.clear();
    blackAttackCellsMap.clear();
}

void  Board::updateVectors(void){
    
    for(int i = 0 ; i < chessBoard.size() ; i++){
        for(int j= 0 ; j < chessBoard[0].size() ; j++){
            Piece * p = chessBoard[i][j];
            if(p != nullptr)
                Piece::analysePieceMovement(p->position);
        }
    }
}

void  Board::updateMaps(void){
    for(int i = 0 ; i < chessBoard.size() ; i++){
        for(int j= 0 ; j < chessBoard[0].size() ; j++){
                    Piece * p = chessBoard[i][j];
                    if(p!=nullptr){
                        
                        if(p->pieceName != "p" && p->pieceName != "P"){
                            for(int k = 0 ; k < p->legalMoves.size() ; k++){
                                if(p->isWhite)
                                    whiteAttackCellsMap[p->legalMoves[k]]++;
                                else
                                    blackAttackCellsMap[p->legalMoves[k]]++;
                            }
                            
                            for(int k = 0 ; k < p->captureOpnentCells.size() ; k++){
                                if(p->isWhite)
                                    whiteAttackCellsMap[p->captureOpnentCells[k]]++;
                                else
                                    blackAttackCellsMap[p->captureOpnentCells[k]]++;
                            }
                        }else{
                            
                            for(int k = 0 ; k < p->threatenedCells.size() ; k++){
                                if(p->isWhite)
                                    whiteAttackCellsMap[p->threatenedCells[k]]++;
                                else
                                    blackAttackCellsMap[p->threatenedCells[k]]++;
                            }
                            
                            for(int k = 0 ; k < p->captureOpnentCells.size() ; k++){
                                if(p->isWhite)
                                    whiteAttackCellsMap[p->captureOpnentCells[k]]++;
                                else
                                    blackAttackCellsMap[p->captureOpnentCells[k]]++;
                            }
                            
                        }
                    }
        }
    }
    
    
}





void Board::startGame(){
    displayBoard();

    cout << "If you want to terminate press exit anytime " << endl ;
    while(1){
        
            string src{};
            string dest{};
        
            cout << "cells that are threatened by White are :" <<endl ;
            showThreatendCells(whiteAttackCellsMap);
            cout << "cells that are threatened by Black are :" <<endl ;
            showThreatendCells(blackAttackCellsMap);
        
            if(lastColoredMove == "black"){
                cout << "White to play" << endl ;
            }
            else{
                cout << "Black to play" <<endl ;
            }
            cout << "Please choose the piece you want to move example d1 , g6 , .... : " ;


           
            cin >> src ;
            if(src == "exit")
                    break ;
                
         // claculate legal moves and Openent's capture pieces for the selected piece
//            Piece::analysePieceMovement(src);
           if(!Piece::isMovable(src)){
               cout << "This piece can't be moved . Please select another one " <<endl;
               continue;
           }
        
            Piece::listAllPossibleMoves(src);
                
            cout << "Please Enter where you want to move this piece : " ;
            cin >> dest ;
            
            if(dest == "exit")
                break ;
        
        

         //change the position of the current piece to a new one on the board
            Piece::move(src, dest);


            displayBoard();
            if(lastColoredMove == "black"){
                lastColoredMove = "white";
            }
            else{
                lastColoredMove = "black";
            }
    
     
    }

};

void  Board::showThreatendCells(unordered_map<string ,int>& m){
    for(auto it = m.begin() ; it != m.end() ; it++ ){
        if(it->second != 0 )
          cout << it->first << " " ;
    }
    cout << endl;
}



/* This function converts code like d1 to real i & j indexes  on board */
pair<int,int>  Board::boardCodeToIndex(string code){
    unordered_map<char , int> m = {{'a' , 0},{'b' , 1},{'c' , 2},{'d' , 3},{'e' , 4},{'f' , 5},{'g' , 6},{'h' , 7}};
    int i = 8 -(int)(code[1] - 48);
    int j = m[code[0]];
    return make_pair(j , i);
}

/* This function converts indexes like i & j to code like a1 , g6 , .....  */
string  Board::IndexToBoardCode(int j , int i){
    string code {};
    unordered_map<int , char> m = {{0,'a'},{1,'b'},{2,'c'},{3,'d'},{4 ,'e'},{5 ,'f'},{6 , 'g'},{7 ,'h'}};
    code+=m[j];
    char ch = '0' + 8 - i;
    code+=ch;
    return code;
}


