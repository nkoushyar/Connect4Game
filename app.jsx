import React, { useState } from 'react';

export default function App() {
  // A 6x7 grid flattened into a 42-element array (0=Blank, 1=Red/Player, 2=Yellow/AI)
  const [board, setBoard] = useState(Array(42).fill(0));
  const [isAiThinking, setIsAiThinking] = useState(false);

  // Calls the Node.js API when it is the AI's turn
  const fetchAiMove = async (currentBoard) => {
    setIsAiThinking(true);
    const boardString = currentBoard.join(''); // Converts [0,0,1,2...] to "0012..."

    try {
      const response = await fetch('/api/get-ai-move', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ boardString }),
      });
      const data = await response.json();
      const aiColumn = data.recommendedMove; // Gets the column index back from C++

      if (aiColumn !== -1) {
        makeMove(aiColumn, 2); // Drop a Yellow piece for the AI
      }
    } catch (err) {
      console.error("Error communicating with backend wrapper:", err);
    } finally {
      setIsAiThinking(false);
    }
  };

  const makeMove = (colIndex, playerValue) => {
    const newBoard = [...board];
    // Find the lowest empty row in that column (simulating physics)
    for (let row = 5; row >= 0; row--) {
      const cellIndex = row * 7 + colIndex;
      if (newBoard[cellIndex] === 0) {
        newBoard[cellIndex] = playerValue;
        setBoard(newBoard);
        
        // If human player just went (value 1), automatically trigger the AI
        if (playerValue === 1) {
          fetchAiMove(newBoard);
        }
        break;
      }
    }
  };

  return (
    <div style={{ textAlign: 'center', fontFamily: 'sans-serif', padding: '20px' }}>
      <h1>Connect 4 C++ Engine Wrapper</h1>
      <p>{isAiThinking ? "🤖 AI is scanning vectors..." : "🔴 Your turn! Pick a column."}</p>
      
      {/* 6x7 Grid Display */}
      <div style={{ display: 'grid', gridTemplateColumns: 'repeat(7, 60px)', gap: '10px', justifyContent: 'center', background: '#0a58ca', padding: '15px', borderRadius: '10px', width: 'max-content', margin: '0 auto' }}>
        {board.map((cell, index) => (
          <div 
            key={index} 
            onClick={() => cell === 0 && !isAiThinking && makeMove(index % 7, 1)}
            style={{ width: '60px', height: '60px', borderRadius: '50%', background: cell === 1 ? '#dc3545' : cell === 2 ? '#ffc107' : '#ffffff', cursor: cell === 0 ? 'pointer' : 'default', border: '2px solid #004085' }}
          />
        ))}
      </div>
    </div>
  );
}
