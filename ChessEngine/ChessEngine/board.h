#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <vector>
#include <unordered_map>
#include "piece.h"

using namespace std;


#define BOARD_X_COORD_min 0
#define BOARD_X_COORD_max 7
#define BOARD_Y_COORD_min 0
#define BOARD_Y_COORD_max 7
#define BOARD_WIDTH  8
#define BOARD_HEIGHT 8

class Board {

public:
      static unordered_map<string , int> whiteAttackCellsMap;
      static unordered_map<string , int> blackAttackCellsMap;
      static vector<vector<Piece *>>  chessBoard ;
      static unordered_map<char , int> boardMap;
      static string lastColoredMove;
      Board();
      void static startGame(void);
      void static initBoard(void);
      void static displayBoard(void);
      void static updateVectors(void);
      void static updateMaps(void);
      void static showThreatendCells(unordered_map<string ,int>& m);
      void static clearAllVectors(void);
      void static clearAllMaps(void);
      void static checkUnprotectedPieces(void);
      pair<int,int> static boardCodeToIndex(string code);
      string static IndexToBoardCode(int j , int i);
};







#endif
