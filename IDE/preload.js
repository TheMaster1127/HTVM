const { app, BrowserWindow } = require('electron');
const path = require('path');

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: path.join(__dirname, 'IDE', 'preload.js'), // Adjust the path if needed
            contextIsolation: true, // Recommended for security
            enableRemoteModule: false,
            nodeIntegration: false // Recommended for security
        }
    });

    win.loadFile('index.html');
}

app.whenReady().then(createWindow);
