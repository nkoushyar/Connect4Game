#include <iostream>
#include <iomanip>
#include <cstring>
#include "c4lib.h"
using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 4){
    cout << "Please provide the board dimensions, either 0P|1P|2P|API, and an optional seed/board_string" << endl;
    return 1;
  }
  int ydim, xdim, seed;
  BoardValue** board = NULL;

  // set the value ydim and xdim 
  ydim = atoi(argv[1]);
  xdim = atoi(argv[2]);
  
  // new feature- API mode for node.js
  if (strcmp(argv[3], "API") == 0 || strcmp(argv[3], "api") == 0) {
    if (argc < 5) {
      cout << "Error: API mode requires a board string as the 5th argument." << endl;
      return 1;
    }
    
    string boardStr = argv[4];
    board = allocateBoard(ydim, xdim);
    
    // Parse the board string ("0012...") back into your 2D array
    // Node.js passes the string from row 0 up to ydim-1
    int strIdx = 0;
    for (int y = 0; y < ydim; y++) {
      for (int x = 0; x < xdim; x++) {
        if (strIdx < (int)boardStr.length()) {
          char c = boardStr[strIdx++];
          if (c == '1') board[y][x] = RED;
          else if (c == '2') board[y][x] = YELLOW;
          else board[y][x] = BLANK;
        }
      }
    }
    
    int targetX, targetY;
    // Assume Node.js wants a calculation for the AI player (Player 1 / Yellow)
    bool error = getUserAIInput(board, ydim, xdim, &targetY, &targetX, 1);
    
    if (error) {
      cout << "-1" << endl; // Output an error sentinel value to stdout
    } else {
      cout << targetX << endl; // Output ONLY the chosen column for Node.js to read
    }
    
    // Memory cleanup
    deallocateBoard(board, ydim);
    return 0; // Terminate early so we don't drop into standard interactive CLI loops
  }

  if(argc >= 5){
    // set the seed with the integer value from the command line
    seed = atoi(argv[4]);
  }
  else {
    // if no seed was provided we'll use the current time
    seed = time(0);
  }
  srand(seed);

  // determine the player modes
  int numP = 2;
  if(strcmp(argv[3],"1P") == 0 || strcmp(argv[3], "1p") == 0){
    numP = 1;
  }
  else if(strcmp(argv[3],"0P") == 0 || strcmp(argv[3], "0p") == 0){ 
    numP = 0;
  }
  else if(strcmp(argv[3],"test") == 0){ 
    numP = -1;
  }
  cout << "Num players: " << numP << endl;

  // initialization code
  board = allocateBoard(ydim, xdim);

  // declarations 
  int turn = 0;        // Number of turns for the game 
  int player = 0;      // MUST alternate between 0 (red) and 1 (yellow) 
                       // to represent the two players
  bool error = false;  
  bool win = false;
  bool draw = false;
  while(true){
    // Increment the turn and print the board
  
    printBoard(board, ydim, xdim);
    // Get the input, check for errors, a winner or a draw
    int x, y;
    if(numP == -1) {
      // Random vs. Random
      error = getRandomAIInput(board, ydim, xdim, &y, &x, player);
    }
    else if(numP == 0 && player == 0){
      // Random vs. User AI
      error = getRandomAIInput(board, ydim, xdim, &y, &x, player);
    }
    else if( (numP == 0 || numP == 1) && player == 1 ){
      // Random vs. User AI ..or.. Human vs. User AI
      error = getUserAIInput(board, ydim, xdim, &y, &x, player);
    }
    else {
      // Human vs. user AI ..or.. Human vs. Human
      error = getNextHumanInput(board, ydim, xdim, &y, &x, player);
    }

    if(error){
      break;
    }
    turn++;
    if(hasWon(board, ydim, xdim, y, x, player)){
      win = true;
      break;
    }
    if(isDraw(board, ydim, xdim)){
      draw = true;
      break;
    }
   
    // switch the player
    player = 1 - player;
  }

  // output the expected messages 
  printBoard(board, ydim, xdim);
  if(win) {
    if(player == 1){
      cout << "Yellow wins" <<  endl;
    } else {
      cout <<  "Red wins" <<  endl;
    }
  }
  else if(draw) {
    cout <<  "Draw" <<  endl;
  }
  else if(error) {
    cout <<  "Early exit" <<  endl;
  }
  cout <<  "Last turn " << turn <<  endl;

  // final cleanup 
  deallocateBoard(board, ydim);
  return 0;
}
