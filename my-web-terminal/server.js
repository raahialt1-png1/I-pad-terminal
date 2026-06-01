const express = require('express');
const http = require('http');
const WebSocket = require('ws');
const { spawn } = require('child_process');
const path = require('path');

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

// Serve static frontend files from the 'public' directory
app.use(express.static(path.join(__dirname, 'public')));

wss.on('connection', (ws) => {
    console.log('New user connected to terminal session.');

    // Spawn your custom compiled C terminal binary
    const term = spawn('./mini-term');

    // Pipe binary output directly back to the web browser
    term.stdout.on('data', (data) => ws.send(data.toString()));
    term.stderr.on('data', (data) => ws.send(data.toString()));

    // Listen for keystrokes/commands from the browser
    ws.on('message', (message) => {
        // Convert incoming buffer/string and pass to binary stdin
        term.stdin.write(message.toString());
    });

    // Clean up if the user closes the browser tab
    term.on('close', () => {
        ws.close();
        console.log('Terminal session ended.');
    });

    ws.on('close', () => {
        term.kill();
    });
});

const PORT = process.env.PORT || 3000;
server.listen(PORT, () => {
    console.log(`Terminal engine live on http://localhost:${PORT}`);
});
