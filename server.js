const express = require('express');
const { execFile } = require('child_process');
const path = require('path');
const app = express();

app.use(express.json());

app.post('/api/get-ai-move', (req, res) => {
    const { boardString } = req.body; 
    
    console.log(`\n[BRIDGE LOG] Sending layout matrix string to engine: "${boardString}"`);
    const binaryPath = path.join(__dirname, 'connect4_engine');

    execFile(binaryPath, ['6', '7', 'API', boardString], (error, stdout, stderr) => {
        if (error || stderr) {
            console.error(`❌ Native Binary Calculation Failure:`, error || stderr);
            return res.status(500).json({ error: "Native AI crash" });
        }

        const calculatedColumn = parseInt(stdout.trim(), 10);
        console.log(`[BRIDGE LOG] C++ Engine chose Column Index: ${calculatedColumn}`);
        
        res.json({ recommendedMove: calculatedColumn });
    });
});

const PORT = process.env.PORT || 5001;
app.listen(PORT, () => console.log(`🚀 Backend bridge spinning on port ${PORT}`));
