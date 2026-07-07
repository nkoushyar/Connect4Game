const express = require('express');
const { execFile } = require('child_process');
const path = require('path');
const app = express();

app.use(express.json());
// Serve static frontend files if built
app.use(express.static(path.join(__dirname, 'client/build')));

// API endpoint that  React frontend hits
app.post('/api/get-ai-move', (req, res) => {
    const { boardString } = req.body; // e.g., "000012100..."

    // Locates  compiled C++ binary executable
    const binaryPath = path.join(__dirname, 'connect4_engine');

    // Executes the C++ binary using child_process, passing standard 6x7 dimensions and API mode
    execFile(binaryPath, ['6', '7', 'API', boardString], (error, stdout, stderr) => {
        if (error || stderr) {
            console.error(`Engine Error: ${error || stderr}`);
            return res.status(500).json({ error: "Game engine calculation failed" });
        }

        // Parse the single digit printed by std::cout in C++
        const aiMove = parseInt(stdout.trim(), 10);
        res.json({ recommendedMove: aiMove });
    });
});

const PORT = process.env.PORT || 5001;
app.listen(PORT, () => console.log(`🚀 Backend bridge spinning on port ${PORT}`));
