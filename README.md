Connect 4 in C++

This project is a fully functional implementation of the classic Connect 4 game developed in C++. It explores core computer science concepts including algorithms, dynamic memory management, and basic AI development.

The program supports multiple gameplay modes and is designed with a focus on correctness, efficiency, and modular design.

Features
Multiple game modes:
2P – Human vs. Human
1P – Human vs. AI
0P – AI vs. Random AI
test – Random AI vs. Random AI (for testing)

Customizable board size via command-line arguments
Win detection (horizontal, vertical, diagonal)
Draw detection when the board is full
Input validation with early exit handling
Randomized testing using seeded simulations
Memory-safe implementation (validated with valgrind)

Technical Highlights
Implemented dynamic 2D arrays using pointers (BoardValue**)
Designed algorithms for win detection using directional scanning
Developed a rule-based AI that blocks opponent wins and prioritizes winning moves
Used modular programming with separate source and header files
Handled command-line arguments for runtime configuration
Ensured no memory leaks through proper allocation and deallocation

Technologies Used
C++
Command-line interface (CLI)
Valgrind (for memory debugging)

How to Run

Compile:
g++ connect4.cpp c4lib.cpp -o connect4

Run:
./connect4 <rows> <cols> <mode> <seed>

Example:
./connect4 6 6 2P 42

Game Rules
Players take turns dropping pieces into columns
Pieces fall to the lowest available row
First player to connect 4 in a row (horizontal, vertical, or diagonal) wins
If the board fills with no winner, the game ends in a draw
AI Behavior

The AI follows simple rules:

Win if possible
Block opponent if they are about to win
Otherwise choose a valid column
Testing
Tested winning scenarios, draw conditions, and input validation
Used randomized simulations to verify correctness
Checked memory safety with:
valgrind --tool=memcheck --leak-check=yes ./connect4 6 6 2P 0
Future Improvements
Implement Minimax algorithm for stronger AI
Add a graphical user interface (GUI)
Improve AI decision-making with heuristics
Optimize performance
Author

Nicole Koushyar
University of Southern California
Computer Science & Computer Engineering
