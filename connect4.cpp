#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "c4lib.h"

using namespace std;

int main(int argc, char* argv[]) {
  int ydim = 6;
  int xdim = 7;
  BoardValue** board = NULL;

  if (argc >= 4) {
    ydim = atoi(argv[1]);
    xdim = atoi(argv[2]);
  }

  // ==========================================
  // 🌟 NODE.JS API TRANSLATION BRIDGE MODE
  // ==========================================
  if (argc >= 4 && (strcmp(argv[3], "API") == 0 || strcmp(argv[3], "api") == 0)) {
    if (argc < 5) {
      cout << "-1" << endl;
      return 1;
    }
    
    string boardStr = argv[4];
    board = allocateBoard(ydim, xdim);
    
    int strIdx = 0;
    for (int y = 0; y < ydim; y++) {
      int targetRow = (ydim - 1) - y; 
      for (int x = 0; x < xdim; x++) {
        if (strIdx < (int)boardStr.length()) {
          char c = boardStr[strIdx++];
          if (c == '1') board[targetRow][x] = RED;       
          else if (c == '2') board[targetRow][x] = YELLOW; 
          else board[targetRow][x] = BLANK;               
        }
      }
    }
    
    int targetX = -1, targetY = -1;
    int aiPlayerId = 1; // 0 = RED, 1 = YELLOW per c4lib rules
    
    bool error = getUserAIInput(board, ydim, xdim, &targetY, &targetX, aiPlayerId);
    
    if (error || targetX < 0 || targetX >= xdim) {
      targetX = -1;
      for (int x = 0; x < xdim; x++) {
        if (findYValue(board, ydim, x) != -1) {
          targetX = x;
          break;
        }
      }
    }
    
    cout << targetX << endl; 
    
    deallocateBoard(board, ydim);
    return 0; 
  }

  // ==========================================
  // ORIGINAL TERMINAL CONSOLE MODE FALLBACK
  // ==========================================
  board = allocateBoard(ydim, xdim);
  int turn = RED; 
  bool gameOver = false;

  while (!gameOver) {
    printBoard(board, ydim, xdim);
    int targetX = -1, targetY = -1;
    bool error = false;

    if (turn == RED) {
      cout << "Red's Turn (Human). Enter column: ";
      cin >> targetX;
      targetY = findYValue(board, ydim, targetX);
      if (targetY == -1 || targetX < 0 || targetX >= xdim) {
        cout << "Invalid move! Try again." << endl;
        continue;
      }
      board[targetY][targetX] = RED;
    } else {
      cout << "Yellow's Turn (AI Thinking...)" << endl;
      error = getUserAIInput(board, ydim, xdim, &targetY, &targetX, 1);
      if (error) {
        cout << "AI calculation error!" << endl;
        break;
      }
      board[targetY][targetX] = YELLOW;
    }

    if (hasWon(board, ydim, xdim, targetY, targetX, (turn == RED ? 0 : 1))) {
      printBoard(board, ydim, xdim);
      cout << (turn == RED ? "Red" : "Yellow") << " wins the match!" << endl;
      gameOver = true;
    } else if (isDraw(board, ydim, xdim)) {
      printBoard(board, ydim, xdim);
      cout << "It's a draw game!" << endl;
      gameOver = true;
    }

    turn = (turn == RED) ? YELLOW : RED;
  }

  deallocateBoard(board, ydim);
  return 0;
}
