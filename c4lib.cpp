#include "c4lib.h"
#include <iostream>
using namespace std;

// Prototype internal helper functions
/**
 * @brief returns the smallest y coordinate that is BLANK in 
 *        column x or -1 if no location is BLANK
 */
int findYValue(BoardValue** board, int ydim, int x);


// ------------------------------------------------------------
// Global variabes - the ONLY we allow in this program

// converts integer player value: 0 or 1 to appropriate enum
enum BoardValue playerToValue[2] = {RED, YELLOW};

// ----------------------------------------------------------------------


// Helper function 
int findYValue(BoardValue** board, int ydim,  int x)
{
  // You complete!
  for(int y = 0; y < ydim; y++){
    if(board[y][x] == BLANK){
      return y;
    }
  }
  return -1; //colomn full


}

BoardValue** allocateBoard(int ydim,  int xdim)
{
  // You complete!
  BoardValue** board = new BoardValue*[ydim];
  for(int y = 0; y < ydim; y++){
    board[y] = new BoardValue[xdim];
    for(int x = 0; x < xdim; x++){
      board[y][x] = BLANK;
    }
  }
  return board;

}
void deallocateBoard(BoardValue** board,  int ydim)
{
  // You complete!
  for(int y = 0; y < ydim; y++){
    delete [] board[y];
  }
  delete [] board;
}

void printBoard(BoardValue** board,  int ydim, int xdim)
{
  // Complete - Do not alter
  const char* boardToString[] = { "\U000026ab", "\U0001F534", "\U0001F7E1" }; 
                                  //  "⚫",          "🔴",         "🟡"}
  for(int y = ydim-1; y >= 0; y--){
    for(int x = 0; x < xdim; x++) {
      cout << boardToString[(int)board[y][x]] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

bool getNextHumanInput(
  BoardValue** board, 
  int ydim,  int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // You complete
  if(!(cin >> *x)){
    return true;
  }
  if(*x == -1){
    return true; // early exit
  }

  if(*x < 0 || *x >= xdim){
    return true; //early exit condition
  }
  
  int row = findYValue(board, ydim, *x);

  if(row == -1){
    return true;
  }

  *y = row;
  board[row][*x] = playerToValue[currentPlayer];
  return false;

}

bool hasWon(
  BoardValue** board,
  int ydim,  int xdim,
  int sy, int sx,
  int currentPlayer)
{
  // Keep, modify, or delete these as you desire
  const int NDIRS=4;
  const int yDirDelta[NDIRS] = {+1,  0, +1, +1};
  const int xDirDelta[NDIRS] = { 0, +1, -1, +1};
  // You complete!
  BoardValue val = playerToValue[currentPlayer];

  for(int d = 0; d < NDIRS; d++){
    int count = 1;

    //foward firection
    int y = sy + yDirDelta[d];
    int x = sx + xDirDelta[d];
    while(y >= 0 && y < ydim && x >= 0 && x < xdim && board[y][x] == val){
      count++;
      y += yDirDelta[d];
      x += xDirDelta[d];
    }

    //backward direction
    y = sy - yDirDelta[d];
    x = sx - xDirDelta[d];
    while(y >= 0 && y < ydim && x >= 0 && x < xdim && board[y][x] == val){
      count++;
      y -= yDirDelta[d];
      x -= xDirDelta[d];
    }
    if(count >= 4){
      return true;
    }
  }
  return false;
}

bool isDraw(
  BoardValue** board,
  int ydim,  int xdim)
{
  // You complete!
    for(int x = 0; x < xdim; x++){
      if(board[ydim-1][x] == BLANK){
        return false;
    }
  }
  return true;

}



bool getUserAIInput(
  BoardValue** board, 
  int ydim,  int xdim, 
  int *y, int *x,
  int currentPlayer)
{ BoardValue me = playerToValue[currentPlayer];
  BoardValue opp = playerToValue[1-currentPlayer];

  // You complete!
  // Check if the current player can win

  for(int col = 0; col < xdim; col++){
    int row = findYValue(board, ydim, col);
    if(row == -1) continue;
    
    board[row][col] = me;   // ← make EXACTLY ONE real move
    if(hasWon(board, ydim, xdim, row, col, currentPlayer)){
      *x = col;
      *y = row;
      return false;
    }
    board[row][col] = BLANK;
  }
  // Check if we need to block 
  //  We can greedily play the first blocking location since
  //  if they can win in multiple ways it does not matter which
  //  we choose.
  for(int col = 0; col < xdim; col++){
    int row = findYValue(board, ydim, col);
    if(row == -1) continue;

    board[row][col] = opp;
    if(hasWon(board, ydim, xdim, row, col, 1-currentPlayer)){
      board[row][col] = me;
      *x = col;
      *y = row;
      return false;
    }
    board[row][col] = BLANK;
  }


  // Add any other logic for how to choose a location to play
  // if neither case above occurs
  for(int col = 0; col < xdim; col++){
    int row = findYValue(board, ydim, col);
    if(row != -1){
      board[row][col] = me;
      *x = col;
      *y = row;
      return false;
    }
  }
  return true; //no moves possible
  
}

// Complete - Do not alter
bool getRandomAIInput(
  BoardValue** board, 
  int ydim, int xdim, 
  int *y, int *x,
  int currentPlayer)
{
  // Allocate variable size array (we don't know xdim when we compile)
  int* possible = new int[xdim];
  int numX = 0;
  bool error = true;
  // find all the possible columns with a blank
  for(int i = 0; i < xdim; i++){
    if(board[ydim-1][i] == BLANK){
      possible[numX++] = i;
    }
  }
  // If at least 1 column has a blank
  if(numX != 0){
    // Choose one column
    *x = possible[rand()%numX];
    *y = findYValue(board, ydim, *x);
    board[*y][*x] = playerToValue[currentPlayer];
    error = false;  
  }
  delete [] possible;
  return error;
}


