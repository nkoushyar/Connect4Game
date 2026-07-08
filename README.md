Connect 4 AI Game Engine & Full-Stack Application

This project is a fully functional implementation of the classic Connect 4 game developed in C++, wrapped in a modern Node.js/Express backend ecosystem, and rendered via a reactive React frontend. It explores core computer science concepts including algorithms, full-stack systems integration, dynamic memory management, and basic AI development.
The program is designed with a focus on correctness, correctness validation under load, efficiency, and modular design.

Features

Multiple game modes: 2P – Human vs. Human 1P – Human vs. AI 0P – AI vs. Random AI test – Random AI vs. Random AI (for testing)
Full-Stack Web Integration: Modern React UI coupled with a Node.js REST API wrapper that communicates with the native C++ engine via system child processes
Customizable board size via command-line arguments
Win detection (horizontal, vertical, diagonal)
Draw detection when the board is full
Input validation with early exit handling
Randomized testing using seeded simulations
Memory-safe implementation (validated with valgrind)

Technical Highlights

Implemented dynamic 2D arrays using pointers (BoardValue) with verified leak-free allocation/deallocation through Valgrind testing
Developed a full-stack web wrapper using Node.js, Express, and React to serve the engine via a clean REST API, mapping frontend game states to backend logic
Designed algorithms for win detection using directional scanning
Developed a rule-based AI that blocks opponent wins, prioritizes winning moves, and handles edge-case scenarios
Conducted automated, seeded validation testing to ensure strict algorithmic correctness and system robustness under edge-case load scenarios
Used modular programming with separate source and header files
Handled command-line arguments for runtime configuration

Technologies Used

C++
JavaScript (ES6+)
Node.js & Express
React
Command-line interface (CLI)
Valgrind (for memory debugging)


How to Run

Compile the C++ Engine: g++ connect4.cpp c4lib.cpp -o connect4_engine
Launch the Backend Bridge: node server.js (should output: `🚀 Backend bridge spinning on port 5001`) NOTE: leave this terminal open and active
Launch the Frontend Layout: Open a second terminal window, navigate to the frontend directory with `cd client`, and initiate the Vite development server by executing `npm run dev`. Once the green Vite logo appears pointing to `http://localhost:5173/`, open this link in your browser
Clear Browser Cache: If the game was already open, perform a hard refresh by pressing `Cmd + Shift + R` (or `Ctrl + F5` on Windows) to flush the browser's temporary memory

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
Checked memory safety with: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./engines/connect4_engine

Future Improvements

Implement Minimax algorithm for stronger AI
Containerize application using Docker for deployment on AWS/GCP
Improve AI decision-making with heuristics

Author
Nicole Koushyar
University of Southern California
Computer Science & Computer Engineering
