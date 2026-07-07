import React, { useState } from 'react';

export default function App() {
  const [board, setBoard] = useState(Array(42).fill(0));
  const [isAiThinking, setIsAiThinking] = useState(false);
  const [gameStatus, setGameStatus] = useState("🔴 Your turn! Pick a column.");
  const [gameOver, setGameOver] = useState(false);

  // Scans the grid horizontally, vertically, and diagonally for 4-in-a-row
  const checkWinner = (grid) => {
    // Horizontal check
    for (let r = 0; r < 6; r++) {
      for (let c = 0; c < 4; c++) {
        const i = r * 7 + c;
        if (grid[i] !== 0 && grid[i] === grid[i+1] && grid[i] === grid[i+2] && grid[i] === grid[i+3]) {
          return grid[i];
        }
      }
    }
    // Vertical check
    for (let r = 0; r < 3; r++) {
      for (let c = 0; c < 7; c++) {
        const i = r * 7 + c;
        if (grid[i] !== 0 && grid[i] === grid[i+7] && grid[i] === grid[i+14] && grid[i] === grid[i+21]) {
          return grid[i];
        }
      }
    }
    // Diagonal down-right (\)
    for (let r = 0; r < 3; r++) {
      for (let c = 0; c < 4; c++) {
        const i = r * 7 + c;
        if (grid[i] !== 0 && grid[i] === grid[i+8] && grid[i] === grid[i+16] && grid[i] === grid[i+24]) {
          return grid[i];
        }
      }
    }
    // Diagonal up-right (/)
    for (let r = 3; r < 6; r++) {
      for (let c = 0; c < 4; c++) {
        const i = r * 7 + c;
        if (grid[i] !== 0 && grid[i] === grid[i-6] && grid[i] === grid[i-12] && grid[i] === grid[i-18]) {
          return grid[i];
        }
      }
    }
    // Check for Draw
    if (!grid.includes(0)) return "Draw";
    
    return null;
  };

  const fetchAiMove = async (currentBoard) => {
    setIsAiThinking(true);
    setGameStatus("🤖 AI is scanning vectors...");
    const boardString = currentBoard.join('');

    try {
      const response = await fetch('/api/get-ai-move', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ boardString }),
      });
      const data = await response.json();
      const aiColumn = data.recommendedMove;

      if (aiColumn !== -1 && aiColumn !== undefined) {
        makeMove(aiColumn, 2, currentBoard); 
      }
    } catch (err) {
      console.error("Error communicating with backend wrapper:", err);
      setIsAiThinking(false);
    }
  };

  const makeMove = (colIndex, playerValue, currentBoardState = null) => {
    if (gameOver) return;

    const targetBoard = currentBoardState ? [...currentBoardState] : [...board];
    let placed = false;
    
    for (let row = 5; row >= 0; row--) {
      const cellIndex = row * 7 + colIndex;
      if (targetBoard[cellIndex] === 0) {
        targetBoard[cellIndex] = playerValue;
        placed = true;
        break;
      }
    }

    if (placed) {
      setBoard(targetBoard);
      
      const result = checkWinner(targetBoard);
      if (result) {
        setGameOver(true);
        setIsAiThinking(false);
        if (result === 1) setGameStatus("🎉 Red Wins! Incredible job.");
        else if (result === 2) setGameStatus("🤖 Yellow Wins! The AI outsmarted you.");
        else setGameStatus("🤝 It's a Draw!");
        return;
      }

      if (playerValue === 1) {
        fetchAiMove(targetBoard);
      } else {
        setGameStatus("🔴 Your turn! Pick a column.");
        setIsAiThinking(false);
      }
    }
  };

  const resetGame = () => {
    setBoard(Array(42).fill(0));
    setGameOver(false);
    setIsAiThinking(false);
    setGameStatus("🔴 Your turn! Pick a column.");
  };

  return (
    <div style={{ textAlign: 'center', fontFamily: 'sans-serif', padding: '20px', backgroundColor: '#1a1a1a', minHeight: '100vh' }}>
      <h1 style={{ color: '#ffffff', marginBottom: '5px' }}>Connect 4 C++ Engine</h1>
      <p style={{ color: gameOver ? '#2ecc71' : '#f1c40f', fontSize: '1.2rem', fontWeight: 'bold', minHeight: '30px' }}>
        {gameStatus}
      </p>
      
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(7, 60px)', gap: '10px', justifyContent: 'center', background: '#0a58ca', padding: '15px', borderRadius: '10px', width: 'max-content', margin: '20px auto', boxShadow: '0 10px 25px rgba(0,0,0,0.5)' }}>
        {board.map((cell, index) => {
          const colIndex = index % 7;
          return (
            <div 
              key={index} 
              onClick={() => !isAiThinking && !gameOver && makeMove(colIndex, 1)}
              style={{ 
                width: '60px', 
                height: '60px', 
                borderRadius: '50%', 
                background: cell === 1 ? '#dc3545' : cell === 2 ? '#ffc107' : '#ffffff', 
                cursor: !isAiThinking && !gameOver ? 'pointer' : 'not-allowed', 
                border: '2px solid #004085',
                boxShadow: cell !== 0 ? 'inset 0 4px 8px rgba(0,0,0,0.4)' : 'none'
              }}
            />
          );
        })}
      </div>

      {gameOver && (
        <button onClick={resetGame} style={{ padding: '10px 20px', fontSize: '1rem', background: '#2ecc71', color: '#fff', border: 'none', borderRadius: '5px', cursor: 'pointer', fontWeight: 'bold', marginTop: '10px', boxShadow: '0 4px 6px rgba(0,0,0,0.2)' }}>
          Play Again
        </button>
      )}
    </div>
  );
}
