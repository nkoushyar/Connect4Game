#ifndef C4LIB_H
#define C4LIB_H

// Definition of the global enum used across the library
enum BoardValue { 
    BLANK = 0, 
    RED = 1, 
    YELLOW = 2 
};

// Global array mapping player IDs to BoardValues
extern enum BoardValue playerToValue[2];

// Function declarations
int findYValue(BoardValue** board, int ydim, int x);
BoardValue** allocateBoard(int ydim, int xdim);
void deallocateBoard(BoardValue** board, int ydim);
void printBoard(BoardValue** board, int ydim, int xdim);
bool getNextHumanInput(BoardValue** board, int ydim, int xdim, int *y, int *x, int currentPlayer);
bool hasWon(BoardValue** board, int ydim, int xdim, int sy, int sx, int currentPlayer);
bool isDraw(BoardValue** board, int ydim, int xdim);
bool getUserAIInput(BoardValue** board, int ydim, int xdim, int *y, int *x, int currentPlayer);
bool getRandomAIInput(BoardValue** board, int ydim, int xdim, int *y, int *x, int currentPlayer);

#endif // C4LIB_H
