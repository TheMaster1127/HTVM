const { app, BrowserWindow, ipcMain, dialog, shell } = require("electron");
const path = require("path");
const fs = require("fs");
const { spawn } = require("child_process");
const EventEmitter = require("events");

class CommandRunner extends EventEmitter {
  constructor(command, args) {
    super();
    this.process = spawn(command, args, { shell: true });

    this.process.stdout.on("data", (data) => {
      this.emit("output", data.toString());
    });

    this.process.stderr.on("data", (data) => {
      this.emit("error", data.toString());
    });

    this.process.on("close", (code) => {
      this.emit("close", code);
      this.process = null;
    });

    this.process.on("error", (err) => {
      this.emit("error", `Error: ${err.message}`);
    });
  }

  stop() {
    if (this.process) {
      this.process.kill();
    }
  }
}

function createWindow() {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    icon: path.join(__dirname, "icon.png"),
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
    },
  });

  win.loadFile("index.html");
}

app.whenReady().then(() => {
  createWindow();

  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") app.quit();
});

function resolveFilePath(place) {
  return path.isAbsolute(place) ? place : path.join(__dirname, place);
}

ipcMain.on("save-data", (event, { data, place }) => {
  const filePath = resolveFilePath(place);
  fs.writeFile(filePath, `${data}\n`, (err) => {
    if (err) {
      event.returnValue = `Failed to save file: ${err.message}`;
    } else {
      event.returnValue = `Data saved successfully to ${filePath}`;
    }
  });
});

ipcMain.on("get-data", (event, place) => {
  const filePath = resolveFilePath(place);
  fs.readFile(filePath, "utf8", (err, data) => {
    if (err) {
      event.returnValue = `[empty file]`;
    } else {
      event.returnValue = data;
    }
  });
});

// New IPC handler for checking file existence
ipcMain.handle("check-file-existence", async (event, filePath) => {
  return fs.promises
    .access(filePath, fs.constants.F_OK)
    .then(() => true) // File exists
    .catch(() => false); // File does not exist
});

// New IPC handler for opening file location
ipcMain.handle("open-file-location", async (event, filePath) => {
  if (fs.existsSync(filePath)) {
    shell.showItemInFolder(filePath); // Open the folder where the file is located
    return `Opened folder for ${filePath}`;
  } else {
    throw new Error(`File does not exist: ${filePath}`);
  }
});

ipcMain.handle("run-cmd", async (event, command) => {
  const [cmd, ...args] = splitCommand(command);
  const runner = new CommandRunner(cmd, args);

  runner.on("output", (data) => {
    console.log("Command Output:", data);
    event.sender.send("command-output", data);
  });

  runner.on("error", (data) => {
    console.error("Command Error:", data);
    event.sender.send("command-error", data);
  });

  return new Promise((resolve) => {
    runner.on("close", (code) => {
      event.sender.send("command-close", code);
      resolve(`Command exited with code: ${code}`);
    });
  });
});

ipcMain.handle("run-cmd-args", async (event, command, args) => {
  const runner = new CommandRunner(command, args);

  runner.on("output", (data) => {
    console.log("Command Output:", data);
    event.sender.send("command-output", data);
  });

  return new Promise((resolve) => {
    runner.on("close", (code) => {
      resolve(code);
    });
  });
});

// Handle the dropped-file event
ipcMain.on("dropped-file", (event, filePaths) => {
  console.log("Files dropped:", filePaths); // Log the received file paths

  // Example: Reading the first file's contents
  if (filePaths.length > 0) {
    const filePath = filePaths[0]; // Get the first dropped file path
    fs.readFile(filePath, "utf8", (err, data) => {
      if (err) {
        console.error(`Error reading file ${filePath}: ${err.message}`);
      } else {
        console.log(`Contents of ${filePath}:`, data); // Log the file contents
        event.reply("file-read-success", data); // Send the file contents back to the renderer
      }
    });
  }
});

// Utility function to handle splitting commands and arguments
function splitCommand(commandString) {
  const result = [];
  let current = "";
  let inQuotes = false;

  for (const char of commandString) {
    if (char === '"') {
      inQuotes = !inQuotes;
    } else if (char === " " && !inQuotes) {
      if (current.length > 0) {
        result.push(current);
        current = "";
      }
    } else {
      current += char;
    }
  }

  if (current.length > 0) {
    result.push(current);
  }

  return result;
}




// Ensure this is only registered once in the main process
ipcMain.handle('get-ide-dir-path', async () => {
  try {
    const ideDirPath = __dirname;  // This returns the directory of the current script (main.js)
    return ideDirPath;
  } catch (error) {
    console.error("Error getting IDE directory path:", error);
    return null;
  }
});

