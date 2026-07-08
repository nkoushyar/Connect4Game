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


    if (argc >= 3) {
        ydim = atoi(argv[1]);
        xdim = atoi(argv[2]);
    }


    // ==========================================
    // NODE.JS API BRIDGE MODE
    // ==========================================
    if (argc >= 4 && 
        (strcmp(argv[3], "API") == 0 || strcmp(argv[3], "api") == 0)) {


        if (argc < 5) {
            cout << "-1" << endl;
            return 1;
        }


        string boardStr = argv[4];


        board = allocateBoard(ydim, xdim);


        /*
            React board:

            0  1  2  3  4  5  6
            7  8  9 10 11 12 13
            ...
            35 36 37 38 39 40 41


            C++ board:

            row 0 = bottom
            row 5 = top

            Reverse rows when importing.
        */


        int index = 0;


        for (int reactRow = 0; reactRow < ydim; reactRow++) {

            int cppRow = ydim - 1 - reactRow;


            for (int x = 0; x < xdim; x++) {


                char c = boardStr[index++];


                if (c == '1') {
                    board[cppRow][x] = RED;
                }

                else if (c == '2') {
                    board[cppRow][x] = YELLOW;
                }

                else {
                    board[cppRow][x] = BLANK;
                }

            }
        }



        int targetX = -1;
        int targetY = -1;



        // AI = Yellow
        bool error = getUserAIInput(
            board,
            ydim,
            xdim,
            &targetY,
            &targetX,
            1
        );



        if(error) {

            cout << "-1" << endl;

            deallocateBoard(board, ydim);

            return 0;
        }



        cout << targetX << endl;


        deallocateBoard(board, ydim);


        return 0;
    }



    // ==========================================
    // TERMINAL VERSION
    // ==========================================


    board = allocateBoard(ydim, xdim);


    int turn = 0; // RED starts

    bool gameOver = false;



    while(!gameOver) {


        printBoard(board, ydim, xdim);


        int targetX = -1;
        int targetY = -1;


        bool error = false;



        if(turn == 0) {


            cout << "Red's Turn. Enter column: ";

            cin >> targetX;



            if(targetX < 0 || targetX >= xdim) {

                cout << "Invalid column." << endl;

                continue;
            }



            targetY = findYValue(board, ydim, targetX);



            if(targetY == -1) {

                cout << "Column full." << endl;

                continue;
            }



            board[targetY][targetX] = RED;

        }



        else {


            cout << "Yellow AI thinking..." << endl;



            error = getUserAIInput(
                board,
                ydim,
                xdim,
                &targetY,
                &targetX,
                1
            );



            if(error) {

                cout << "AI failed." << endl;

                break;
            }


            board[targetY][targetX] = YELLOW;

        }



        if(hasWon(
            board,
            ydim,
            xdim,
            targetY,
            targetX,
            turn
        )) {


            printBoard(board, ydim, xdim);


            if(turn == 0)
                cout << "Red wins!" << endl;

            else
                cout << "Yellow wins!" << endl;


            gameOver = true;

        }


        else if(isDraw(board, ydim, xdim)) {


            printBoard(board, ydim, xdim);


            cout << "Draw!" << endl;


            gameOver = true;
        }



        turn = 1 - turn;

    }



    deallocateBoard(board, ydim);


    return 0;
}
