// Global Application State
let editor, term, fitAddon;
let currentOpenFile = null, currentDirectory = '/', openTabs = [], recentlyClosedTabs = [];
const fileSessions = new Map();
const fileBreakpoints = new Map();

// --- NEW DEBUGGER STATE ---
const debuggerState = {
    isActive: false,
    isPaused: false,
    scope: {},
    resolve: null, // A function to resolve the pause promise
    reject: null,  // A function to reject on stop
};

// Global IDE settings and objects
let IDE_ID, STORAGE_PREFIX, langTools;

// Constants will be defined in config, but this prepares the variables
// that will be initialized in main.js